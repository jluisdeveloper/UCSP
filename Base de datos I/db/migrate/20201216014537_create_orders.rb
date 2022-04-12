class CreateOrders < ActiveRecord::Migration[6.0]
  def change
    create_table :orders do |t|
      t.references :treatment, null: false, foreign_key: true
      t.references :type_order, null: false, foreign_key: true
      t.integer :status_order
      t.integer :priority_order

      t.timestamps
    end
  end
end
