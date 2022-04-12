class CreatePrescriptions < ActiveRecord::Migration[6.0]
  def change
    create_table :prescriptions do |t|
      t.references :treatment, null: false, foreign_key: true
      t.string :description

      t.timestamps
    end
  end
end
