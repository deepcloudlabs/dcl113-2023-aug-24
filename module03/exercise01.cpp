#include <iostream>

auto
factorial(int n){
    if (n == 0){
        return 1; // deduction -> int
    } else {
        return factorial(n-1) * n ;
    }
}

/*
auto
factorial2(int n){
    if (n > 1){
        return factorial2(n-1) * n ;
    } else {
        return 1; // deduction -> int
    }
}
*/
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
