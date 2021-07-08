module DeviseHelper
	def devise_error_message!
		resource.errors.full_message.map { |msg| content_tag(:li,msg)}.join
		#rescue.errors.full_message.map { |msg| content_tag(:li,msg)}.join
	end 
end