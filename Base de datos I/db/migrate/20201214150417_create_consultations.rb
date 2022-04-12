class CreateConsultations < ActiveRecord::Migration[6.0]
  def change
    create_table :consultations do |t|
      t.references :user, null: false, foreign_key: true
      t.references :triage, null: false, foreign_key: true
      t.string :hour
      t.integer :status

      t.timestamps
    end
  end
end
