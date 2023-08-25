#include <iostream>
#include <functional>

using namespace std;

void print(const int v){ cout << v << "\t"; }
int main() {
    function<bool(int, int)> fun = less<int>();
    cout << (fun(2, 4) ? "true" : "false") << endl;
    function<bool(int)> less_than_20 = bind(fun,placeholders::_1,20);

    vector<int> numbers{4, 8,  42, 16, 15, 23 };
    auto counter = count_if(numbers.begin(), numbers.end(),less_than_20);
    cout << "counter: " << counter << endl;
    for_each(numbers.begin(), numbers.end(), print);
    auto ascending_order= less<int>();
    sort(numbers.begin(), numbers.end(),ascending_order);
    cout << endl;
    for_each(numbers.begin(), numbers.end(), print);
    cout << endl;
    auto descending_order = bind(ascending_order,placeholders::_2,placeholders::_1);
    auto descending_order_lambda = [ascending_order](int x,int y){
        return ascending_order(y,x);
    };
    sort(numbers.begin(), numbers.end(),descending_order);
    cout << endl;
    for_each(numbers.begin(), numbers.end(), print);
    cout << endl;
    sort(numbers.begin(), numbers.end(),descending_order_lambda);
    for_each(numbers.begin(), numbers.end(), print);
    cout << endl;
    return 0;
}
