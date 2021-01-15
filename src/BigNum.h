//
// Created by lenovo on 2019/6/1.
//

#ifndef OOPLAB4_BIGNUM_H
#define OOPLAB4_BIGNUM_H

#include <sstream>
#include <vector>
#include <string>

/*
 * 1.vector<int>, vector[0]:[0000,9999]; vector[1]:[0000,9999]; ...; vector[n]:[0000,9999] ... 
 * 3.可以直接打印
 * 4.两个int相乘还在int范围内 2^13 * 2^13 = 2^26
 * 5.小端存储
 */
#define MAX 9999

class BigNum {
    std::vector<int> num;
    bool sign;
    int length;

    /*字符串转化为整数*/
    void str2int(const std::string &string_temp, int &int_temp);

    void int2str(const int &int_temp, std::string &string_temp, bool flag) const ;

    /*每一位都带符号进行加法运算，最终结果保存在result中，每一位可能有不同的符号*/
    void add(const std::vector<int> &left, bool sign1, const std::vector<int> &right, bool sign2,
             std::vector<int> &) const;

    void mutiply(const std::vector<int> &left, const std::vector<int> &right,
                 std::vector<int> &) const;

    bool equalsZero() const;

    /*使每一位都与最高位的符号相同*/
    void uniform(const std::vector<int> &temp, std::vector<int> &result);

public:
    BigNum();

    explicit BigNum(std::vector<int> const &, bool sign = true);

    /*将字符串解析为一个整数的向量，小端存储法*/
    explicit BigNum(const std::string &s);

    ~BigNum();

    std::string tostring(std::string &s) const;

    const BigNum operator+(const BigNum &) const;

    const BigNum operator-(const BigNum &) const;

    const BigNum operator*(const BigNum &right) const;

//    friend const BigNum operator*(const BigNum &v, const BigNum &right);

    BigNum &operator+=(const BigNum &);

    BigNum &operator-=(const BigNum &);

    bool equals(const BigNum&) const;
};


/*
 * 1.int[10], int[0]:[0000,INT_MAX]; int[1]:[0000,INT_MAX]; ...; int[10]:[0000,INT_MAX]
 * 2.2^128 = 3.4028236692093846346337460743177e+38 = 340 * 10^36
 * 3.need longlong to calculate (int * int)
 */
// #define LEN 4
// #define MAX __INT_MAX__

#endif //OOPLAB4_BIGNUM_H
