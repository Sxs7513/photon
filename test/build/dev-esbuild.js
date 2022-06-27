const path = require('path');
const alias = require('esbuild-plugin-alias');

require('esbuild').build({
    entryPoints: [path.resolve(__dirname, '../memesearchapp/index.jsx')],
    bundle: true,
    platform: 'neutral',
    external: ['path'],
    outfile: path.resolve(__dirname, '../test-memesearchapp.js'),
    plugins: [
      alias({
        'photon-ui': path.resolve(__dirname, '../../render/react/index.js'),
      }),
    ],
}).catch(() => process.exit(1))