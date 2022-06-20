
const os = globalThis.SJSJSBridge.os
const fs = globalThis.SJSJSBridge.fs

const buildInModule = ["path", "internal"]

const platformIsWin32 = (process.platform === 'win32');

const sep = platformIsWin32 ? "\\" : "/"
const LIB_PATH_PREFIX = `${process.execPath}${sep}lib${sep}`

const modules = {}

let idx = 0

let debug = console.log
{
	let _debugOptions = os.getenv('DEBUG')
	if (typeof _debugOptions == 'undefined' || _debugOptions.split(',').indexOf('require') === -1) {
		debug = function () {}
	}
}

const pathModule = fastLoadBuitInModule('path')

function safeWrapAndExec (moduleObj, requireFunc, path, dirname, filename, content, name) {
	const tempArgs = [moduleObj.exports, requireFunc, moduleObj, filename, dirname]
	const key = `__SJS_MODULE_WRAPPER_${idx++}`
	globalThis[key] = tempArgs
    content = `(function loader (exports, require, module, __filename, __dirname) {${content}})(...globalThis["${key}"])`
    __NativeEvalModule(content, name)
	delete globalThis[key]
}

class Module {
	constructor (path) {
        this.path = path
		this._failed = null
		this._loaded = false
		this.exports = {}
	}

	load () {
		const __file = this.path
		const __dir = pathModule.dirname(this.path)

		let ctx = { exports: {} }
		// Prevents modules from changing exports
		Object.seal(ctx)

		const _require = (path) => {
			const module = path.split('/')[0]
			if (buildInModule.includes(module)) {
				path = `${LIB_PATH_PREFIX}${path}`
			} else {
				path = pathModule.resolve(__dir, path)
			}

			return require(path)
		}

		let _script = fs.readFileSync(this.path)
		this._failed = _script === null
		if (this._failed) {
			return new Error(`Can't load script ${__file}`)
		}

		safeWrapAndExec(this, _require, this.path, __dir, this.path, _script, this.path)

		this.exports = ctx.exports
		this._loaded = true
		return true
	}
}

function _statPath (path) {
	const [fstat, err] = fs.statSync(path)
	return {
		errno: err,
		isFile: fstat && (fstat.mode & fs.S_IFREG) && true,
		isDir: fstat && (fstat.mode & fs.S_IFDIR) && true
	}
}

function _loadModule (path) {
	debug(`_loadModule# Module ${path}`)
	
	debug(`_loadModule# id ${path}`)
	if (modules.hasOwnProperty(path)) {
		return modules[path]
	}

	let _module = new Module(path)
	modules[path] = _module

	let _result = _module.load()
	if (_result !== true) {
		throw _result
		return
	}
	return _module
}

function _lookupModule (path) {
	let fstat = _statPath(path)

	debug(`_lookupModule# Looking for ${path}`)
	// Path found
	if (fstat.isFile) {
		debug(`_lookupModule# Found module file`)
		return path
	}

	// Path not found
	if (fstat.errno) {
		debug(`_lookupModule# Not found module file`)
		// Try with '.js' extension
		if (!path.endsWith('.js') && _statPath(`${path}.js`).isFile) {
			debug(`_lookupModule# Found appending .js to file name`)
			return `${path}.js`
		}
		return new Error(`Error: Module ${path} not found!`)
	}

	// Path found and it isn't a dir
	if (!fstat.isDir) {
		return new Error(`Error: Module file type not supported for ${path}`)
	}

	// Path it's a dir
	let _path = null	// Real path to module
	let _tryOthers = true	// Keep trying?

	debug(`_lookupModule# Path is a directory, trying options...`)
	// Try with package.json for NPM or YARN modules
	if (_statPath(`${path}/package.json`).isFile) {
		debug(`_lookupModule# It has package.json, looking for main script...`)
		let _pkg = JSON.parse(fs.readFileSync(`${path}/package.json`))
		if (_pkg && Object.keys(_pkg).indexOf('main') !== -1 && _pkg.main !== '' && _statPath(`${path}/${_pkg.main}`).isFile) {
			_tryOthers = false
			_path = `${path}/${_pkg.main}`
			debug(`_lookupModule# Found package main script!`)
		}
	}
	// Try other options
	if (_tryOthers && _statPath(`${path}/index.js`).isFile) {
		_tryOthers = false
		_path = `${path}/index.js`
		debug(`_lookupModule# Found package index.js file`)
	}
	if (_tryOthers && _statPath(`${path}/main.js`).isFile) {
		_tryOthers = false
		_path = `${path}/main.js`
		debug(`_lookupModule# Found package main.js file`)
	}

	if (_path === null) {
		return new Error(`Error: Module ${path} is a directory, but not a package`)
	}

	debug(`_lookupModule# Found module file: ${_path}`)
	// Returns what it founded
	return _path
}

function require (path) {
	if (typeof __filename == 'undefined') {
		debug('require# Calling from main script')
	} else {
		debug(`require# Calling from ${__filename} parent module`)
	}
	let _path = _lookupModule(path)

	// Module not found
	if (_path instanceof Error) {
		throw _path
		return
	}

	let _module = _loadModule(_path)

	return _module.exports
}

function _dirname (path) {
	let idx = path.lastIndexOf(sep)
	if (idx === 0)
		return sep
	return path.substring(0, idx)
}

function fastLoadBuitInModule (module) {
	const path = `${LIB_PATH_PREFIX}${module}.js`
	let _module = {
		id: module,
        path: path,
		_failed: null,
		_loaded: true,
		exports: {}
	}
	modules[path] = _module

	const _require = fastLoadBuitInModule

	let _script = fs.readFileSync(path)
	safeWrapAndExec(_module, _require, path, _dirname(path), path, _script, path)

	return _module.exports
}

function loadMainModule (path) {
	let _module = new Module(path, path)
	modules[path] = _module

	_module.load()
}

function executeUserEntryPoint(main = process.argv[1]) {
	const resolvedMain = resolveMainPath(main);
	const useESMLoader = shouldUseESMLoader(resolvedMain);
	if (useESMLoader) {
	  runMainESM(resolvedMain || main);
	} else {
	  // Module._load is the monkey-patchable CJS module loader.
	  Module._load(main, null, true);
	}
  }

globalThis.__loadMainModule = loadMainModule