class CreateSpecialities < ActiveRecord::Migration[6.0]
  def change
    create_table :specialities do |t|
      t.string :name
      t.text :description
      t.references :profession, null: false, foreign_key: true

      t.timestamps
    end
  end
end
