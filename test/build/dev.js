const path = require('path')

let envPlugin = {
    name: 'env',
    setup(build) {
      // Intercept import paths called "env" so esbuild doesn't attempt
      // to map them to a file system location. Tag them with the "env-ns"
      // namespace to reserve them for this plugin.
      build.onResolve({ filter: /^path$/ }, args => ({
        path: args.path,
        namespace: 'env-ns',
      }))
  
      // Load paths tagged with the "env-ns" namespace and behave as if
      // they point to a JSON file containing the environment variables.
      build.onLoad({ filter: /.*/, namespace: 'env-ns' }, (args) => {
        return {
            contents: args.path,
          }
      })
    },
  }

require('esbuild').build({
    entryPoints: [path.resolve(__dirname, '../weather/index.jsx')],
    bundle: true,
    platform: 'neutral',
    external: ['path'],
    outfile: path.resolve(__dirname, '../test-weather.js'),
  }).catch(() => process.exit(1))