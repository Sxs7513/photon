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
const fs = require('fs');
const path = require('path');
const { sep } = path;

const fs = globalThis.SJSJSBridge.fs

const { validateString } = require('internal/validators');

const {
  CHAR_FORWARD_SLASH,
  CHAR_BACKWARD_SLASH,
  CHAR_COLON
} = require('internal/constants');

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

function toRealPath(requestPath) {
  return fs.realpathSync(requestPath);
}

Module._load = function(request, parent, isMain) {
    const filename = Module._resolveFilename(request, parent, isMain);
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

Module._resolveFilename = function(request, parent, isMain, options) {
    if (NativeModule.canBeRequiredByUsers(request)) {
      return request;
    }
  
    let paths = Module._resolveLookupPaths(request, parent);
  
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

Module._resolveLookupPaths = function(request, parent) {
  if (NativeModule.canBeRequiredByUsers(request)) {
    debug('looking for %j in []', request);
    return null;
  }

  if (StringPrototypeCharAt(request, 0) !== '.' ||
      (request.length > 1 &&
      StringPrototypeCharAt(request, 1) !== '.' &&
      StringPrototypeCharAt(request, 1) !== '/' &&
      (!isWindows || StringPrototypeCharAt(request, 1) !== '\\'))) {

    let paths = modulePaths;
    if (parent?.paths?.length) {
      paths = ArrayPrototypeConcat(parent.paths, paths);
    }

    debug('looking for %j in %j', request, paths);
    return paths.length > 0 ? paths : null;
  }

  if (!parent || !parent.id || !parent.filename) {
    const mainPaths = ['.'];

    debug('looking for %j in %j', request, mainPaths);
    return mainPaths;
  }

  debug('RELATIVE: requested: %s from parent.id %s', request, parent.id);

  const parentDir = [path.dirname(parent.filename)];
  debug('looking for %j', parentDir);
  return parentDir;
};

Module._initPaths = function() {
  const homeDir = isWindows ? process.env.USERPROFILE : safeGetenv('HOME');
  const nodePath = isWindows ? process.env.NODE_PATH : safeGetenv('NODE_PATH');

  const prefixDir = process.execPath

  const paths = [path.resolve(prefixDir, 'lib')];

  // if (homeDir) {
  //   ArrayPrototypeUnshift(paths, path.resolve(homeDir, '.node_libraries'));
  //   ArrayPrototypeUnshift(paths, path.resolve(homeDir, '.node_modules'));
  // }

  // if (nodePath) {
  //   ArrayPrototypeUnshiftApply(paths, ArrayPrototypeFilter(
  //     StringPrototypeSplit(nodePath, path.delimiter),
  //     Boolean
  //   ));
  // }

  modulePaths = paths;

  // Clone as a shallow copy, for introspection.
  Module.globalPaths = ArrayPrototypeSlice(modulePaths);
};

const trailingSlashRegex = /(?:^|\/)\.?\.$/;
Module._findPath = function(request, paths, isMain) {
  const absoluteRequest = path.isAbsolute(request);
  if (absoluteRequest) {
    paths = [''];
  } else if (!paths || paths.length === 0) {
    return false;
  }

  const cacheKey = request + '\x00' + ArrayPrototypeJoin(paths, '\x00');
  const entry = Module._pathCache[cacheKey];
  if (entry)
    return entry;

  let exts;
  let trailingSlash = request.length > 0 &&
    StringPrototypeCharCodeAt(request, request.length - 1) ===
    CHAR_FORWARD_SLASH;
  if (!trailingSlash) {
    trailingSlash = RegExpPrototypeTest(trailingSlashRegex, request);
  }

  // For each path
  for (let i = 0; i < paths.length; i++) {
    const curPath = paths[i];

    const basePath = path.resolve(curPath, request);
    let filename;

    const [fstat, err] = fs.statSync(basePath)
    if (!trailingSlash) {
      if (fstat.isFile()) {  // File.
        if (!isMain) {
          filename = toRealPath(basePath);
        } else if (preserveSymlinksMain) {
          // For the main module, we use the preserveSymlinksMain flag instead
          // mainly for backward compatibility, as the preserveSymlinks flag
          // historically has not applied to the main module.  Most likely this
          // was intended to keep .bin/ binaries working, as following those
          // symlinks is usually required for the imports in the corresponding
          // files to resolve; that said, in some use cases following symlinks
          // causes bigger problems which is why the preserveSymlinksMain option
          // is needed.
          filename = path.resolve(basePath);
        } else {
          filename = toRealPath(basePath);
        }
      }

      if (!filename) {
        // Try it with each of the extensions
        if (exts === undefined)
          exts = ObjectKeys(Module._extensions);
        filename = tryExtensions(basePath, exts, isMain);
      }
    }

    if (!filename && rc === 1) {  // Directory.
      // try it with each of the extensions at "index"
      if (exts === undefined)
        exts = ObjectKeys(Module._extensions);
      filename = tryPackage(basePath, exts, isMain, request);
    }

    if (filename) {
      Module._pathCache[cacheKey] = filename;
      return filename;
    }
  }

  return false;
};