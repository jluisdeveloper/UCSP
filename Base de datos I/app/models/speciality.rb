class Speciality < ApplicationRecord
  has_one :user
  belongs_to :profession
end
