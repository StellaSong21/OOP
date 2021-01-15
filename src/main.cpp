#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <fstream>
#include <cassert>

#include "Matrix.h"
#include "BigNum.h"
#include "FileUtil.h"


#define DEBUG(x) cout << #x << ":\n" << (x) << endl

using namespace std;

#define  DE

Matrix eval(map<string, Matrix> matrixmap, const vector<string> &RNP);

Matrix eval(map<string, Matrix> matrixmap, const vector<string> &RNP) {
    stack<Matrix> auxiliary;
    for (const auto &i : RNP) {
        if (matrixmap.count(i)) {
            auxiliary.push(matrixmap.at(i));
        } else if (i == "~") {
            Matrix matrix = auxiliary.top();
            auxiliary.pop();
            auxiliary.push(~matrix);
        } else if (i == "+") {
            Matrix matrix1 = auxiliary.top();
            auxiliary.pop();
            Matrix matrix2 = auxiliary.top();
            auxiliary.pop();
            auxiliary.push(matrix2 + matrix1);
        } else if (i == "-") {
            Matrix matrix1 = auxiliary.top();
            auxiliary.pop();
            Matrix matrix2 = auxiliary.top();
            auxiliary.pop();
            auxiliary.push(matrix2 - matrix1);
        } else if (i == "+=") {
            Matrix matrix1 = auxiliary.top();
            auxiliary.pop();
            Matrix matrix2 = auxiliary.top();
            auxiliary.pop();
            auxiliary.push(matrix2 += matrix1);
        } else if (i == "-=") {
            Matrix matrix1 = auxiliary.top();
            auxiliary.pop();
            Matrix matrix2 = auxiliary.top();
            auxiliary.pop();
            auxiliary.push(matrix2 -= matrix1);
        } else if (i == "*") {
            Matrix matrix1 = auxiliary.top();
            auxiliary.pop();
            Matrix matrix2 = auxiliary.top();
            auxiliary.pop();
            auxiliary.push(matrix2 * matrix1);
        } else {
            BigNum bigNum = BigNum(i);
            auxiliary.push(Matrix(bigNum));
        }
    }
    if (auxiliary.size() == 1)
        return auxiliary.top();
    else
        return Matrix();
}


void readMatrix(const string &file, vector<Matrix> &mmap) {
    ifstream infile;
    infile.open(file.data());   //将文件流对象与文件连接起来
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行

    string tmp;
    string name;
    int num = 0;
    vector<string> matrixstr;

    while (infile >> tmp) {
        num++;
        if (num % 10 == 1) {
            if (!matrixstr.empty()) {
                mmap.emplace_back(matrixstr);
            }
            matrixstr.clear();
            continue;
        } else {
            matrixstr.push_back(tmp);
        }
    }
    if (!matrixstr.empty()) {
        mmap.emplace_back(matrixstr);
    }
    matrixstr.clear();

    infile.close();
}

#undef DE

int main() {
//    Matrix A(BigNum("1"));
//    Matrix B(BigNum("2"));
//    Matrix C(BigNum("3"));
//    A + B += C;

    map<string, Matrix> matrixmap;
    FileUtil::readMatrix("../source/testcase_matrix.in", matrixmap);

//    map<string, Matrix>::iterator it;
//    for (it = matrixmap.begin(); it != matrixmap.end(); it++) {
//        DEBUG(it->first);
//        string s;
//        DEBUG(it->second.tostring(s));
//    }

    vector<vector<string>> v;
    FileUtil::readExpression("../source/testcase_expression.in", v);
//    FileUtil::readExpression("../source/expression.in", v);

    for (const auto &i : v) {
        Matrix matrix = eval(matrixmap, i);
        FileUtil::writeMatrix("../source/result.out", matrix);
    }


//#define DE
//    vector<Matrix> mmap;
//    readMatrix("../source/output.out", mmap);
//    for (int i = 0; i < v.size(); i++) {
//        Matrix matrix = eval(matrixmap, v[i]);
//        bool m = matrix.equals(mmap[i]);
//        DEBUG(m);
//        if (!m) {
//            string test;
//            matrix.tostring(test);
//            DEBUG(test);
//        }
//    }
//#undef DE

//    string m = t.substr(1, 0);
//    DEBUG(m.size());
//    const char *s = "123";
//    DEBUG(strcspn(s, "3"));


} ///:~
