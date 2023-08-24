#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include "employee.h"

auto
print_employee(const employee& emp){
    cout << "employee[ " << emp.getLastName() << ", " << emp.getFirstName()
         << ", department: " << emp.getDepartment()
         << ", birth year: " << emp.getBirthYear()
         << endl;
}

struct PrintEmployee {
    auto
    operator()(const employee& emp){
        cout << "employee[ " << emp.getLastName() << ", " << emp.getFirstName()
             << ", department: " << emp.getDepartment()
             << ", birth year: " << emp.getBirthYear()
             << endl;
    }
};
int main() {
    vector<employee> employees{
            {"kate","austen", employee::department_t::it,employee::gender_t::female, 200'000, "tr1", 1986},
            {"james","sawyer", employee::department_t::hr,employee::gender_t::male, 250'000, "tr2", 1976},
            {"juliet","burke", employee::department_t::sales,employee::gender_t::female, 100'000, "tr3", 1996},
            {"john","locke", employee::department_t::finance,employee::gender_t::male, 150'000, "tr4", 1956},
            {"ben","linus", employee::department_t::it,employee::gender_t::male, 300'000, "tr5", 1966}
    };
    // HoF: for_each
    for_each(employees.begin(),employees.end(), print_employee); // C-like function
    for_each(employees.begin(),employees.end(), PrintEmployee()); // Function Object
    for_each(employees.begin(),employees.end(), [](const employee& emp){ // Lambda Expression -- syntactic sugar --> Function Object
        cout << "employee[ " << emp.getLastName() << ", " << emp.getFirstName()
             << ", department: " << emp.getDepartment()
             << ", birth year: " << emp.getBirthYear()
             << endl;
    });

    return 0;
}
