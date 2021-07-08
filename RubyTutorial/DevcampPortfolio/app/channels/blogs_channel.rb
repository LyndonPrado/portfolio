class BlogsChannel < ApplicationCable::Channel
	def subscribed
		stream_from "blogs#{params['blog_id']}_channel"
	end

	def unsubscribed 
	end 

	def send_comment(data)
		byebug
		current_user.comments.create!(content: data['comment'], blog_id: data['blog_id'])
	end
end
