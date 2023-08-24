# DCL-113: Functional Programming in C++20

These projects are created as part of the following training: DCL-113 "Functional Programming in C++20"

Please follow the link for the complete training catalog: https://www.deepcloudlabs.com/resources

## C++17'de Fonksiyonel Programlama

C++11 ile birlikte C++'da fonksiyonel programlama yapılabiliniyor. Standard Template Library (STL) ile fonksiyonel programlama birlikte kullanıldığında karmaşık kod parçalarını daha basit ve yalın hale indirgediği söylenebilir. Bu yazıda bu yalınlığı göstermek üzere örnekler sunacağım. Önce problem uzayını tanıtacağım. Yazılarımın çoğunda kullandığım dünya ülkeleri ve şehirlerinden yararlanacağım:

``` cpp
city.h:

#ifndef __city_h__
#define __city_h__

#include "country.h"

#include <string>
#include <memory>
#include <iostream>

namespace world {
 // forward declaration
 struct country;
 struct city;

 struct city {
  int id;
  std::string name;
  std::string country_code; 
  int population;
  std::shared_ptr<world::country> belongs_to;
  
  city(int id,const std::string& name,const std::string& country_code,int population);
 };
  
};

std::ostream& operator<<(std::ostream& out,const world::city& _city); 
#endif
```
city.cpp:
``` cpp
#include "city.h"

namespace world {
 
 city::city(int id,const std::string& name,const std::string& country_code,int population){
  this->id= id;
  this->name= name;
  this->population= population;
  this->country_code= country_code;
 }
   
};

std::ostream& operator<<(std::ostream& out,const world::city& _city){
 out << "city [ id=" << _city.id 
  << ", name=" << _city.name 
  << ", " << *(_city.belongs_to)
  << ", population=" 
  << _city.population 
  << " ]";
 return out;
}  
```

country.h:

``` cpp
#ifndef __country_h__
#define __country_h__

#include "city.h"

#include <vector>
#include <memory>
#include <iostream>
#include <string>

namespace world {
 // forward declaration
 struct city;
 struct country;
 
 struct country {   
  std::string code;
  std::string continent;
  std::string name;
  double surface_area;
  int population;
  double gnp;
  int capital_id;
  std::shared_ptr<world::city> capital;
  std::vector<std::shared_ptr<world::city>> cities;   
  country(const std::string&,const std::string&,const std::string&,int,double,double,int);  
  country(const std::string&,const std::string&,const std::string&,int,double,double,int,std::vector<std::shared_ptr<world::city>>&,std::shared_ptr<world::city>&);  
 };
};
std::ostream& operator<<(std::ostream&,const world::country&);
#endif
```

country.cpp:

``` cpp
#include "country.h"

namespace world {
 country::country(const std::string& code,const std::string& name,const std::string& continent,int population,double surface_area,double gnp,int capital_id){
  this->code= code;
  this->name= name;
  this->continent= continent;
  this->population= population;
  this->surface_area= surface_area;
  this->gnp= gnp;
  this->capital_id= capital_id;
 } 
 country::country(const std::string& code,const std::string& name,const std::string& continent,int population,double surface_area,double gnp,int capital_id,std::vector<std::shared_ptr<world::city>>& cities,std::shared_ptr<world::city>& capital){
  this->code= code;
  this->name= name;
  this->continent= continent;
  this->population= population;
  this->surface_area= surface_area;
  this->gnp= gnp;
  this->capital_id= capital_id;
  this->cities= cities;
  this->capital= capital;
 }
};

std::ostream& operator<<(std::ostream& out,const world::country& _country){
 out << "country [ code=" << _country.code 
  << ", name=" << _country.name 
  << ", population=" << _country.population 
  << ", surface_area=" << _country.surface_area 
  << ", capital=" << _country.capital_id
  << ", # of cities= " << _country.cities.size() 
  << " ]";
 return out; 
}
```

