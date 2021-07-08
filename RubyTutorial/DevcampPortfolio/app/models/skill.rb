class Skill < ApplicationRecord
	include Placeholder
	validates_presence_of :title, :percent_utilized

end
