//
// Created by lenovo on 2019/5/12.
//

#include <iostream>
#include "header1.h"
#include "header2.h"

#define F(x) std::cout << #x " = " << x << std::endl

int main() {
    using namespace header;
    F(a);
    F(b);
    F(c);
}
