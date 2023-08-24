from functools import reduce

employees = [
    {"identity": "1", "fullname": "jack bauer", "salary": "10000", "iban": "tr1", "department": "IT",
     "birthYear": 1964},
    {"identity": "2", "fullname": "kate austen", "salary": "20000", "iban": "tr2", "department": "SALES",
     "birthYear": 1984},
    {"identity": "3", "fullname": "james sawyer", "salary": "30000", "iban": "tr3", "department": "HR",
     "birthYear": 1982},
    {"identity": "4", "fullname": "jin kwon", "salary": "40000", "iban": "tr4", "department": "IT", "birthYear": 1988},
    {"identity": "5", "fullname": "sun kwon", "salary": "50000", "iban": "tr5", "department": "FINANCE",
     "birthYear": 1987}
]
total_it_salary = 0
# outer loop
for employee in employees:
    if employee["department"] == "IT":
        salary = float(employee["salary"])
        total_it_salary += salary
print(f"total it salary is {total_it_salary}")

worksInItDepartment = lambda e: e["department"] == "IT"
toSalary = lambda e: float(e["salary"])
add = lambda x, y: x + y

# filter/map/reduce
total_it_salary = reduce(add, map(toSalary, filter(worksInItDepartment, employees)))
print(f"total it salary is {total_it_salary}")
# Functions : 1) Higher-Order Function: filter, map, reduce, sorted, order_by
#             2) Pure Function: lambda expression
