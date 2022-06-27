const path = require('path');
const Webpack = require('webpack');
const webpackDevServer = require('webpack-dev-server');

const config = {
    devServer: {
        hot: true
    },
    entry: [path.resolve(__dirname, '../react-router/index.jsx')],
    output: {
        filename: path.resolve(__dirname, '../test-weather.js'),
    },
    plugins: [
        new webpack.HotModuleReplacementPlugin(),
    ],
}
const compiler = Webpack(webpackConfig);
const server = new webpackDevServer({ hot: false, client: false }, compiler);   // // `hot` and `client` options are disabled because we added them manually
(async () => {
    await server.start();
    console.log('dev server is running');
})();