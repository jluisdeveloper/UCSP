class Panel::TriagesController < ApplicationController
  before_action :set_triage, only: [:show]
  #
  def index
    @triages = Triage.where('status = 0' ).order(created_at: :desc).page(params[:page])
    @patients = Patient.all
    @specialities = Speciality.all
    @users = User.where('profession_id = 2')

    render json: {
      triages: @triages,
      patients: @patients,
      users: @users,
      specialities: @specialities,
      current_page: @triages.current_page,
      total_pages: @triages.total_pages,
      per_pages: @triages.limit_value
    }, status: :ok
  end

  def show
    # render json: {
    #   triage: @triage,
    # }, status: :ok

    render :json => @triage, :include => {
      :patient => {:only => [:id, :full_name, :nro_register, :blood_type, :phone, :address ] },
      :consultation => {:only => [:id, :user_id] },
    }, :except => [:created_at, :updated_at]

  end

  def create
    @triage = Triage.new(triage_params)
    @triage.save
    render json: { params: params, notice: 'Triaje registrado exitosamente' }
  end

  private
    def set_triage
      @triage = Triage.find(params[:id])
    end

    def triage_params
      params.require(:triage).permit(:patient_id, :weight, :height, :blood_pressure, :priority)
    end
end
