# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# This file is the source Rails uses to define your schema when running `rails
# db:schema:load`. When creating a new database, `rails db:schema:load` tends to
# be faster and is potentially less error prone than running all of your
# migrations from scratch. Old migrations may fail to apply correctly if those
# migrations use external dependencies or application code.
#
# It's strongly recommended that you check this file into your version control system.

ActiveRecord::Schema.define(version: 2020_12_16_014537) do

  # These are extensions that must be enabled in order to support this database
  enable_extension "plpgsql"

  create_table "consultations", force: :cascade do |t|
    t.bigint "user_id", null: false
    t.bigint "triage_id", null: false
    t.string "hour"
    t.integer "status"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.index ["triage_id"], name: "index_consultations_on_triage_id"
    t.index ["user_id"], name: "index_consultations_on_user_id"
  end

  create_table "orders", force: :cascade do |t|
    t.bigint "treatment_id", null: false
    t.bigint "type_order_id", null: false
    t.integer "status_order"
    t.integer "priority_order"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.index ["treatment_id"], name: "index_orders_on_treatment_id"
    t.index ["type_order_id"], name: "index_orders_on_type_order_id"
  end

  create_table "patients", force: :cascade do |t|
    t.string "nro_register"
    t.string "full_name"
    t.string "phone"
    t.string "address"
    t.string "blood_type"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
  end

  create_table "prescriptions", force: :cascade do |t|
    t.bigint "treatment_id", null: false
    t.string "description"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.index ["treatment_id"], name: "index_prescriptions_on_treatment_id"
  end

  create_table "professions", force: :cascade do |t|
    t.string "name"
    t.text "description"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
  end

  create_table "specialities", force: :cascade do |t|
    t.string "name"
    t.text "description"
    t.bigint "profession_id", null: false
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.index ["profession_id"], name: "index_specialities_on_profession_id"
  end

  create_table "treatments", force: :cascade do |t|
    t.string "diagnostic"
    t.bigint "consultation_id", null: false
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.index ["consultation_id"], name: "index_treatments_on_consultation_id"
  end

  create_table "triages", force: :cascade do |t|
    t.bigint "patient_id", null: false
    t.decimal "weight"
    t.decimal "height"
    t.string "blood_pressure"
    t.string "priority"
    t.integer "status"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.index ["patient_id"], name: "index_triages_on_patient_id"
  end

  create_table "type_orders", force: :cascade do |t|
    t.string "name"
    t.string "description"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
  end

  create_table "users", force: :cascade do |t|
    t.string "email", default: "", null: false
    t.string "encrypted_password", default: "", null: false
    t.string "reset_password_token"
    t.datetime "reset_password_sent_at"
    t.datetime "remember_created_at"
    t.string "full_name", default: "", null: false
    t.string "code_job", default: "", null: false
    t.decimal "salary", precision: 8, scale: 2, null: false
    t.datetime "payment_date", null: false
    t.datetime "hiring_date", null: false
    t.bigint "profession_id", null: false
    t.bigint "speciality_id"
    t.string "phone"
    t.string "address"
    t.string "avatar"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.index ["code_job"], name: "index_users_on_code_job", unique: true
    t.index ["email"], name: "index_users_on_email", unique: true
    t.index ["profession_id"], name: "index_users_on_profession_id"
    t.index ["reset_password_token"], name: "index_users_on_reset_password_token", unique: true
    t.index ["speciality_id"], name: "index_users_on_speciality_id"
  end

  add_foreign_key "consultations", "triages"
  add_foreign_key "consultations", "users"
  add_foreign_key "orders", "treatments"
  add_foreign_key "orders", "type_orders"
  add_foreign_key "prescriptions", "treatments"
  add_foreign_key "specialities", "professions"
  add_foreign_key "treatments", "consultations"
  add_foreign_key "triages", "patients"
  add_foreign_key "users", "professions"
  add_foreign_key "users", "specialities"
end
