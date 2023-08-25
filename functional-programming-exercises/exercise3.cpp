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

    // TODO:  Find the richest country wrt GNP
	
    return 0;
}