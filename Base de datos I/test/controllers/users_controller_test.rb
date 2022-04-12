require 'test_helper'

class UsersControllerTest < ActionDispatch::IntegrationTest
  test "should get current_user" do
    get users_current_user_url
    assert_response :success
  end

end
