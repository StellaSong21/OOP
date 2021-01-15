//
// Created by lenovo on 2019/6/1.
//

#include "BigNum.h"
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

BigNum::BigNum() {
    num.push_back(0);
    length = 1;
    sign = true;
}

BigNum::BigNum(const vector<int> &temp, bool flag) {
    this->sign = flag && (temp.back() >= 0);
    uniform(temp, this->num);
    this->length = this->num.size();
}

BigNum::BigNum(const string &s) {
    length = 0;
    int strlen = s.length();
    sign = !(strlen > 0 && s[0] == '-');
    bool flag = (strlen > 0 && s[0] == '-') || (strlen > 0 && s[0] == '+');

    for (int i = strlen - 4; i > flag - 4; i -= 4) {
        int number;
        str2int(i > flag ? s.substr(i, 4) : s.substr(flag, i + 4 - flag), number);
        num.push_back(number);
        length++;
    }
}

BigNum::~BigNum() = default;

const BigNum BigNum::operator+(const BigNum &right) const {
    vector<int> temp;
    add(this->num, this->sign, right.num, right.sign, temp);
    return BigNum(temp);
}

const BigNum BigNum::operator-(const BigNum &right) const {
    BigNum newNum(right);
    newNum.sign = !right.sign;
    return operator+(newNum);
}

const BigNum BigNum::operator*(const BigNum &right) const {
    vector<int> temp;
    if (this->length > right.length) {
        mutiply(right.num, this->num, temp);
    } else {
        mutiply(this->num, right.num, temp);
    }
    return BigNum(temp, this->equalsZero() || this->sign == right.sign || right.equalsZero());
}

BigNum &BigNum::operator+=(const BigNum &right) {
    vector<int> temp;
    add(this->num, this->sign, right.num, right.sign, temp);
    this->sign = temp.back() >= 0; //小于0为1，大于等于0为0
    uniform(temp, this->num);
    this->length = this->num.size();
    return *this;
}

BigNum &BigNum::operator-=(const BigNum &right) {
    BigNum newNum(right);
    newNum.sign = !right.sign;
    return operator+=(newNum);
}

string BigNum::tostring(string &s) const {
    if (!sign)
        s += "-";
    for (int i = length - 1; i >= 0; i--) {
        string m;
        int2str(num[i], m, i != length - 1);
        s += m;
    }
    return s;
}

void BigNum::str2int(const string &string_temp, int &int_temp) {
    stringstream stream(string_temp);
    stream >> int_temp;
}

void BigNum::int2str(const int &int_temp, string &string_temp, bool flag) const {
    stringstream ss;
    ss << int_temp;
    string_temp = ss.str();
    if (flag && string_temp.size() < 4) {
        string_temp.insert(0, 4 - string_temp.size(), '0');
    }
}

void BigNum::add(const vector<int> &left, bool sign1, const vector<int> &right, bool sign2,
                 vector<int> &temp) const {
    temp.clear();
    int carryBit = 0;
    int maxlen = left.size() > right.size() ? left.size() : right.size();
    for (int i = 0; i < maxlen; i++) {
        int leftv = (i < left.size()) ? (sign1 ? left[i] : -left[i]) : 0;
        int rightv = (i < right.size()) ? (sign2 ? right[i] : -right[i]) : 0;
        int sum0 = leftv + rightv + carryBit;
        carryBit = sum0 / (MAX + 1);
        temp.push_back(sum0 % (MAX + 1));
    }
    temp.push_back(carryBit > 0 ? carryBit : -carryBit); //进位
    while (temp.back() == 0 && temp.size() > 1)          //去除最高位上的0
    {
        temp.pop_back();
    }
}

void BigNum::mutiply(const std::vector<int> &left, const std::vector<int> &right,
                     std::vector<int> &temp) const {
    temp.clear();
    for (int i = 0; i < left.size() + right.size(); i++) {
        temp.push_back(0);
    }
    int carryBit = 0;
    for (int i = 0; i < left.size(); i++) {
        carryBit = 0;
        int leftv = left[i];
        int j = 0;
        for (j = 0; j < right.size(); j++) {
            int sum0 = temp[i + j] + leftv * right[j] + carryBit;
            carryBit = sum0 / (MAX + 1);
            temp[i + j] = sum0 % (MAX + 1);
        }
        while (carryBit != 0) {
            int sum0 = temp[i + j] + carryBit;
            carryBit = sum0 / (MAX + 1);
            temp[i + j] = sum0 % (MAX + 1);
            j++;
        }
    }
    while (temp.back() == 0 && temp.size() > 1)          //去除最高位上的0
    {
        temp.pop_back();
    }
    int top = temp.back();
    temp[temp.size() - 1] = (top + carryBit) % (MAX + 1); //进位
    if ((top + carryBit) > MAX) {
        temp.push_back((top + carryBit) / (MAX + 1));
    }
}

void BigNum::uniform(const vector<int> &temp, vector<int> &result) {
    result.clear();
    bool flag = temp.back() < 0;
    int carryBit = 0;
    for (int i : temp) {
        int m = i + carryBit;
        if (m > 0 && flag) //最终结果是负数，正在处理的数是正数
        {
            m = (MAX + 1) - m;
            carryBit = 1;
        } else if (m < 0 && !flag) //最终结果是正数，正在处理的数是负数
        {
            m += (MAX + 1);
            carryBit = -1;
        } else //正在处理的位与最终结果的符号相同，所以取绝对值，并把借位标记为0
        {
            m = abs(m);
            carryBit = 0;
        }
        result.push_back(m);
    }
    while (result.back() == 0 && result.size() > 1) //去除最高位上的0
    {
        result.pop_back();
    }
}

bool BigNum::equalsZero() const {
    return this->length == 1 && this->num[0] == 0;
}

bool BigNum::equals(const BigNum &bigNum) const {
    if (this->length != bigNum.length) {
        return false;
    }
    if (this->sign != bigNum.sign) {
        return false;
    }
    for (int i = 0; i < this->length; i++) {
        if (this->num[i] != bigNum.num[i]) {
            cout << "numequals:" << i << endl;
            cout << "this:" << this->num[i] << endl;
            cout << "that:" << bigNum.num[i] << endl;
            return false;
        }
    }
    return true;
}
