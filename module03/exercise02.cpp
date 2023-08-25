#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include "employee.h"

template<int Age>
bool older_than(const employee &emp) {
    return (2023 - emp.getBirthYear()) > Age;
}

struct OlderThan {

    auto
    operator()(const employee &emp) -> bool {
        return (2023 - emp.getBirthYear()) > limit;
    }

    explicit OlderThan(int limit=42) : limit(limit) {}

private:
        int limit;
};

template <int Limit>
struct OlderThan2 {

    auto
    operator()(const employee &emp) -> bool {
        return (2023 - emp.getBirthYear()) > Limit;
    }

};
int main() {
    vector<employee> employees{
            {"kate",   "austen", employee::department_t::it,      employee::gender_t::female, 200'000, "tr1", 1986},
            {"james",  "sawyer", employee::department_t::hr,      employee::gender_t::male,   100'000, "tr2", 1976},
            {"juliet", "burke",  employee::department_t::sales,   employee::gender_t::female, 100'000, "tr3", 1996},
            {"john",   "locke",  employee::department_t::finance, employee::gender_t::male,   200'000, "tr4", 1956},
            {"ben",    "linus",  employee::department_t::it,      employee::gender_t::male,   100'000, "tr5", 1966}
    };
    auto counter = count_if(employees.begin(), employees.end(), older_than < 50 > ); // HoF
    cout << counter << endl;
    counter = count_if(employees.begin(), employees.end(), older_than < 40 > ); // HoF
    cout << counter << endl;
    counter = count_if(employees.begin(), employees.end(), OlderThan(30) ); // HoF
    cout << counter << endl;
    counter = count_if(employees.begin(), employees.end(), OlderThan2<30>() ); // HoF
    cout << counter << endl;
    auto limit = 30;
    counter = count_if(employees.begin(), employees.end(), [&limit](const employee &emp) -> bool {
        return (2023 - emp.getBirthYear()) > limit;
    } ); // HoF
    cout << counter << endl;

    return 0;
}
