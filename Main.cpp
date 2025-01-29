#include <iostream>
#include "BigReal.h"

int main() {
    BigReal a("-70.12");
    BigReal b("-30");
    bool d = (a < b);
    std::cout << d << std::endl;
    return 0;
}