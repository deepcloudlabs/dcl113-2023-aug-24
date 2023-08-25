#include "city.h"
#include "country.h"
#include "world-util.h"

#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <numeric>

using namespace std;
using namespace world;

map<int, shared_ptr<city>> cities;
map<string, shared_ptr<country>> countries;

int main() {
    create_world();

    auto continentCountriesReducer = [](auto &&continentCountries, auto &entry) {
        auto country = entry.second;
        auto continent = country->continent;
        auto not_found = continentCountries.end();
        auto iterator = continentCountries.find(continent);
        if (iterator == not_found) continentCountries[continent] = vector<shared_ptr<world::country>>();
        continentCountries[continent].push_back(country);
        return continentCountries;
    };

    auto countriesOfContinents = accumulate(countries.begin(), countries.end(),
                                            map<string, vector<shared_ptr<country>>>(), continentCountriesReducer);

    for (auto &entry: countriesOfContinents) {
        cout << entry.first << endl;
        for (auto &eachCountry: entry.second) {
            cout << *eachCountry << endl;
        }
        cout << endl;
    }

    return 0;
}