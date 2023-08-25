#include <functional>
#include <string>

using namespace std;

auto
is_even(int u){ return u%2 == 0;}

struct EvenNumber {
    auto
    operator() (int u){ return u%2 == 0;}

};
template <class T,class Iterator>
auto
kosullu_say(Iterator begin,Iterator end,function<bool(const T&)> pred){
    auto counter = int();
    for(Iterator it=begin;it!=end;++it){
        if(pred(*it)) ++counter;
    }
    return counter;
}

int main(){
    function<bool(int)> fun;
    fun = [](int u){ return u%2 == 0;};
    fun = is_even;
    fun = EvenNumber();
    function<bool(string)> gun;
    gun = &string::empty;
    string m("test");
    m.empty(); // empty(&m);
    gun(m);
    vector<string> names { "", "ali", "zeki", "zehra", ""};
    count_if(names.begin(),names.end(),gun);
    return 0;
}