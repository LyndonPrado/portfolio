class PagesController < ApplicationController
  def home
	@posts = Blog.all
	@skills = Skill.all
	@currentUser = current_user
  end

  def about
  	@skills =  Skill.all
  end

  def contact
  end
end
