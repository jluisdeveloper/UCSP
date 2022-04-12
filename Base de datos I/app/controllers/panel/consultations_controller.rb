class Panel::ConsultationsController < ApplicationController
  before_action :set_consultation, only: [:show]

  def index
    @consultations = Consultation.all
    render :json => @consultations, :include => {
      :triage => {:only => [:id, :priority], :include => { :patient => { :only => [:id, :full_name, :nro_register] } } },
      :user => {:only => [:id, :full_name] },
    }, :except => [:triage_id, :user_id]
  end


  def show
    render :json => @consultation, :include => {
      :triage => {:only => [:id, :priority, :blood_pressure, :weight, :height], :include => { :patient => { :only => [:id, :full_name, :nro_register] } } },
      :treatment => {:only => [:id, :diagnostic], :include => { :prescriptions => { :only => [:id, :description] }, :orders => { :only => [:id, :status_order, :priority_order], :include => {:type_order => { :only => [:id, :name] } } } } },
      :user => {:only => [:id, :full_name] },
    }, :except => [:created_at, :updated_at, :triage_id, :user_id]

  end

  def create
    @consultation = Consultation.new(consultation_params)
    @consultation.save

    @triageUpdate = Triage.find(params[:triage_id])
    @triageUpdate.status = "assigned"
    @triageUpdate.save

    render json: { params: params, notice: 'Consulta asignada exitosamente' }
  end

  private
    def set_consultation
      @consultation = Consultation.find(params[:id])
    end

    def consultation_params
      params.require(:consultation).permit(:user_id, :triage_id, :hour, :status)
    end
end
