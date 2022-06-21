'use strict'

const {
    ArrayFrom,
    ArrayPrototypeMap,
    ArrayPrototypePush,
    ArrayPrototypeSlice,
    Error,
    ObjectCreate,
    ObjectDefineProperty,
    ObjectKeys,
    ObjectPrototypeHasOwnProperty,
    ReflectGet,
    SafeMap,
    SafeSet,
    String,
    StringPrototypeStartsWith,
    TypeError,
} = primordials;

const moduleLoadList = [];
ObjectDefineProperty(process, 'moduleLoadList', {
    __proto__: null,
    value: moduleLoadList,
    configurable: true,
    enumerable: true,
    writable: false
});

const loaderId = 'internal/bootstrap/loaders';
const moduleIds = [];

const getOwn = (target, property, receiver) => {
    return ObjectPrototypeHasOwnProperty(target, property) ?
        ReflectGet(target, property, receiver) :
        undefined;
};

class NativeModule {
    /**
     * A map from the module IDs to the module instances.
     * @type {Map<string, NativeModule>}
     */
    static map = new SafeMap(
        ArrayPrototypeMap(moduleIds, (id) => [id, new NativeModule(id)])
    );

    constructor(id) {
        this.filename = `${id}.js`;
        this.id = id;
        this.canBeRequiredByUsers = !StringPrototypeStartsWith(id, 'internal/');

        this.exports = {};
        this.loaded = false;
        this.loading = false;

        this.module = undefined;

        this.exportKeys = undefined;
    }

    static exposeInternals() {
        for (const { 0: id, 1: mod } of NativeModule.map) {
            if (id !== loaderId) {
                mod.canBeRequiredByUsers = true;
            }
        }
    }

    static exists(id) {
        return NativeModule.map.has(id);
    }

    static canBeRequiredByUsers(id) {
        const mod = NativeModule.map.get(id);
        return mod && mod.canBeRequiredByUsers;
    }

    compileForPublicLoader() {
        if (!this.canBeRequiredByUsers) {
            throw new Error(`Should not compile ${this.id} for public use`);
        }
        this.compileForInternalLoader();
        return this.exports;
    }

    compileForInternalLoader() {
        if (this.loaded || this.loading) {
            return this.exports;
        }

        const id = this.id;
        this.loading = true;

        try {
            const requireFn = StringPrototypeStartsWith(this.id, 'internal/deps/') ?
                requireWithFallbackInDeps : nativeModuleRequire;

            const fn = compileFunction(id);
            fn(this.exports, requireFn, this, process, internalBinding, primordials);

            this.loaded = true;
        } finally {
            this.loading = false;
        }

        ArrayPrototypePush(moduleLoadList, `NativeModule ${id}`);
        return this.exports;
    }
};

const loaderExports = {
    NativeModule,
    require: nativeModuleRequire
};

function nativeModuleRequire(id) {
    if (id === loaderId) {
        return loaderExports;
    }

    const mod = NativeModule.map.get(id);
    if (!mod) throw new TypeError(`Missing internal module '${id}'`);
    return mod.compileForInternalLoader();
};

function requireWithFallbackInDeps(request) {
    if (!NativeModule.map.has(request)) {
        request = `internal/deps/${request}`;
    }
    return nativeModuleRequire(request);
};

globalThis.NativeLoaderExports = loaderExports;