'use strict'

const {
    ArrayIsArray,
    ArrayPrototypeConcat,
    ArrayPrototypeFilter,
    ArrayPrototypeIncludes,
    ArrayPrototypeIndexOf,
    ArrayPrototypeJoin,
    ArrayPrototypePush,
    ArrayPrototypeSlice,
    ArrayPrototypeSplice,
    ArrayPrototypeUnshift,
    ArrayPrototypeUnshiftApply,
    Boolean,
    Error,
    JSONParse,
    ObjectCreate,
    ObjectDefineProperty,
    ObjectFreeze,
    ObjectGetOwnPropertyDescriptor,
    ObjectGetPrototypeOf,
    ObjectKeys,
    ObjectPrototype,
    ObjectPrototypeHasOwnProperty,
    ObjectSetPrototypeOf,
    Proxy,
    ReflectApply,
    ReflectSet,
    RegExpPrototypeExec,
    RegExpPrototypeTest,
    SafeMap,
    SafeWeakMap,
    String,
    StringPrototypeCharAt,
    StringPrototypeCharCodeAt,
    StringPrototypeEndsWith,
    StringPrototypeLastIndexOf,
    StringPrototypeIndexOf,
    StringPrototypeMatch,
    StringPrototypeRepeat,
    StringPrototypeSlice,
    StringPrototypeSplit,
    StringPrototypeStartsWith,
} = primordials;

const { NativeModule } = require('internal/bootstrap/loaders');
const path = require('path');
const { sep } = path;

const { validateString } = require('internal/validators');

const isWindows = process.platform === 'win32';

const moduleParentCache = new SafeWeakMap();
function Module(id = '', parent) {
    this.id = id;
    this.path = path.dirname(id);
    this.exports = {};
    this.filename = null;
    this.loaded = false;
}

const builtinModules = [];
for (const { 0: id, 1: mod } of NativeModule.map) {
  if (mod.canBeRequiredByUsers) {
    ArrayPrototypePush(builtinModules, id);
  }
}

ObjectFreeze(builtinModules);
Module.builtinModules = builtinModules;

Module._cache = ObjectCreate(null);
Module._pathCache = ObjectCreate(null);
Module._extensions = ObjectCreate(null);
let modulePaths = [];
Module.globalPaths = [];

let wrap = function(script) {
    return Module.wrapper[0] + script + Module.wrapper[1];
};
  
const wrapper = [
    '(function (exports, require, module, __filename, __dirname) { ',
    '\n});',
];

function getModuleParent() {
    return moduleParentCache.get(this);
}
  
function setModuleParent(value) {
    moduleParentCache.set(this, value);
}

const realpathCache = new SafeMap();

function emitCircularRequireWarning(prop) {
    console.log(
      `Accessing non-existent property '${String(prop)}' of module exports ` +
      'inside circular dependency'
    );
}

const CircularRequirePrototypeWarningProxy = new Proxy({}, {
    __proto__: null,
  
    get(target, prop) {
      if (prop in target || prop === '__esModule') return target[prop];
      emitCircularRequireWarning(prop);
      return undefined;
    },
  
    getOwnPropertyDescriptor(target, prop) {
      if (ObjectPrototypeHasOwnProperty(target, prop) || prop === '__esModule')
        return ObjectGetOwnPropertyDescriptor(target, prop);
      emitCircularRequireWarning(prop);
      return undefined;
    }
});

