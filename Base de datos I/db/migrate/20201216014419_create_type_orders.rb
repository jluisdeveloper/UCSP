class CreateTypeOrders < ActiveRecord::Migration[6.0]
  def change
    create_table :type_orders do |t|
      t.string :name
      t.string :description

      t.timestamps
    end
  end
end
