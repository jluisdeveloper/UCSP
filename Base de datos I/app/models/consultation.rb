class Consultation < ApplicationRecord
  belongs_to :user
  belongs_to :triage
  has_one :treatment, dependent: :destroy
  before_create :set_status

  enum status: [ :attended, :on_hold ]

  private
    def set_status
      self.status = :on_hold
    end

end