Module._load = function(request, isMain) {
    const filename = Module._resolveFilename(request, isMain);
    const cachedModule = Module._cache[filename];
    if (cachedModule !== undefined) {
      if (!cachedModule.loaded) {
        const parseCachedModule = cjsParseCache.get(cachedModule);
        if (!parseCachedModule || parseCachedModule.loaded)
          return getExportsForCircularRequire(cachedModule);
        parseCachedModule.loaded = true;
      } else {
        return cachedModule.exports;
      }
    }
  
    const mod = loadNativeModule(filename, request);
    if (mod?.canBeRequiredByUsers) {
      return mod.exports;
    }
  
    const module = cachedModule || new Module(filename, parent);
  
    if (isMain) {
      process.mainModule = module;
      module.id = '.';
    }
  
    Module._cache[filename] = module;
  
    let threw = true;
    try {
      module.load(filename);
      threw = false;
    } finally {
      if (threw) {
        delete Module._cache[filename];
      } else if (module.exports &&
                 !isProxy(module.exports) &&
                 ObjectGetPrototypeOf(module.exports) ===
                   CircularRequirePrototypeWarningProxy) {
        ObjectSetPrototypeOf(module.exports, ObjectPrototype);
      }
    }
  
    return module.exports;
};

Module._resolveFilename = function(request, isMain, options) {
    if (NativeModule.canBeRequiredByUsers(request)) {
      return request;
    }
  
    let paths;
  
    if (typeof options === 'object' && options !== null) {
      if (ArrayIsArray(options.paths)) {
        const isRelative = StringPrototypeStartsWith(request, './') ||
            StringPrototypeStartsWith(request, '../') ||
            ((isWindows && StringPrototypeStartsWith(request, '.\\')) ||
            StringPrototypeStartsWith(request, '..\\'));
  
        if (isRelative) {
          paths = options.paths;
        } else {
          const fakeParent = new Module('', null);
  
          paths = [];
  
          for (let i = 0; i < options.paths.length; i++) {
            const path = options.paths[i];
            fakeParent.paths = Module._nodeModulePaths(path);
            const lookupPaths = Module._resolveLookupPaths(request, fakeParent);
  
            for (let j = 0; j < lookupPaths.length; j++) {
              if (!ArrayPrototypeIncludes(paths, lookupPaths[j]))
                ArrayPrototypePush(paths, lookupPaths[j]);
            }
          }
        }
      } else if (options.paths === undefined) {
        paths = Module._resolveLookupPaths(request, parent);
      } else {
        throw new ERR_INVALID_ARG_VALUE('options.paths', options.paths);
      }
    } else {
      paths = Module._resolveLookupPaths(request, parent);
    }
  
    if (parent?.filename) {
      if (request[0] === '#') {
        const pkg = readPackageScope(parent.filename) || {};
        if (pkg.data?.imports != null) {
          try {
            return finalizeEsmResolution(
              packageImportsResolve(request, pathToFileURL(parent.filename),
                                    cjsConditions), parent.filename,
              pkg.path);
          } catch (e) {
            if (e.code === 'ERR_MODULE_NOT_FOUND')
              throw createEsmNotFoundErr(request);
            throw e;
          }
        }
      }
    }
  
    // Try module self resolution first
    const parentPath = trySelfParentPath(parent);
    const selfResolved = trySelf(parentPath, request);
    if (selfResolved) {
      const cacheKey = request + '\x00' +
           (paths.length === 1 ? paths[0] : ArrayPrototypeJoin(paths, '\x00'));
      Module._pathCache[cacheKey] = selfResolved;
      return selfResolved;
    }
  
    // Look up the filename first, since that's the cache key.
    const filename = Module._findPath(request, paths, isMain, false);
    if (filename) return filename;
    const requireStack = [];
    for (let cursor = parent;
      cursor;
      cursor = moduleParentCache.get(cursor)) {
      ArrayPrototypePush(requireStack, cursor.filename || cursor.id);
    }
    let message = `Cannot find module '${request}'`;
    if (requireStack.length > 0) {
      message = message + '\nRequire stack:\n- ' +
                ArrayPrototypeJoin(requireStack, '\n- ');
    }
    // eslint-disable-next-line no-restricted-syntax
    const err = new Error(message);
    err.code = 'MODULE_NOT_FOUND';
    err.requireStack = requireStack;
    throw err;
};