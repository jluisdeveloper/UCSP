class CreatePatients < ActiveRecord::Migration[6.0]
  def change
    create_table :patients do |t|
      t.string :nro_register
      t.string :full_name
      t.string :phone
      t.string :address
      t.string :blood_type
      t.timestamps
    end
  end
end
