#include "city.h"
#include "country.h"
#include "world-util.h"

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <parallel/algorithm>
#include <numeric>

using namespace std;
using namespace world;

map<int, shared_ptr<world::city>> cities;
map<std::string, shared_ptr<world::country>> countries;

void print_continent_country_counts(const pair<string,int>& entry){
    cout << entry.first << ": " << entry.second << endl ;
}
int main(int argc, char *argv[]) {
    create_world();
    auto groupingByContinentCounter = [](auto&& groupByCounting, auto& entry){
        ++groupByCounting[entry.second->continent];
        return groupByCounting;
    };
    // reduce
    map<string,int> numOfCountriesByContinent = accumulate(countries.begin(),countries.end(),map<string,int>(),groupingByContinentCounter);
    for_each(numOfCountriesByContinent.begin(),numOfCountriesByContinent.end(),print_continent_country_counts);
    return 0;
}