country ve city sınıfları dünya ülke ve şehirlerini modeller. country ve city sınıfları arasında bire-çoklu ve bire-bir bir ilişki bulunuyor:
``` cpp
world-util.h:

#ifndef __world_util_h__
#define __world_util_h__

#include "city.h"
#include "country.h"

#include <memory>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

extern std::map<int,std::shared_ptr<world::city>> cities;
extern std::map<std::string,std::shared_ptr<world::country>> countries;

void create_cities();
void create_countries();
void create_world();

#endif

world-util.cpp:

#include "world-util.h"

void create_cities(){
 std::cout << "Creating cities..." ;
 cities[1]= std::make_shared<world::city>(world::city(1, std::string("Kabul"), std::string("AFG"), 1780000));
        .
        .
        .
 cities[4079]= std::make_shared<world::city>(world::city(4079, std::string("Rafah"), std::string("PSE"), 92020));
 std::cout << "done." << std::endl;  
}

void create_countries(){
 std::cout << "Creating countries..." ;  
 countries[std::string("ABW")]= std::make_shared<world::country>(world::country(std::string("ABW"), std::string("Aruba"), std::string("North America"), 103000, 193.00, 828.00, 129));
        .
        .
        .
 countries[std::string("ZWE")]= std::make_shared<world::country>(world::country(std::string("ZWE"), std::string("Zimbabwe"), std::string("Africa"), 11669000, 390757.00, 5951.00, 4068)); 
 std::cout << "done." << std::endl; 
} 

void create_world(){
 create_cities();
 create_countries(); 
 
 auto linkCityToCountry= [](std::pair<const int,std::shared_ptr<world::city>>& entry) -> void {
  auto city= entry.second.get();
  auto country= countries[city->country_code];
  city->belongs_to = std::make_shared<world::country>(*country);
  country->cities.push_back(std::make_shared<world::city>(*city)); 
 };  
 
 auto linkCapitalCityToCountry= [](std::pair<const std::string,std::shared_ptr<world::country>>& entry) -> void {
  auto country= entry.second.get();
  if (country->capital_id>=0){
   auto capital= cities[country->capital_id];
   country->capital= std::make_shared<world::city>(*capital);   
  }
 }; 
 
 std::for_each(cities.begin(),cities.end(),linkCityToCountry);
 std::for_each(countries.begin(),countries.end(),linkCapitalCityToCountry);
}
```

Artık bu alan modeli üzerinden örnek problemler çözerek hem STL hem de fonksiyonel programlama çalışabiliriz:

1. Dünyadaki kıtaların bir listesini hesaplayalım:

exercise1.cpp:

``` cpp
#include "city.h"
#include "country.h" 
#include "world-util.h" 

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;
using namespace world;

std::map<int,std::shared_ptr<world::city>> cities;
std::map<std::string,std::shared_ptr<world::country>> countries;

int main(int argc, char* argv[]){
 create_world();
 
 auto distinctContinentReducer= [](set<string>& continents, pair<const string,shared_ptr<country>>& entry) -> set<string>&  {
  auto country= entry.second.get();
  continents.insert(country->continent);
  return continents;
 }; 
 
 auto continents= accumulate(countries.begin(),countries.end(),set<string>(), distinctContinentReducer);
 
 for (auto& continent: continents){
  cout << continent << endl; 
 }
  
 return 0;
}
```

Yukarıdaki uygulamayı çalıştırdığımızda aşağıdaki çıktıyı elde ediyoruz:

```
$ ./exercise1
Creating cities...done.
Creating countries...done.
Africa
Antarctica
Asia
Europe
North America
Oceania
South America
```

2. Her bir kıtada kaç ülke olduğunu bulalım:

exercise2.cpp:

``` cpp
#include "city.h"
#include "country.h" 
#include "world-util.h" 

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;
using namespace world;

std::map<int,std::shared_ptr<world::city>> cities;
std::map<std::string,std::shared_ptr<world::country>> countries;

int main(int argc, char* argv[]){
 create_world();
 
 auto countCountriesInContinentReducer= [](map<string,int>& numberOfCountriesInEachContinent, pair<const string,shared_ptr<country>>& entry) -> map<string,int>&  {
  auto country= entry.second.get();
  auto continent= country->continent;
  auto end= numberOfCountriesInEachContinent.end();
  auto iterator= numberOfCountriesInEachContinent.emplace_hint(end,continent,0);
  (iterator->second)++;
  return numberOfCountriesInEachContinent;
 }; 
 
 auto continentCountriesCounter= accumulate(countries.begin(),countries.end(),map<string,int>(),countCountriesInContinentReducer);
 
 for (auto& entry: continentCountriesCounter){
  cout << entry.first << ": " << entry.second << endl; 
 }
  
 return 0;
}
```

