from functools import reduce
from operator import concat

numbers = [3, 6, 1, 5]  # 3615

total = 0
for number in numbers:
    total = 10 * total + number
print(total)

total = reduce(lambda ps, number: 10 * ps + number, numbers)
print(total)

total = reduce(concat, map(str, numbers))
print(total)

list = [(lambda u: 2*u)(x) for x in numbers]
print(list)
