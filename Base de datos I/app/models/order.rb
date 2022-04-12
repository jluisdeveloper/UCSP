class Order < ApplicationRecord
  belongs_to :type_order
  belongs_to :treatment

  # 2 horas para comentar esta wada :v no tocar o trashea
  # belongs_to :consultation


  before_create :set_status_order

  enum status_order: [ :atendido, :espera, :rechazado ]
  enum priority_order: [ :urgente, :medio, :opcional ]


  private
    def set_status_order
      self.status_order = :espera
    end

end
