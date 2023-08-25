#include "city.h"
#include "country.h"
#include "world-util.h"

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

template <class E,class T>
struct statistics {
    E min_element;
    E max_element;
    T min;
    T max;
    int numberOfSamples;
    statistics() : numberOfSamples(0) {}
    auto add_sample(E sample,T sampleValue){
        if (numberOfSamples == 0) {
            min = sampleValue;
            min_element = sample;
            max = sampleValue;
            max_element = sample;
        }
        numberOfSamples++;
        if (min > sampleValue) {
            min = sampleValue;
            min_element = sample;
        } else if (max < sampleValue) {
            max = sampleValue;
            max_element = sample;
        }
        return *this;
    }
};

ostream& operator<<(ostream& out,const statistics<shared_ptr<city>,int>& stats){
    if (stats.min_element.get()==nullptr) {
        out << "No body lives in this country!" ;
    }else{
        out << "statistics [ "
            << stats.min_element->name
            << " ( " << stats.min << " )"
            << ",  " << stats.max_element->name
            << " ( " << stats.max << " )"
            << " ]";
    }
    return out;
}

typedef statistics<shared_ptr<city>, int> CityPopulationStatistics;
typedef shared_ptr<city> SharedPtrCity;

int main(int argc, char* argv[]){
    create_world();

	// Find cities with the min and the max population in each country
    for (auto &entry: countries) {
        auto this_country = entry.second;
        auto country_cities = this_country->cities;
        auto statisticsReducer = [](auto&& cityPopulationStatistics,auto &a_city)  {
            return cityPopulationStatistics.add_sample(a_city,a_city->population);
        };
        auto populationStatistics = accumulate(country_cities.begin(), country_cities.end(), CityPopulationStatistics(), statisticsReducer);
        cout << this_country->name << "'s statistics ==> \t" ;
        cout << populationStatistics << endl;
    }
    return 0;
}