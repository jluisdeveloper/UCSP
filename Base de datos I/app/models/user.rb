class User < ApplicationRecord
  # Include default devise modules. Others available are:
  # :confirmable, :lockable, :timeoutable, :trackable and :omniauthable
  devise :database_authenticatable,
         :registerable,
         :recoverable,
         :rememberable,
         :validatable,
         authentication_keys: [:login]
  attr_writer :login
  mount_uploader  :avatar, AvatarUploader

  belongs_to :profession
  belongs_to :speciality
  has_many :consultations

  paginates_per 10

  # login polimorfico para iniciar sesion con el correo o el codigo de trabajo
  def login
    @login || self.code_job || self.email
  end

  private

    # Saltamos la verificacion del warden en cada inicio de sesion solo para validar y unificar mayusculas y minusculas
    def self.find_for_database_authentication warden_condition
      conditions = warden_condition.dup
      login = conditions.delete(:login)
      where(conditions).where(
        ["lower(code_job) = :value OR lower(email) = :value",
         { value: login.strip.downcase}]).first
    end

end
