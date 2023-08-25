#include "city.h"
#include "world-util.h"

#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;
using namespace world;

map<int,shared_ptr<city>> cities;
map<string,shared_ptr<country>> countries;


int main(int argc, char* argv[]){
    create_world();
    auto compareByGnpAsc = [](auto &firstEntry,auto &secondEntry){
        return firstEntry.second->gnp < secondEntry.second->gnp;
    };
    // reduce
    auto richest_country_entry =
    max_element(countries.begin(),countries.end(),compareByGnpAsc);
    cout << richest_country_entry->second->name << ", "
         << richest_country_entry->second->gnp
         << endl;
    auto poor_country_entry =
            min_element(countries.begin(),countries.end(),compareByGnpAsc);
    cout << poor_country_entry->second->name << ", "
         << poor_country_entry->second->gnp
         << endl;
    return 0;
}