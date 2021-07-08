class User < ApplicationRecord
  ############################################################################################
  ## PeterGate Roles                                                                        ##
  ## The :user role is added by default and shouldn't be included in this list.             ##
  ## The :root_admin can access any page regardless of access settings. Use with caution!   ##
  ## The multiple option can be set to true if you need users to have multiple roles.       ##
  petergate(roles: [:site_admin], multiple: false)                                      ##
  ############################################################################################ 
 

  # Include default devise modules. Others available are:
  # :confirmable, :lockable, :timeoutable, :trackable and :omniauthable
  extend Devise::Models
  devise :database_authenticatable, :registerable,
         :recoverable, :rememberable,:trackable, :validatable
	
   validates_presence_of :name

   def first_name 
   	if(self.name != nil)
   		self.name.split[0]
   	else
   		puts "first name is nil!"
   	end
   end

   def last_name
   	if(self.name != nil)
   		self.name.split[1]
   	else
		puts "first name is nil!"
   	end
   end
end

