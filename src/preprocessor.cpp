//
// Created by lenovo on 2019/4/10.
//
#include <utility>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include "preprocessor.h"

Preprocessor::Preprocessor(const string &initCode) {
    this->code = initCode;

}

Preprocessor::~Preprocessor() {
    defines.clear();
}

string Preprocessor::preCompile() {
    size_t startHere = 0;
    size_t endHere;
    size_t lookHere = 0;
    int len = 0;
    string line, file, macro;
    int write = 1;
    int num = 0;
    vector<int> ifv(1, 1);
    while ((endHere = code.find('\n', lookHere)) != string::npos) {
        //考虑到换行的情况
        if (code.find('\\') == endHere - 1) {
            code.erase(endHere - 1, 2);
            lookHere = endHere - 1;
            continue;
        }
        line = code.substr(startHere, endHere - startHere);
        macro = line;
        if (startsWith(macro, "#", 0)) {
            size_t sharp = macro.find('#');
            if (startsWith(macro, "include", sharp + 1)) {
                file = addressInclude(macro);
            } else if (startsWith(macro, "define", sharp + 1)) {
                macro = macroReplace(line);
                code.replace(startHere, endHere - startHere, macro);
                endHere += macro.length() - line.length();
                addressDefine(macro);
            } else if (startsWith(macro, "undef", sharp + 1)) {
                addressUndef(macro);
            } else if (startsWith(macro, "ifdef", sharp + 1)) {
                write = ifv[num] && addressIfdef(macro);
                ifv[++num] = write;
            } else if (startsWith(macro, "ifndef", sharp + 1)) {
                write = ifv[num] && addressIfndef(macro);
                ifv[++num] = write;
            } else if (startsWith(macro, "if", sharp + 1)) {
                write = ifv[num] && addressIf(macro);
                ifv[++num] = write;
            } else if (startsWith(macro, "else", sharp + 1)) {
                write = ifv[num - 1] && !ifv[num];
                ifv[num] = write;
            } else if (startsWith(macro, "endif", sharp + 1)) {
                write = ifv[--num];
            }
            len = file.length();
            code.replace(startHere, endHere - startHere + 1, file);
            lookHere = startHere + len;
            startHere = lookHere;
            file = "";
        } else if (write == 1) {
            macro = macroReplace(line);
            code.replace(startHere, endHere - startHere, macro);
            endHere += macro.length() - line.length();
            lookHere = endHere + 1;
            startHere = lookHere;
        } else {
            code.replace(startHere, endHere - startHere + 1, "");
        }
    }
    vector<int>().swap(ifv);
    return code;
}

string Preprocessor::addressInclude(const string &line) {
    size_t start = line.find('\"', 0);
    size_t end = line.find('\"', start + 1);
    string filename = line.substr(start + 1, end - start - 1);
    if (filename == "iostream" || line.find('<') != string::npos)
        return line;
    string filepath = "../test/" + filename;
    ifstream include(filepath);
    string file;
    if (!include.is_open()) {
        cout << "File " << filepath << " not found";
    } else {
        string line0;
        while (getline(include, line0)) {
            file.append(line0).push_back('\n');
        }
        include.close();
    }
    return file;
}

string Preprocessor::addressDefine(const string &line) {
    string m = deleteSpace(line);
    string key;
    string value;
    size_t first = m.find(' ', 0);
    size_t second = m.find(' ', first + 1);
    size_t parentheses = m.find('(', 0);
    if (second == string::npos) {//只有一个标识符
        key = m.substr(first + 1, second - first - 1);
    } else if (parentheses == string::npos || parentheses > second) {//定义一个数据
        key = m.substr(first + 1, second - first - 1);
        value = m.substr(second + 1);
    } else {//定义一个函数
        key = m.substr(first + 1, parentheses - first - 1);
        value = m.substr(parentheses);
    }
    defines.insert(
            pair<string, string>(key, value));
    return "";
}

string Preprocessor::addressUndef(const string &line) {
    string m = deleteSpace(line);
    size_t first = m.find(' ', 0);
    string define = m.substr(first + 1);
    defines.erase(define);
    return "";
}

int Preprocessor::addressIfdef(const string &line) {
    string m = deleteSpace(line);
    size_t s = m.find(' ');
    return s != string::npos && defines.count(m.substr(s + 1)) > 0;
}

