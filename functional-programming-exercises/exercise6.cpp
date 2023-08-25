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

template <class T>
struct statistics {
    T minimum;
    T maximum;
    double sum;
    int numberOfSamples;
    statistics() : sum(0), numberOfSamples(0) {}
    statistics(T value) : sum(value), numberOfSamples(1),minimum(value),maximum(value) {}
    double average() const {
        if (numberOfSamples==0) return 0.0;
        return sum/numberOfSamples;
    }
};

template <class T>
ostream& operator<<(ostream& out,const statistics<T>& stats){
    out << "statistics [ number of samples= " << stats.numberOfSamples
        << ", minimum=" << stats.minimum
        << ", maximum=" << stats.maximum
        << ", sum=" <<stats.sum
        << ", average=" << stats.average()
        << " ]";
    return out;
}

using statistics_int = statistics<int> ;
using statistics_int_ptr = shared_ptr<statistics_int> ;

int main(int argc, char* argv[]){
    create_world();

    // TODO: Find the min, the max, and the average population at each continent

    return 0;
}