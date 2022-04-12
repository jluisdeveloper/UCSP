class Treatment < ApplicationRecord
  belongs_to :consultation

  has_many :prescriptions, dependent: :destroy
  has_many :orders, dependent: :destroy

  accepts_nested_attributes_for :prescriptions, allow_destroy: true
  accepts_nested_attributes_for :orders, allow_destroy: true

end