Yukarıdaki uygulamayı çalıştırdığımızda aşağıdaki çıktıyı elde ediyoruz:

```
$ ./exercise2
Creating cities...done.
Creating countries...done.
Africa: 58
Antarctica: 5
Asia: 51
Europe: 46
North America: 37
Oceania: 28
South America: 14
```

3. Dünyanın, GNP (Gross National Product)(=Gayri Safi Milli Hasıla) değerine göre en zengin ülkesini bulalım:

exercise3.cpp:

``` cpp
#include "city.h"
#include "country.h" 
#include "world-util.h" 

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;
using namespace world;

std::map<int,std::shared_ptr<world::city>> cities;
std::map<std::string,std::shared_ptr<world::country>> countries;

int main(int argc, char* argv[]){
 create_world();
 
 auto gnpComparator= [](pair<const string,shared_ptr<country>>& left, pair<const string,shared_ptr<country>>& right) -> bool  {
  return left.second->gnp < right.second->gnp;
 }; 
 
 auto richestCountryPair= max_element(countries.begin(),countries.end(),gnpComparator);
 auto richestCountry= *(richestCountryPair->second);
 
 cout << richestCountry << endl; 
  
 return 0;
}
```

Yukarıdaki uygulamayı çalıştırdığımızda aşağıdaki çıktıyı elde ediyoruz:

```
$ ./exercise3
Creating cities...done.
Creating countries...done.
country [ code=USA, name=United States, population=278357000, surface_area=9.36352e+06, capital=3813, # of cities= 274 ]
```

4. Şimdi her kıtanın GNP (Gross National Product)(=Gayri Safi Milli Hasıla) değerine göre en zengin ülkesini bulalım:

``` cpp
exercise4.cpp:

#include "city.h"
#include "country.h" 
#include "world-util.h" 

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;
using namespace world;

std::map<int,std::shared_ptr<world::city>> cities;
std::map<std::string,std::shared_ptr<world::country>> countries;

int main(int argc, char* argv[]){
 create_world();
 
 auto gnpComparator= [](shared_ptr<country>& left, shared_ptr<country>& right) -> bool  {
  return left->gnp < right->gnp;
 }; 
  
 auto richestCountryOfContinentReducer=  [&gnpComparator](map<string,shared_ptr<country>>& richestCountriesOfContinents, pair<const string,shared_ptr<country>>& entry) -> map<string,shared_ptr<country>>&  {
    auto country= entry.second;
    auto continent= country->continent;
    auto richestCountryIterator= richestCountriesOfContinents.find(continent);
       auto richestCountry= richestCountryIterator->second;  
    if (richestCountryIterator==richestCountriesOfContinents.end() || gnpComparator(richestCountry,country) )
  richestCountriesOfContinents[continent]= country;
    return richestCountriesOfContinents;
 }; 
 
 auto richestCountriesOfContinents= accumulate(countries.begin(),countries.end(),map<string,shared_ptr<country>>(),richestCountryOfContinentReducer);

 for (auto& entry: richestCountriesOfContinents){
    cout << entry.first << ": " << *(entry.second) << endl;   
 } 
  
 return 0;
}
```

Yukarıdaki uygulamayı çalıştırdığımızda aşağıdaki çıktıyı elde ediyoruz:

