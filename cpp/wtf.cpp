/////////////////////////////////////////////////////////////
//                    What on earth...                     //
// https://twitter.com/zygoloid/status/1366917418354761728 //
/////////////////////////////////////////////////////////////

#include <iostream>

void foo(int &&x) {
    std::cout << "ok" << std::endl;
}

int main() {
    int i = 1234;
    float j = 5.4;

    foo(i); // does not compile
    foo(j); // does compile
}