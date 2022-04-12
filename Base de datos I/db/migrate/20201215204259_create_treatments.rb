class CreateTreatments < ActiveRecord::Migration[6.0]
  def change
    create_table :treatments do |t|
      t.string :diagnostic
      t.references :consultation, null: false, foreign_key: true
      t.timestamps
    end
  end
end