```
$ ./exercise4
Creating cities...done.
Creating countries...done.
Africa: country [ code=ZAF, name=South Africa, population=40377000, surface_area=1.22104e+06, gnp=116729, # of cities= 44 ]
Antarctica: country [ code=ATA, name=Antarctica, population=0, surface_area=1.312e+07, gnp=0, # of cities= 0 ]
Asia: country [ code=JPN, name=Japan, population=126714000, surface_area=377829, gnp=3.78704e+06, # of cities= 248 ]
Europe: country [ code=DEU, name=Germany, population=82164700, surface_area=357022, gnp=2.13337e+06, # of cities= 93 ]
North America: country [ code=USA, name=United States, population=278357000, surface_area=9.36352e+06, gnp=8.5107e+06, # of cities= 274 ]
Oceania: country [ code=AUS, name=Australia, population=18886000, surface_area=7.74122e+06, gnp=351182, # of cities= 14 ]
South America: country [ code=BRA, name=Brazil, population=170115000, surface_area=8.5474e+06, gnp=776739, # of cities= 250 ]
```

5. Her bir kıtadaki ülkelerin listesini alalım:

exercise5.cpp:

``` cpp
#include "city.h"
#include "country.h" 
#include "world-util.h" 

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;
using namespace world;

std::map<int,std::shared_ptr<world::city>> cities;
std::map<std::string,std::shared_ptr<world::country>> countries;

int main(int argc, char* argv[]){
 create_world();
  
 auto continentCountriesReducer= [](map<string,vector<shared_ptr<country>>>& continentCountries, pair<const string,shared_ptr<country>>& entry) -> map<string,vector<shared_ptr<country>>>&  {
  auto country= entry.second;
  auto continent= country->continent;
  auto not_found= continentCountries.end();  
  auto iterator= continentCountries.find(continent);
  if (iterator==not_found) continentCountries[continent]= vector<shared_ptr<world::country>>();
  continentCountries[continent].push_back(country);
  return continentCountries;
 }; 
  
 auto countriesOfContinents= accumulate(countries.begin(),countries.end(),map<string,vector<shared_ptr<country>>>(),continentCountriesReducer);

 for (auto& entry: countriesOfContinents){
    cout << entry.first << endl;   
    for (auto& eachCountry : entry.second){
        cout << *eachCountry << endl;
    }
    cout << endl;
 } 
  
 return 0;
}
```

Yukarıdaki uygulamayı çalıştırdığımızda aşağıdaki çıktıyı elde ediyoruz:

```
$ ./exercise5
Creating cities...done.
Creating countries...done.
Africa
country [ code=AGO, name=Angola, population=12878000, surface_area=1.2467e+06, gnp=6648, continent=Africa, # of cities= 5 ]
.
.
.
country [ code=ZWE, name=Zimbabwe, population=11669000, surface_area=390757, gnp=5951, continent=Africa, # of cities= 6 ]

Antarctica
country [ code=ATA, name=Antarctica, population=0, surface_area=1.312e+07, gnp=0, continent=Antarctica, # of cities= 0 ]
.
.
.
country [ code=SGS, name=South Georgia and the South Sandwich Islands, population=0, surface_area=3903, gnp=0, continent=Antarctica, # of cities= 0 ]

Asia
country [ code=AFG, name=Afghanistan, population=22720000, surface_area=652090, gnp=5976, continent=Asia, # of cities= 4 ]
.
.
.
country [ code=YEM, name=Yemen, population=18112000, surface_area=527968, gnp=6041, continent=Asia, # of cities= 6 ]

Europe
country [ code=ALB, name=Albania, population=3401200, surface_area=28748, gnp=3205, continent=Europe, # of cities= 1 ]
.
.
.
country [ code=YUG, name=Yugoslavia, population=10640000, surface_area=102173, gnp=17000, continent=Europe, # of cities= 8 ]

North America
country [ code=ABW, name=Aruba, population=103000, surface_area=193, gnp=828, continent=North America, # of cities= 1 ]
.
.
.
country [ code=VIR, name=Virgin Islands, U.S., population=93000, surface_area=347, gnp=0, continent=North America, # of cities= 1 ]

Oceania
country [ code=ASM, name=American Samoa, population=68000, surface_area=199, gnp=334, continent=Oceania, # of cities= 2 ]
.
.
.
country [ code=WSM, name=Samoa, population=180000, surface_area=2831, gnp=141, continent=Oceania, # of cities= 1 ]

South America
country [ code=ARG, name=Argentina, population=37032000, surface_area=2.7804e+06, gnp=340238, continent=South America, # of cities= 57 ]
.
.
.
country [ code=VEN, name=Venezuela, population=24170000, surface_area=912050, gnp=95023, continent=South America, # of cities= 41 ]
```

