#include <iostream>
#include <ranges>
#include <array>

using namespace std;

int main() {
    auto is_even = [](int x){
        cout << "[is_even]: " << x << endl;
        return x%2 == 0;
    };
    auto to_cube = [](int u){
        cout << "[to_cube]: " << u << endl;
        return u*u*u;
    };
    array<int,6> numbers{4, 8,  42, 16, 15, 23 };
    for (auto number : numbers | ranges::views::filter(is_even)
                                   | ranges::views::transform(to_cube)){
        cout << "[for loop]: " << number << endl;
    }
    return 0;
}