int Preprocessor::addressIf(const string &line) {
    string m = deleteSpace(line);
    size_t s = m.find(' ');
    string define = m.substr(s + 1);
    auto iter = defines.find(define);
    if (iter != defines.end()) {
        define = iter->second;
    }
    return s != string::npos && atoi(define.c_str());
}

//如果已经发生替换，说明该语句判断条件为false
int Preprocessor::addressIfndef(const string &line) {
    string m = deleteSpace(line);
    size_t s = m.find(' ');
    return s != string::npos ? 0 >= defines.count(m.substr(s + 1)) : true;
}

//该方法是处理宏定义中的空格，去掉定义内容之前的不必要的空格
string Preprocessor::deleteSpace(const string &str) {
    string m;
    int a = 0;
    int num = 0;
    //\000指的是\n吗？不是，传进来的时候并没有\n，所以不能用\n判断字符串的结束
    for (int i = 0; str[i] != '\000'; i++) {
        char c = str[i];
        switch (c) {
            case '(':
                a = 1;
                m.append(1, c);
                break;
            case ')':
                a = 0;//表示可以加空格
                m.append(1, c);
                break;
            case ' ':
                if (m.length() == 1) {
                    continue;
                }
                if (num >= 2) {
                    m.append(1, ' ');
                } else if (str[i + 1] != '\0' && str[i + 1] != ' ' && !a) {
                    m.append(1, c);
                    num++;
                }
                break;
            default:
                m.append(1, c);
        }
    }
    return m;
}

//考虑到前面有空格的情况和#中间有空格的情况
bool Preprocessor::startsWith(const string &str, const string &start, int i) {
    size_t s = str.find(start, i);
    return (s != string::npos) && (str.substr(i, s - i) == string(s - i, ' '));
}

//将宏定义替换为具体的内容
string Preprocessor::macroReplace(const string &line) {
    string m = line;
    size_t s;
    string key, value;
    map<string, string>::iterator iter;
    iter = defines.begin();
    regex reg("^[0-9a-zA-Z_]+$");
    while (iter != defines.end()) {
        key = iter->first;
        s = m.find(key);
        if (s != string::npos) {
            if (numOfParenthese(m, s) % 2 != 0) {
                iter++;
                continue;
            }
            if (regex_match(m.substr(s - 1, 1), reg)
                || regex_match(m.substr(s + key.length(), 1), reg)) {
                iter++;
                continue;
            }
            value = iter->second;
            if (m[s + key.length()] == '(') {
                size_t left = s + key.length();
                size_t right = m.find(')', left);
                size_t a, b;
                if (value.find_first_of('#') == string::npos) {
                    size_t space = value.find(' ');
                    string formalParameter = value.substr(1, space - 2);
                    a = value.find(formalParameter, space);
                    if (regex_match(m.substr(s - 1, 1), reg)
                        || regex_match(m.substr(s + key.length(), 1), reg)) { ;
                    } else {
                        string actualParameter = m.substr(left + 1, right - left - 1);
                        value.replace(a, formalParameter.length(), actualParameter);
                    }
                    m.replace(s, right - s + 1, value.substr(space + 1));
                } else if ((a = value.find_first_of('#')) == (b = value.find_last_of('#')) - 1) {
                    size_t space = value.find(' ');
                    string formalParameter = value.substr(1, space - 2);
                    a = value.find(formalParameter, space);
                    if (regex_match(m.substr(s - 1, 1), reg)
                        || regex_match(m.substr(s + key.length(), 1), reg)) { ;
                    } else {
                        string actualParameter = m.substr(left + 1, right - left - 1);
                        value.erase(a - 1, 4);
                        value.replace(a, formalParameter.length(), actualParameter);
                    }
                    m.replace(s, right - s + 1, value.substr(space + 1));
                } else {
                    a = value.find_first_of('\"');
                    b = value.find_last_of('\"');
                    string actualParameter = m.substr(left + 1, right - left - 1);
                    value.insert(b, actualParameter);
                    m.replace(s, right - s + 1, value.substr(a, b - a + 1 + actualParameter.length()));
                }
            } else {
                m.replace(s, key.length(), value);
            }
        }
        iter++;
    }
    return m;
}



int Preprocessor::numOfParenthese(const string &line, int m) {
    int num = 0;
    size_t s = 0;
    size_t e;
    while ((e = line.find('\"', s)) != string::npos && e < m) {
        if (line[e - 1] != '\\') {
            num++;
        }
        s = e + 1;
    }
    return num;
}
