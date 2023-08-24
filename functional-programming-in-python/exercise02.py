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


def order_by_salary(emp):
    return emp["salary"]


def order_by_age(emp):
    return 2022 - emp["birthYear"]


def order_by_department(emp):
    return emp["department"]


def order_by(field): # higher-order function
    return lambda e: e[field]


for employee in employees:
    print(employee)
employees.sort(key=order_by("birthYear"), reverse=False)  # higher-order function
for employee in employees:
    print(employee)
