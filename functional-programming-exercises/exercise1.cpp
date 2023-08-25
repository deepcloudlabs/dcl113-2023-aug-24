#include "city.h"
#include "country.h" 
#include "world-util.h" 

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <numeric>

using namespace std;
using namespace world;

map<int,shared_ptr<city>> cities;
map<string,shared_ptr<country>> countries;
void print_continent(const string& continent){
    cout << continent << "\t" ;
}
int main(int argc, char* argv[]){
	create_world();
    auto continentReducer = [](auto&& conts,auto& entry){
        auto country = entry.second;
        conts.insert(country->continent);
        return conts;
    };
    // reduce
    auto continents = accumulate(countries.begin(),countries.end(),set<string>(),continentReducer);
    for_each(continents.begin(),continents.end(),print_continent);
	cout << endl << "done." << endl;
    return 0;
}