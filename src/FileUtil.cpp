//
// Created by lenovo on 2019/6/1.
//

#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <vector>
#include <regex>
#include <stack>
#include "FileUtil.h"
#include "Matrix.h"

using namespace std;

void FileUtil::readMatrix(const string &file, map<string, Matrix> &mmap) {
    ifstream infile;
    infile.open(file.data());   //将文件流对象与文件连接起来 
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行

    string tmp;

    infile >> tmp;//按空格读取，遇到空白符结束
    int num = 0;
    stringstream stream(tmp);
    stream >> num;

    string numStr[SIZE * SIZE];
    string name;

    for (int j = 0; j < num; j++) {
        infile >> name;
        for (auto &i : numStr) {
            infile >> tmp;
            i = tmp;
        }
        mmap.insert(make_pair(name, Matrix(numStr)));
    }

    infile.close();
}

void FileUtil::readExpression(const std::string &file, vector<vector<string>> &RNPs) {
    ifstream infile;
    infile.open(file.data());   //将文件流对象与文件连接起来
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行
    string line;
    vector<string> auxiliary;
    std::vector<std::string> RNP;
    while (getline(infile, line)) {
        split(line, auxiliary);
        getRNP(auxiliary, RNP);

/*        cout << line << ":\t";
        for (const auto &i : auxiliary) {
            cout << i << " ";
        }
        cout << endl;
        for (const auto &i : RNP) {
            cout << i << " ";
        }
        cout << endl;
*/
        RNPs.push_back(RNP);
        auxiliary.clear();
        RNP.clear();
    }

/*    for (const auto &i : RNPs) {
        for (const auto &j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
*/
    infile.close();
}

//改为后缀表达式,只要小于等于栈顶的优先级，就要出栈入队列
void FileUtil::getRNP(const std::vector<std::string> &expression, std::vector<std::string> &RNP) {
    stack<string> auxiliary;
    for (const auto &i : expression) {
        if (!opera.count(i)) {
            RNP.push_back(i);
        } else {
            while (!auxiliary.empty() && opera.at(i) <= opera.at(auxiliary.top())) {
                RNP.push_back(auxiliary.top());
                auxiliary.pop();
            }
            auxiliary.push(i);
        }
    }
    while (!auxiliary.empty()) {
        RNP.push_back(auxiliary.top());
        auxiliary.pop();
    }
}

//每次都会将上一次的符号和目前之间的内容插入进去，所以，每次剩余未处理部分都是符号开头
void FileUtil::split(const std::string &lines, std::vector<std::string> &expression) {
    string operators = "+-*~=";
    int last = -1;
    int current = lines.find_first_of(operators, 0);
    while (current >= 0) {/* 表示里面还有运算符号 */
        if (current == 0) {/* 首位就是运算符号，那么可能是~，+，-，如果是~，last=0 */
            if (lines[current] == '~') {
                last = 0;
            }
        } else if (current == last + 1) {
            /*
             * 1.+=/-=
             * 2.+~/-~
             * 3.=+1/++1/+-1，第二个符号为后面数字的正负号，要包括在后面的数字中
             */
            if (lines[current] == '=') {
                expression.push_back(lines.substr(last, 2));
                last = current;
            } else if (lines[current] == '~') {
                expression.push_back(lines.substr(last, 1));
                last = current;
                /*
                 * 如果首位为~的情况没有处理，那么可以采用该if条件
                 * if (last >= 0) {
                 * expression.push_back(lines.substr(last, 1));
                 * }
                 */
            }
        } else {/* 中间有数字或者矩阵名(由else if的处理，数字包括前面可能存在的正负号) */
            if (last >= 0) {
                expression.push_back(lines.substr(last, 1));
            }
            expression.push_back(lines.substr(last + 1, current - last - 1));
            last = current;
        }
        current = lines.find_first_of(operators, current + 1);
    }

    if (last >= 0 && lines[last] != '=') {/* 收尾，最后剩余部分插进去，包括符号和非符号部分 */
        expression.push_back(lines.substr(last, 1));
    }
    expression.push_back(lines.substr(last + 1));
}

void FileUtil::writeMatrix(const string &file, const Matrix &matrix) {
    ofstream outf;
    outf.open(file, iostream::app);
    assert(outf.is_open());
    string s;
    outf << matrix.tostring(s) << endl;
    outf.close();
}

const map<std::string, int> FileUtil::opera = FileUtil::initOpera();

