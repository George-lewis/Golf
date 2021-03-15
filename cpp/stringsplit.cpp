// It splits strings into 4 parts
// Made because someone on the internet said this is difficult

#include <string>
#include <iostream>

void quadsplit(std::string &in, std::string &a, std::string &b, std::string &c, std::string &d) {
    int len = in.length();
    int part = len / 4;
    a = in.substr(0 * part, part);
    b = in.substr(1 * part, part);
    c = in.substr(2 * part, part);
    if (len % 2 == 0) {
        d = in.substr(3 * part, part);
    } else {
        d = in.substr(3 * part);
    }
}

int main() {
    std::cout << "Input a string: ";
    std::string str, a, b, c, d;
    std::getline(std::cin, str);
    quadsplit(str, a, b, c, d);
    std::cout << '[' << a << ']' << " ; " << '[' << b << ']' << " ; " << '[' << c << ']' << " ; " << '[' << d << ']' << std::endl;
}