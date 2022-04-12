class Panel::UsersController < ApplicationController
  before_action :set_user, only: [:show, :update, :destroy]

  def current_user
    @user = User.find(session["warden.user.user.key"][0][0])
    render :json => @user, :include => {
      :profession => {:only => [:id, :name]},
      :speciality => {:only => [:id, :name] }
    }, :except => [:profession_id, :speciality_id]
  end

  def index
    @users = User.all.order(created_at: :desc).page(params[:page])
    render json: {
      users: @users,
      current_page: @users.current_page,
      total_pages: @users.total_pages,
      per_pages: @users.limit_value
    }, status: :ok
  end

  def show
  end

  def new
    @user = User.new
  end

  def create
    @user = User.new
    @user.email = params[:email]
    @user.password = params[:password]
    @user.password_confirmation = params[:password_confirmation]
    @user.full_name = params[:full_name]
    @user.code_job = params[:code_job]
    @user.salary = params[:salary]
    @user.payment_date = params[:payment_date]
    @user.hiring_date = params[:hiring_date]
    @user.profession_id = params[:profession_id]
    @user.speciality_id = params[:speciality_id]
    @user.phone = params[:phone]
    @user.address = params[:address]
    @user.avatar = params[:avatar]
    @user.save!

    render json: { params: params, notice: 'Usuario registrado exitosamente' }
  end

  def update
    @user.update(user_params)
    render json: { notice: 'Usuario actualizado exitosamente' }
  end

  def destroy
    @user.destroy
    render json: { notice: 'Usuario eliminado exitosamente' }
  end

  private
    def set_user
      @user = User.find(params[:id])
    end

    def user_params
      params.require(:user).permit(:email, :password, :password_confirmation, :remember_me, :full_name, :code_job, :salary, :payment_date, :hiring_date, :profession_id, :speciality_id, :phone, :address, :avatar)
    end

end
