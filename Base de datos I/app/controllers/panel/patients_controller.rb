class Panel::PatientsController < ApplicationController
  before_action :set_patient, only: [:update, :destroy]

  def index
    @patients = Patient.all.order(created_at: :desc).page(params[:page])
    render json: {
      patients: @patients,
      current_page: @patients.current_page,
      total_pages: @patients.total_pages,
      per_pages: @patients.limit_value
    }, status: :ok
  end

  def full_patients
    @patients = Patient.all.order(created_at: :desc)
    render json: {
      patients: @patients
    }, status: :ok
  end

  def create
    @patient = Patient.new(patient_params)
    @patient.save
    render json: { params: params, notice: 'Paciente registrado exitosamente' }
  end


  def destroy
    @patient.destroy
    render json: { notice: 'Paciente Eliminado exitosamente' }
  end

  def update
    @patient.update(patient_params)
    render json: { notice: 'Paciente actualizado exitosamente' }
  end

  private
    def set_patient
      @patient = Patient.find(params[:id])
    end

    def patient_params
      params.require(:patient).permit :nro_register, :full_name, :phone, :address, :blood_type, triages_attributes: [:id, :weight, :height, :blood_pressure, :priority, :_destroy ]
    end

end
