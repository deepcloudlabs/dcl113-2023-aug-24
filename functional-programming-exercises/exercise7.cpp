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

int main(int argc, char* argv[]){
    create_world();

	// TODO: Find cities with the min and the max population in each country

    return 0;
}