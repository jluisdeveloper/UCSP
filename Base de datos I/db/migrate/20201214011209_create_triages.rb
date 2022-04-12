class CreateTriages < ActiveRecord::Migration[6.0]
  def change
    create_table :triages do |t|
      t.references :patient, null: false, foreign_key: true
      t.decimal :weight
      t.decimal :height
      t.string :blood_pressure
      t.string :priority
      t.integer :status

      t.timestamps
    end
  end
end
