class Profession < ApplicationRecord
  has_many :users
  has_many :specialities
end
