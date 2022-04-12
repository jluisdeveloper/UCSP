  Rails.application.routes.draw do

    # verificar las rutas para panel y front despues de hacer pruebas
    resources :specialities
    resources :professions

    devise_for :users
    devise_scope :user do
      authenticated :user do
        root 'pages#panel', as: :authenticated_root
        # espacios de nombres para rutas del panel
        namespace :panel do
          get 'current_user', to: 'users#current_user'
          resources :users
          resources :patients
          get 'full_patients', to: 'patients#full_patients'
          resources :triages
          resources :consultations

          resources :treatments
          resources :orders
          get 'type_orders', to: 'orders#list_type_orders'

        end
        # Con match hacemos peticiones generales desde un punto de inicio q es panel, mantener este match abajo de todas las rutas
        match '*path', to: 'pages#panel', via: :all
      end
      unauthenticated :user do
        root 'pages#index', as: :unauthenticated_root
      end
    end
end