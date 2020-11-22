#include <iostream>
#include "../../include/app/app.hpp"


int main () {
    Leaf::Greeter greeter;
    std::cout << greeter.greeting() << std::endl;
    return 0;
}
