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

auto
byBirthYear(const employee& emp){
    return emp.getBirthYear();
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


template<class T,class OrderByFirst,class CompareByFirst,class OrderBySecond,class CompareBySecond>
decltype(auto)
getOrderThen(OrderByFirst orderByFirst, CompareByFirst compareByFirst,OrderBySecond orderBySecond, CompareBySecond compareBySecond){ // Generic HoF
    return [orderByFirst,compareByFirst,orderBySecond,compareBySecond](const T& first,const T& second) -> bool { // Pure Function
         if ( orderByFirst(first) == orderByFirst(second) )
            return compareBySecond(orderBySecond(first),orderBySecond(second));
         return compareByFirst(orderByFirst(first),orderByFirst(second));
    } ;
}
int main() {
    vector<employee> employees{
            {"kate",   "austen", employee::department_t::it,      employee::gender_t::female, 200'000, "tr1", 1986},
            {"james",  "sawyer", employee::department_t::hr,      employee::gender_t::male,   100'000, "tr2", 1976},
            {"juliet", "burke",  employee::department_t::sales,   employee::gender_t::female, 100'000, "tr3", 1996},
            {"john",   "locke",  employee::department_t::finance, employee::gender_t::male,   200'000, "tr4", 1956},
            {"ben",    "linus",  employee::department_t::it,      employee::gender_t::male,   100'000, "tr5", 1966}
    };
    // HoF: sort
    // sorting ? criteria
    for_each(employees.begin(), employees.end(), print_employee); // C-like function
    sort(employees.begin(), employees.end(), getOrder<employee>(bySalary, less<>()));
    cout << endl;
    for_each(employees.begin(), employees.end(), print_employee); // C-like function
    cout << endl;
    sort(employees.begin(), employees.end(), getOrder<employee>(bySalary, greater<>()));
    for_each(employees.begin(), employees.end(), print_employee); // C-like function
    vector<string> names {"jack", "james", "ben", "sun", "jin", "kate"};
    auto byStringLength = [](const string &s) { return s.size(); };
    sort(names.begin(), names.end(), getOrder<string>(byStringLength, inAscendingOrder<int>));
    for_each(names.begin(),names.end(),[](const string& s){cout << s << endl;});
    sort(names.begin(),names.end(),getOrder<string>(byStringLength, inDescendingOrder<int>));
    for_each(names.begin(),names.end(),[](const string& s){cout << s << endl;});
    sort(names.begin(),names.end(),getOrder<string>(byStringLength, less<>()));
    for_each(names.begin(),names.end(),[](const string& s){cout << s << endl;});
    sort(names.begin(),names.end(),getOrder<string>(byStringLength, greater<>()));
    for_each(names.begin(),names.end(),[](const string& s){cout << s << endl;});
    cout << endl;
    sort(employees.begin(), employees.end(), getOrderThen<employee>(bySalary, less<double>(), byBirthYear, less<int>()));
    for_each(employees.begin(), employees.end(), print_employee); // C-like function
    return 0;
}
