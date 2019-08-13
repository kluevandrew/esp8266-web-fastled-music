const path = require('path');
const merge = require('webpack-merge');
const baseWebpackConfig = require('./webpack.base');

module.exports = merge(baseWebpackConfig, {
    mode: 'development',
    devtool: 'eval-source-map',
    devServer: {
        contentBase: path.join(__dirname, "dist"),
        compress: true,
        inline: true,
        port: 4200,
    },
});