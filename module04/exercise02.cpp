#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <fstream>

using namespace std;

#include "employee.h"

enum format_t {
    plain, full_name, full
};

auto
print_employee(const employee &emp, ostream &out, format_t format) {
    if (format == format_t::full_name) {
        out << "employee[ " << emp.getLastName() << ", " << emp.getFirstName()
            << " ]" << endl;
    } else if (format == format_t::full) {
        out << "employee[ " << emp.getLastName() << ", " << emp.getFirstName()
            << ", department: " << emp.getDepartment()
            << ", birth year: " << emp.getBirthYear()
            << ", salary: " << emp.getSalary()
            << ", iban: " << emp.getIban()
            << " ]" << endl;
    } else if (format == format_t::plain) {
        out << "employee[ " << emp.getLastName() << ", " << emp.getFirstName()
            << ", department: " << emp.getDepartment()
            << " ]" << endl;
    }
}

auto
is_working_in_department(employee &emp, employee::department_t dept) {
    return emp.getDepartment() == dept;
}

int main() {
    ofstream to_file("c:\\tmp\\employees.txt");
    function<void(employee &)> printFullDetailsToConsole = bind(print_employee,placeholders::_1, ref(cout),format_t::full);
    function<void(employee &)> printFullDetailsToFile = bind(print_employee,placeholders::_1, ref(to_file),format_t::full);
    function<void(employee &)> printFullnameDetailsToFile = bind(print_employee,placeholders::_1, ref(to_file),format_t::full_name);
    function<void(employee &)> printFullnameDetailsToConsole = bind(print_employee,placeholders::_1, ref(cout),format_t::full_name);

    vector<employee> employees{
            {"kate",   "austen", employee::department_t::it,      employee::gender_t::female, 230'000, "tr1", 1986},
            {"james",  "sawyer", employee::department_t::hr,      employee::gender_t::male,   130'000, "tr2", 1976},
            {"juliet", "burke",  employee::department_t::sales,   employee::gender_t::female, 320'000, "tr3", 1996},
            {"john",   "locke",  employee::department_t::finance, employee::gender_t::male,   500'000, "tr4", 1956},
            {"ben",    "linus",  employee::department_t::it,      employee::gender_t::male,   400'000, "tr5", 1966}
    };
    function<bool(employee &, employee &)> bySalaryAsc = [](employee &first, employee &second) {
        return first.getSalary() < second.getSalary();
    };
    for_each(employees.begin(), employees.end(), printFullnameDetailsToConsole); // C-like function
    auto max_salary_emp = max_element(employees.begin(), employees.end(), bySalaryAsc);
    print_employee(*max_salary_emp,cout,format_t::full);
    auto min_salary_emp = max_element(employees.begin(), employees.end(),
                                      bind(bySalaryAsc, placeholders::_2, placeholders::_1));
    print_employee(*min_salary_emp,cout,format_t::plain);
    vector<employee> it_workers;
    function<bool(employee &)> is_working_in_it = bind(is_working_in_department, placeholders::_1,
                                                       employee::department_t::it);
    function<bool(employee &)> is_working_in_it2 = [](employee &emp) { // function object -> new
        return is_working_in_department(emp, employee::department_t::it);
    };
    cout << endl;
    copy_if(employees.begin(), employees.end(), back_inserter(it_workers), is_working_in_it);
    for_each(it_workers.begin(), it_workers.end(), printFullnameDetailsToFile); // C-like function
    cout << endl;
    vector<employee> it_workers2;
    copy_if(employees.begin(), employees.end(), back_inserter(it_workers2), is_working_in_it2);
    for_each(it_workers2.begin(), it_workers2.end(), printFullDetailsToFile); // C-like function
    return 0;
}
