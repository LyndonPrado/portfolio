Rails.application.routes.draw do
  resources :topics, only: [:index, :show]
  # get 'topics/index'
  # get 'topics/show'
  resources :comments
  devise_for :users, path: '', path_names: {sign_in: 'login', sign_out: 'logout', sign_up: 'register'}
  resources :portfolios, except: [:show] do
    put :sort, on: :collection
  end
  get 'angular-items', to: 'portfolios#angular'
  get 'portfolio/:id', to: 'portfolios#show', as: 'portfolio_show'
  # get 'portfolios/index'
  get 'about', to: 'pages#about'
  get 'contact', to: 'pages#contact'
  #get 'pages/about'
  #get 'pages/contact'
  # get 'portfolios/index'
  resources :blogs do
    member do
      get :toggle_status
    end
  end
  #get 'portfolios/index' => 'portfolios#index'
  # For details on the DSL available within this file, see https://guides.rubyonrails.org/routing.html
  mount ActionCable.server => '/cable'
  root to: 'pages#home'
end