6. Her bir kıta için minimum, maksimum ve ortalama nüfus sayılarını hesaplayalım:

exercise6.cpp:

``` cpp
#include "city.h"
#include "country.h" 
#include "world-util.h" 

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;
using namespace world;

std::map<int,std::shared_ptr<world::city>> cities;
std::map<std::string,std::shared_ptr<world::country>> countries;

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
std::ostream& operator<<(std::ostream& out,const statistics<T>& stats){
 out << "statistics [ number of samples= " << stats.numberOfSamples 
     << ", minimum=" << stats.minimum 
     << ", maximum=" << stats.maximum
     << ", sum=" <<stats.sum
     << ", average=" << stats.average()
     << " ]";
 return out;  
}

int main(int argc, char* argv[]){
 create_world();
  
 auto statisticsReducer=  [](map<string,shared_ptr<statistics<int>>>& continentStatistics, pair<const string,shared_ptr<country>>& entry) -> map<string,shared_ptr<statistics<int>>>&  {
  auto country= entry.second;
  auto continent= country->continent;
  auto continentStatisticsIterator= continentStatistics.find(continent);
  if (continentStatisticsIterator==continentStatistics.end())
   continentStatistics[continent]= make_shared<statistics<int>>(statistics<int>(country->population));
  else {   
   auto continentStat= continentStatisticsIterator->second;
   auto countryPopulation= country->population;
   if (continentStat->minimum > countryPopulation) continentStat->minimum= countryPopulation;
   if (continentStat->maximum < countryPopulation) continentStat->maximum= countryPopulation;
   continentStat->sum += countryPopulation;
   continentStat->numberOfSamples++;  
  }
     return continentStatistics;
 }; 
 
 auto continentStatistics= accumulate(countries.begin(),countries.end(),map<string,shared_ptr<statistics<int>>>(),statisticsReducer);

 for (auto& entry: continentStatistics){
    cout << entry.first << ": " << *(entry.second) << endl;   
 } 
  
 return 0;
}
```

Yukarıdaki uygulamayı çalıştırdığımızda aşağıdaki çıktıyı elde ediyoruz:

```
$ ./exercise6
Creating cities...done.
Creating countries...done.
Africa: statistics [ number of samples= 58, minimum=0, maximum=111506000, sum=7.84475e+08, average=1.35254e+07 ]
Antarctica: statistics [ number of samples= 5, minimum=0, maximum=0, sum=0, average=0 ]
Asia: statistics [ number of samples= 51, minimum=286000, maximum=1277558000, sum=3.70503e+09, average=7.26476e+07 ]
Europe: statistics [ number of samples= 46, minimum=1000, maximum=146934000, sum=7.30075e+08, average=1.58712e+07 ]
North America: statistics [ number of samples= 37, minimum=7000, maximum=278357000, sum=4.82993e+08, average=1.30539e+07 ]
Oceania: statistics [ number of samples= 28, minimum=0, maximum=18886000, sum=3.04012e+07, average=1.08576e+06 ]
South America: statistics [ number of samples= 14, minimum=2000, maximum=170115000, sum=3.4578e+08, average=2.46986e+07 ]
```

7. Ülkelerin, en az nüfusa ve en çok nüfusa sahip şehirlerini bulalım:

exercise7.cpp:

