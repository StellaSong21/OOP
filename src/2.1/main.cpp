//
// Created by lenovo on 2019/5/12.
//
#include <iostream>
#include "header1.h"
#include "header2.h"

int main() {
    std::cout << "x in header1.h: " << header1::x << std::endl;
    std::cout << "x in header2.h: " << header2::x << std::endl;

    std::cout << "y in header1.h: " << header1::y << std::endl;
    std::cout << "y in header2.h: " << header2::y << std::endl;
}
