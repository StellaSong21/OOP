//
// Created by lenovo on 2019/6/1.
//

#include <malloc.h>
#include <iostream>
#include "Matrix.h"

using namespace std;

Matrix::Matrix() {
}

Matrix::Matrix(const std::vector<std::string> &vector) {
    for (int i = 0; i < SIZE * SIZE; i++) {
        matrix[i] = BigNum(vector[i]);
    }
}

Matrix::Matrix(const string numString[]) {
    for (int i = 0; i < SIZE * SIZE; i++) {
        matrix[i] = BigNum(numString[i]);
    }
}


Matrix::Matrix(const BigNum bigNum[]) {
    for (int i = 0; i < SIZE * SIZE; i++) {
        this->matrix[i] = bigNum[i];
    }
}


Matrix::Matrix(const BigNum &bigNum) {
    for (int i = 0; i < SIZE * SIZE; i++) {
        this->matrix[i] = (i % 4 == 0) ? bigNum : BigNum("0");
    }
}


Matrix::~Matrix() {
    //delete []matrix
}

// 临时变量
const Matrix Matrix::operator+(const Matrix &right) const {
    BigNum bigNum[SIZE * SIZE];
    for (int i = 0; i < SIZE * SIZE; i++) {
        bigNum[i] = this->matrix[i] + right.matrix[i];
    }
    return Matrix(bigNum);
}

const Matrix Matrix::operator-(const Matrix &right) const {
    BigNum bigNum[SIZE * SIZE];
    for (int i = 0; i < SIZE * SIZE; i++) {
        bigNum[i] = this->matrix[i] - right.matrix[i];
    }
    return Matrix(bigNum);
}

const Matrix Matrix::operator*(const Matrix &right) const {
    BigNum bigNum[SIZE * SIZE];
    for (auto &i : bigNum) //initialize to 0
    {
        i = BigNum("0");
    }
    for (int i = 0; i < SIZE * SIZE; i++) {
        int row = i / SIZE;
        int col = i % SIZE;
        for (int j = 0; j < SIZE; j++) {
            bigNum[i] += this->matrix[row * SIZE + j] * right.matrix[col + j * SIZE];
        }
    }
    return Matrix(bigNum);
}

const Matrix operator*(const BigNum &num, const Matrix &right) {
    BigNum bigNum[SIZE * SIZE];
    for (int i = 0; i < SIZE * SIZE; i++) {
        bigNum[i] = right.matrix[i] * num;
    }
    return Matrix(bigNum);
}

const Matrix Matrix::operator~() const {
    BigNum bigNum[SIZE * SIZE];
    for (int i = 0; i < SIZE * SIZE; i++) {
        bigNum[i] = this->matrix[i < SIZE * SIZE - 1 ? i * SIZE % (SIZE * SIZE - 1) : i];
    }
    return Matrix(bigNum);
}

Matrix &Matrix::operator+=(const Matrix &right) {
    for (int i = 0; i < SIZE * SIZE; i++) {
        this->matrix[i] += right.matrix[i];
    }
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &right) {
    for (int i = 0; i < SIZE * SIZE; i++) {
        this->matrix[i] -= right.matrix[i];
    }
    return *this;
}

std::string Matrix::tostring(std::string &s) const {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            string m;
            s.append((this->matrix)[i * SIZE + j].tostring(m) + "\t");
        }
        if (i < SIZE - 1)
            s.append("\n");
    }
    return s;
}

bool Matrix::equals(const Matrix &matrixs) const {
    for (int i = 0; i < SIZE * SIZE; i++) {
        if (!(matrixs.matrix[i]).equals(this->matrix[i])) {
            cout << i << endl;
            return false;
        }
    }

    return true;
}