``` cpp
#include "city.h"
#include "country.h" 
#include "world-util.h" 

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;
using namespace world;

std::map<int,std::shared_ptr<world::city>> cities;
std::map<std::string,std::shared_ptr<world::country>> countries;

template <class E,class T>
struct statistics {
 E min_element;
 E max_element; 
 T min;
 T max;
 int numberOfSamples;
 statistics() : numberOfSamples(0) {}
};

std::ostream& operator<<(std::ostream& out,const statistics<shared_ptr<city>,int>& stats){
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

 for (auto& entry: countries){
  auto this_country= entry.second;
  auto country_cities= this_country->cities;
  auto statisticsReducer=  [](statistics<shared_ptr<city>,int>& cityPopulationStatistics, shared_ptr<city>& a_city) -> statistics<shared_ptr<city>,int>&  {
   auto cityPopulation= a_city->population;
   if (cityPopulationStatistics.numberOfSamples==0){
      cityPopulationStatistics.min= cityPopulation;
      cityPopulationStatistics.min_element= a_city; 
      cityPopulationStatistics.max= cityPopulation;
      cityPopulationStatistics.max_element= a_city;     
   }
   cityPopulationStatistics.numberOfSamples++;
   if (cityPopulationStatistics.min>cityPopulation){
      cityPopulationStatistics.min= cityPopulation;
      cityPopulationStatistics.min_element= a_city; 
   }
   if (cityPopulationStatistics.max>cityPopulation){
      cityPopulationStatistics.max= cityPopulation;
      cityPopulationStatistics.max_element= a_city; 
   }
   return cityPopulationStatistics;
  };     
  auto populationStatistics= accumulate(country_cities.begin(),country_cities.end(),statistics<shared_ptr<city>,int>(),statisticsReducer);
  cout << this_country->name << "'s statistics:" << endl;
     cout << populationStatistics << endl;
 } 
  
 return 0;
}

Yukarıdaki uygulamayı çalıştırdığımızda aşağıdaki çıktıyı elde ediyoruz:

```
$ ./exercise7
Creating cities...done.
Creating countries...done.
Aruba's statistics:
statistics [ Oranjestad ( 29034 ),  Oranjestad ( 29034 ) ]
Afghanistan's statistics:
statistics [ Mazar-e-Sharif ( 127800 ),  Mazar-e-Sharif ( 127800 ) ]
Angola's statistics:
statistics [ Namibe ( 118200 ),  Namibe ( 118200 ) ]
.
.
.
South Africa's statistics:
statistics [ Ladysmith ( 89292 ),  Ladysmith ( 89292 ) ]
Zambia's statistics:
statistics [ Luanshya ( 118100 ),  Luanshya ( 118100 ) ]
Zimbabwe's statistics:
statistics [ Gweru ( 128037 ),  Gweru ( 128037 ) ]
```

8. En kalabalık başkenti bulalım:

exercise8.cpp:

``` cpp
#include "city.h"
#include "country.h" 
#include "world-util.h" 

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;
using namespace world;

std::map<int,std::shared_ptr<world::city>> cities;
std::map<std::string,std::shared_ptr<world::country>> countries;

