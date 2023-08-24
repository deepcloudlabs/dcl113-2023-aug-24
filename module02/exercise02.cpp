#include <iostream>
#include <vector>
#include <algorithm>

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
    cout << "orderByAgeDesc( " << first.getFirstName() << "," << second.getFirstName() << " )" << endl ;
    return first.getBirthYear() < second.getBirthYear();
}

auto
bySalary(const employee& emp){
    return emp.getSalary();
}

template <class T>
bool
inAscendingOrder(const T& x,const T& y){
    return x < y;
}

template <class T>
bool
inDescendingOrder(const T& x,const T& y) {
    return x > y;
}

template<class T,class OrderBy,class CompareBy>
decltype(auto)
getOrder(OrderBy orderBy, CompareBy compareBy){ // Generic HoF
    return [orderBy,compareBy](const T& first,const T& second){ // Pure Function
          return compareBy(orderBy(first),orderBy(second));
    } ;
}

int main() {
    vector<employee> employees{
            {"kate",   "austen", employee::department_t::it,      employee::gender_t::female, 200'000, "tr1", 1986},
            {"james",  "sawyer", employee::department_t::hr,      employee::gender_t::male,   250'000, "tr2", 1976},
            {"juliet", "burke",  employee::department_t::sales,   employee::gender_t::female, 100'000, "tr3", 1996},
            {"john",   "locke",  employee::department_t::finance, employee::gender_t::male,   150'000, "tr4", 1956},
            {"ben",    "linus",  employee::department_t::it,      employee::gender_t::male,   300'000, "tr5", 1966}
    };
    // HoF: sort
    // sorting ? criteria
    for_each(employees.begin(), employees.end(), print_employee); // C-like function
    sort(employees.begin(), employees.end(), getOrder<employee>(bySalary, less<double>()));
    cout << endl;
    for_each(employees.begin(), employees.end(), print_employee); // C-like function
    cout << endl;
    sort(employees.begin(), employees.end(), getOrder<employee>(bySalary, greater<double>()));
    for_each(employees.begin(), employees.end(), print_employee); // C-like function
    vector<string> names {"jack", "james", "ben", "sun", "jin", "kate"};
    auto byStringLength = [](const string &s) { return s.size(); };
    sort(names.begin(), names.end(), getOrder<string>(byStringLength, inAscendingOrder<int>));
    for_each(names.begin(),names.end(),[](const string& s){cout << s << endl;});
    sort(names.begin(),names.end(),getOrder<string>(byStringLength, inDescendingOrder<int>));
    for_each(names.begin(),names.end(),[](const string& s){cout << s << endl;});
    sort(names.begin(),names.end(),getOrder<string>(byStringLength, less<int>()));
    for_each(names.begin(),names.end(),[](const string& s){cout << s << endl;});
    sort(names.begin(),names.end(),getOrder<string>(byStringLength, greater<int>()));
    for_each(names.begin(),names.end(),[](const string& s){cout << s << endl;});
    return 0;
}