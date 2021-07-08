const { environment } = require('@rails/webpacker')
const coffee =  require('./loaders/coffee')

const babelLoader = environment.loaders.get('babel')
babelLoader.test = /\.(coffee|js)(\.erb)?$/

const webpack = require('webpack')
environment.plugins.prepend( 'Provide',
	new webpack.ProvidePlugin({
		$: 'jquery/src/jquery',
		jQuery: 'jquery/src/jquery',
		Popper: ['popper.js', 'default']
	})
	// new webpack.ProvidePlugin({
	// 	$: 'jquery-ui-bundle/jquery-ui'
	// 	jquery-ui: 'jquery-ui-bundle/jquery-ui'
	// })
);

const aliasConfig = {
	'jquery-ui': 'query-ui-bundle/jquery-ui.js'
};

environment.config.set('resolve.alias', aliasConfig);

environment.loaders.prepend('coffee', coffee)
environment.loaders.append('coffee',coffee)
module.exports = babelLoader
environment.loaders.prepend('coffee', coffee)
module.exports = environment
