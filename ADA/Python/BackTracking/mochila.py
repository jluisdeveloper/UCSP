# max amount of weight allowed
max_weight = 23

# max no.of items allowed
max_items = 2

# actual items
items = [13, 5, 4, 2, 6]

# max no.of items available
noof_items = len(items)

def knapsack(current_weight=0, index=0, items_count=0):
    # exit conditions
    if current_weight >= max_weight:
        return current_weight
    if items_count >= max_items:
        return current_weight
    if index >= noof_items:
        return current_weight
    # selection options/recursions
    #   note: in below case, since we have possibility of adding 1 new item we have 2 cases (take/don't take)
    case1 = knapsack(current_weight + items[index], index + 1, items_count + 1)
    case2 = knapsack(current_weight, index + 1, items_count)
    # checking if taking `index` item makes weight more than required.
    return max([x for x in [case1, case2] if x <= max_weight])


print(knapsack())