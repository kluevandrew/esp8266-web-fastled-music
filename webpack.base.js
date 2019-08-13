const path = require('path');
const webpack = require('webpack');
const ExtractTextPlugin = require('extract-text-webpack-plugin');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const CleanWebpackPlugin = require('clean-webpack-plugin');
const CopyPlugin = require('copy-webpack-plugin');
const OptimizeCssAssetsPlugin = require('optimize-css-assets-webpack-plugin');
const Autoprefixer = require('autoprefixer');

const PATHS = {
    root: path.resolve(__dirname, './'),
    source: path.join(__dirname, './ui'),
    build: path.join(__dirname, './data')
};

module.exports = {
    mode: 'production',
    context: PATHS.root + '/ui',
    entry: {
        'esp8266-web-fastled-music': [PATHS.root + '/ui/app.ts', PATHS.root + '/ui/sass/app.scss'],
    },
    output: {
        path: PATHS.build,
        filename: 'app.[contenthash].js',
        publicPath: '/'
    },
    resolve: {
        extensions: ['.ts', '.js', '.css', '.scss', '.html', '.svg', '.jpg', '.jpeg', '.png', '.gif'],
    },
    module: {
        rules: [
            {
                test: /\.ts$/,
                loader: 'ts-loader',
                exclude: /node_modules/,
            },
            {
                test: /\.(css|scss)$/,
                loader: ExtractTextPlugin.extract({
                    use: 'css-loader!sass-loader',
                    fallback: 'style-loader',
                }),
            },
            {
                test: /\.(jpe?g|png|gif|svg)$/,
                loaders: [
                    'file-loader?hash=sha512&digest=hex&name=[name]_[hash].[ext]&outputPath=images/',
                    'image-webpack-loader?bypassOnDebug&optimizationLevel=7&interlaced=false'
                ]
            },
            {
                test: /\.twig/,
                exclude: /node_modules/,
                loader: "twig-loader?exportAsEs6Default"
            },
        ],
    },
    plugins: [
        new webpack.ProgressPlugin(),
        new CleanWebpackPlugin(),
        new HtmlWebpackPlugin({
            template: PATHS.root + '/ui/index.html'
        }),
        Autoprefixer,
        new ExtractTextPlugin({
            filename: 'app.[hash].css',
            allChunks: true,
        }),
        new OptimizeCssAssetsPlugin({
            assetNameRegExp: /\.css$/g,
            cssProcessor: require('cssnano'),
            cssProcessorPluginOptions: {
                preset: ['default', {discardComments: {removeAll: true}}],
            },
            canPrint: true
        }),
        new CopyPlugin([
            {from: 'assets', to: 'assets', force: true},
        ])
    ],
};
