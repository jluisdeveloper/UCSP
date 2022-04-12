require "application_system_test_case"

class ProfessionsTest < ApplicationSystemTestCase
  setup do
    @profession = professions(:one)
  end

  test "visiting the index" do
    visit professions_url
    assert_selector "h1", text: "Professions"
  end

  test "creating a Profession" do
    visit professions_url
    click_on "New Profession"

    fill_in "Description", with: @profession.description
    fill_in "Name", with: @profession.name
    click_on "Create Profession"

    assert_text "Profession was successfully created"
    click_on "Back"
  end

  test "updating a Profession" do
    visit professions_url
    click_on "Edit", match: :first

    fill_in "Description", with: @profession.description
    fill_in "Name", with: @profession.name
    click_on "Update Profession"

    assert_text "Profession was successfully updated"
    click_on "Back"
  end

  test "destroying a Profession" do
    visit professions_url
    page.accept_confirm do
      click_on "Destroy", match: :first
    end

    assert_text "Profession was successfully destroyed"
  end
end
