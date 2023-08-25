#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

#include "employee.h"

auto
print_employee(const employee &emp) {
    cout << "employee[ " << emp.getLastName() << ", " << emp.getFirstName()
         << ", department: " << emp.getDepartment()
         << ", birth year: " << emp.getBirthYear()
         << ", salary: " << emp.getSalary()
         << endl;
}

struct PrintEmployee {
    auto
    operator()(const employee &emp) {
        cout << "employee[ " << emp.getLastName() << ", " << emp.getFirstName()
             << ", department: " << emp.getDepartment()
             << ", birth year: " << emp.getBirthYear()
             << endl;
    }
};

auto
orderByAgeAsc(employee &first, employee &second) {
    cout << "orderByAgeAsc()" << endl;
    return first.getBirthYear() > second.getBirthYear();
}

auto
orderByAgeDesc(employee &first, employee &second) {
    cout << "orderByAgeDesc( " << first.getFirstName() << "," << second.getFirstName() << " )" << endl;
    return first.getBirthYear() < second.getBirthYear();
}

auto
bySalary(const employee &emp) {
    return emp.getSalary();
}

auto
byBirthYear(const employee &emp) {
    return emp.getBirthYear();
}

template<class T>
bool
inAscendingOrder(const T &x, const T &y) {
    return x < y;
}

template<class T>
bool
inDescendingOrder(const T &x, const T &y) {
    return x > y;
}

template<class T, class OrderBy, class CompareBy>
decltype(auto)
getOrder(OrderBy orderBy, CompareBy compareBy) { // Generic HoF
    return [orderBy, compareBy](const T &first, const T &second) { // Pure Function
        return compareBy(orderBy(first), orderBy(second));
    };
}


template<class T, class OrderByFirst, class CompareByFirst, class OrderBySecond, class CompareBySecond>
decltype(auto)
getOrderThen(OrderByFirst orderByFirst, CompareByFirst compareByFirst, OrderBySecond orderBySecond,
             CompareBySecond compareBySecond) { // Generic HoF
    return [orderByFirst, compareByFirst, orderBySecond, compareBySecond](const T &first,
                                                                          const T &second) -> bool { // Pure Function
        if (orderByFirst(first) == orderByFirst(second))
            return compareBySecond(orderBySecond(first), orderBySecond(second));
        return compareByFirst(orderByFirst(first), orderByFirst(second));
    };
}

auto
topla(double birikec, const employee &emp) {
    return birikec + emp.getSalary();
}

struct ToplamMaas {
    auto
    operator()(double birikec, const employee &emp) {
        return birikec + emp.getSalary();
    }
};

struct BolumToplamMaas {
    employee::department_t dept;

    explicit BolumToplamMaas(employee::department_t dept=employee::department_t::it) : dept(dept) {}

    auto
    operator()(double birikec, const employee &emp) {
            auto salary = 0.0;
            if (emp.getDepartment() == dept)
                salary = emp.getSalary();
            return birikec + salary;
        }
};

int main() {
    vector<employee> employees{
            {"kate",   "austen", employee::department_t::it,      employee::gender_t::female, 200'000, "tr1", 1986},
            {"james",  "sawyer", employee::department_t::hr,      employee::gender_t::male,   100'000, "tr2", 1976},
            {"juliet", "burke",  employee::department_t::it,      employee::gender_t::female, 100'000, "tr3", 1996},
            {"john",   "locke",  employee::department_t::finance, employee::gender_t::male,   200'000, "tr4", 1956},
            {"ben",    "linus",  employee::department_t::it,      employee::gender_t::male,   100'000, "tr5", 1966}
    };
    auto dept = employee::department_t::it;

    //auto total_salary = accumulate(employees.begin(),employees.end(),double(),topla);
    //total_salary = accumulate(employees.begin(),employees.end(),double(),ToplamMaas());
    // Object            --> Class
    // Lambda Expression --> Function Object
    auto getTotalSalaryOfEmployeesInDept = [dept](double birikec, const employee &emp) {
        auto salary = 0.0;
        if (emp.getDepartment() == dept)
            salary = emp.getSalary();
        return birikec + salary;
    };
    //auto total_salary = accumulate(employees.begin(), employees.end(), double(), getTotalSalaryOfEmployeesInDept);
    auto total_salary = accumulate(employees.begin(), employees.end(), double(), BolumToplamMaas(employee::it));

    cout << "total salary is " << total_salary << endl;
    return 0;
}
