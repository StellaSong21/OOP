//
// Created by lenovo on 2019/6/1.
//

#ifndef OOPLAB4_MATRIX_H
#define OOPLAB4_MATRIX_H

#include <string>
#include "BigNum.h"

#define SIZE 3

class Matrix {
    BigNum matrix[SIZE * SIZE];

public:
    Matrix();

    //todo explicit
    explicit Matrix(const std::vector<std::string> &numVector);

    explicit Matrix(const std::string numString[]);

    explicit Matrix(const BigNum bigNum[]);

    explicit Matrix(const BigNum &bigNum);

    ~Matrix();

    std::string tostring(std::string &s) const;

    const Matrix operator+(const Matrix &right) const;

    const Matrix operator-(const Matrix &right) const;

    const Matrix operator*(const Matrix &right) const;

    friend const Matrix operator*(const BigNum &num, const Matrix &right);

    const Matrix operator~() const;

    Matrix &operator+=(const Matrix &);

    Matrix &operator-=(const Matrix &);

    bool equals(const Matrix&) const;
};

#endif //OOPLAB4_MATRIX_H
