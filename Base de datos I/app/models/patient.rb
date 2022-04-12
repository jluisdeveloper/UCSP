class Patient < ApplicationRecord
  paginates_per 10

  has_many :triages, dependent: :destroy
  accepts_nested_attributes_for :triages, allow_destroy: true
end
