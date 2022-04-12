class Triage < ApplicationRecord
  belongs_to :patient
  has_one :consultation, dependent: :destroy
  before_create :set_status

  paginates_per 10

  enum status: [ :unssigned, :assigned ]

  private
    def set_status
      self.status = :unssigned
    end
end
