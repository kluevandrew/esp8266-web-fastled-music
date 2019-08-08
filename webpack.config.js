const path = require('path');
const webpack = require('webpack');
const ExtractTextPlugin = require('extract-text-webpack-plugin');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const CleanWebpackPlugin = require('clean-webpack-plugin');
const CopyPlugin = require('copy-webpack-plugin');
const OptimizeCssAssetsPlugin = require('optimize-css-assets-webpack-plugin');
const Autoprefixer = require('autoprefixer');
const fg = require('fast-glob');

const PATHS = {
    root: path.resolve(__dirname, './'),
    source: path.join(__dirname, './ui'),
    build: path.join(__dirname, './data')
};

function html(glob) {
    return fg.sync(glob).map(function (file) {
        const name = path.basename(file);
        if (name[0] === '_') {
            return null;
        }
        return new HtmlWebpackPlugin({
            filename: file.replace('./ui/', '').replace('.twig', '.html'),
            template: `${PATHS.source}/${file.replace('./ui/', '')}`,
        });
    }).filter((i) => i !== null);
}

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
                test: /\.twig/,
                loader: 'twig-loader'
            },
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
        ],
    },
    plugins: [
        new webpack.ProgressPlugin(),
        new CleanWebpackPlugin(),
        ...html('./ui/**/*.twig'),
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
