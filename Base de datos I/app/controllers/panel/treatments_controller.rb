class Panel::TreatmentsController < ApplicationController

  def create
    @treatment = Treatment.new(treatment_params)

    if @treatment.save
      @consultationUpdate = Consultation.find(params[:treatment][:consultation_id])
      @consultationUpdate.status = "attended"
      @consultationUpdate.save
      render json: { params: params, notice: 'Paciente diagnosticado y recetado exitosamente' }
    end

  end

  private
    def treatment_params
      params.require(:treatment).permit :diagnostic, :consultation_id, prescriptions_attributes: [:id, :description, :_destroy ], orders_attributes: [:id, :type_order_id, :priority_order, :_destroy ]
    end
end
