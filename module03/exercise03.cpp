#include <iostream>
#include <vector>
#include <parallel/algorithm>
#include <parallel/numeric>

using namespace std;


int main() {
    vector<int> numbers{1,2,3,4,5,6,7,8,9,10};
    vector<int> even_numbers;
    vector<int> cubed_numbers;
    // filter
    auto even_number = [](int x){return x%2 == 0;};
    copy_if(numbers.begin(),numbers.end(), back_inserter(even_numbers),even_number);
    // map
    auto to_cube = [](int x){return x*x*x;};
    transform(even_numbers.begin(),even_numbers.end(), back_inserter(cubed_numbers),to_cube);
    // reduce
    auto solution =
    accumulate(cubed_numbers.begin(),cubed_numbers.end(),int(),plus<int>());
    cout << "solution: " << solution << endl;
    return 0;
}