int main(int argc, char* argv[]){
 create_world();
  
 auto highPopulatedCapitalReducer=  [](shared_ptr<city>& highPopulatedCapital, pair<const string,shared_ptr<country>>& entry) -> shared_ptr<city>&  {
  auto capital= entry.second->capital;
  if(capital==nullptr) return highPopulatedCapital;
  auto population= capital->population;
  if (highPopulatedCapital==nullptr){
     highPopulatedCapital= capital;
  } else  if (highPopulatedCapital->population<population) {
     highPopulatedCapital= capital;
                }
         return highPopulatedCapital;
 }; 
 
 auto highPopulatedCapital = accumulate(countries.begin(),countries.end(),shared_ptr<city>(nullptr),highPopulatedCapitalReducer).get();

        cout << *highPopulatedCapital << endl;   
  
        return 0;
}
```

Yukarıdaki uygulamayı çalıştırdığımızda aşağıdaki çıktıyı elde ediyoruz:

```
$ ./exercise8
Creating cities...done.
Creating countries...done.
city [ id=2331, name=Seoul, country [ code=KOR, name=South Korea, population=46844000, surface_area=99434, gnp=320749, continent=Asia, # of cities= 0 ], population=9981619 ]
```

## Ranges

Yukarıdaki örnek problemlerin çözümünde STL kütüphanesini ve fonksiyonel programlamayı kullanmış olmak, kodlama üretkenliğimizi iyileştirmiş olsa da hala her çözümde tekrar ettiğimiz noktalar bulunuyor. Üstelik STL torbalaları üzerinde yaptığımız işlemlerin bellek kullanımı ve çalışma zamanı başarımında problemler bulunuyor. Bu problemlerin çözümü için geliştirilen iki kütüphane bulunuyor:

- Boost Range 2.0
- Range 3.0

İkinci çözüm Eric Niebler'e ait ve C++20 standardına eklenmek üzere kabul edilmiş durumda. 2020 yılında çıkacak C++'ın yeni sürümünde hazır olarak ulaşacağımız bir çözüm sunuyor. Eğer C++14 ve sonrası bir C++ derleyiciniz varsa şimdiden kullanabilirsiniz. Şimdi yukarıda çözdüğümüz problemlerin bir kaçını tekrar ele alalım ve Range v3 ile tekrar çözelim:

1. Asya kıtasındaki ülkelerin bir listesini almak istiyoruz:

ranges1.cpp:

``` cpp
#include "city.h"
#include "country.h"
#include "world-util.h"

#include <vector>
#include <functional>
#include <map>
#include <iostream>
#include <string>
#include <memory>

#include <range/v3/core.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/map.hpp>
#include <range/v3/view/view.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/algorithm/for_each.hpp>

using namespace std;
using namespace world;
using namespace ranges::v3;

std::map<int,std::shared_ptr<world::city>> cities;
std::map<std::string,std::shared_ptr<world::country>> countries;

int main(int argc, char* argv[]){
    create_world();
    auto is_asian = [](shared_ptr<country> &a_country) -> bool {
        return a_country->continent.compare("Asia") == 0;
    };
    const auto asian_countries=countries | view::values | view::filter(is_asian) | to_vector ;
    for (auto& a_country : asian_countries)
        cout << *a_country << endl;   
    return 0;
}
```

2. Ülkelerin adlarından oluşan bir liste oluşturmak istiyoruz:

ranges2.cpp:

``` cpp
#include "city.h"
#include "country.h" 
#include "world-util.h" 

#include <vector>
#include <functional>
#include <map>
#include <iostream>
#include <string>
#include <memory>

#include <range/v3/core.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/map.hpp>
#include <range/v3/view/view.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/algorithm/for_each.hpp>

using namespace std;
using namespace world;
using namespace ranges::v3;

std::map<int,std::shared_ptr<world::city>> cities;
std::map<std::string,std::shared_ptr<world::country>> countries;

int main(int argc, char* argv[]){
    create_world();
    auto country_name_mapper = [](shared_ptr<country> &a_country) -> string {
        return a_country->name ;
    };

    const auto countries_names= countries | view::values | view::transform(country_name_mapper) | to_vector ;

    for (auto& country_name : countries_names)
        cout << country_name << endl; 

    return 0;
}
```

3. Dünya ülkelerini, GNP değerleri 25000'nin altında olan ülkeler ve 25000'nin üstünde olan ülkeler olarak iki sınıfta gruplayalım:

ranges3.cpp:

```
#include "city.h"
#include "country.h" 
#include "world-util.h" 

#include <vector>
#include <functional>
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <range/v3/core.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/map.hpp>
#include <range/v3/view/group_by.hpp>
#include <range/v3/view/all.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/view.hpp>
#include <range/v3/action/sort.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/algorithm/for_each.hpp>

using namespace std;
using namespace world;
using namespace ranges;

std::map<int,std::shared_ptr<world::city>> cities;
std::map<std::string,std::shared_ptr<world::country>> countries;

auto group_by_gnp() {
   return 
   view::group_by(
          [](shared_ptr<country> a,shared_ptr<country> b) -> bool {
              auto is_a_rich= a->gnp >= 25000.0 ; 
              auto is_b_rich= b->gnp >= 25000.0 ; 
              return is_a_rich == is_b_rich ;
          }
   );
}

auto order_by_gnp = [](shared_ptr<country> &a,shared_ptr<country> &b) -> bool {
     return a->gnp < b->gnp ;
};

int main(int argc, char* argv[]){

    create_world();
    auto all= countries | view::values | to_vector | action::sort(order_by_gnp);
    auto rich_poor_countries= all | group_by_gnp() ;
    RANGES_FOR(auto cluster, rich_poor_countries)
    {
        RANGES_FOR(auto c, cluster)
        {
            cout << *c << endl;
        }
        cout << endl;
    }

    return 0;
}
```
