module DevcampViewTool
	extend ActiveSupport::Concern
	# class Renderer
	# 	def self.copyright name, msg
	# 		"&copy; #{Time.now.year} | <b>#{name}</b> #{msg}".html_safe
	# 	end
	# end

	included do
		before_action :set_copyright
	end
	
	
end

