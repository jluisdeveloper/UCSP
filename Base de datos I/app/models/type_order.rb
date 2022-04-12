class TypeOrder < ApplicationRecord
  has_many :orders, dependent: :destroy

end
