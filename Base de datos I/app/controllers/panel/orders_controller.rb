class Panel::OrdersController < ApplicationController
  # before_action :set_user, only: [:show, :destroy]

  def create
    @order = Order.new(triage_params)
    @order.save
    render json: { params: params, notice: 'Orden registrada exitosamente' }
  end

  def list_type_orders
    @type_orders = TypeOrder.all
    render json: {
      type_orders: @type_orders,
    }, status: :ok
  end

  private
    def set_order
      @order = Order.find(params[:id])
    end

    def order_params
      params.require(:order).permit( :type_order_id, :treatment_id, :status)
    end
end
