//
// Created by lenovo on 2019/4/10.
//

#ifndef OOPLAB2_PREPROCESSOR_H
#define OOPLAB2_PREPROCESSOR_H

class Preprocessor;

#include <map>
#include <stack>
#include <string>

using namespace std;

typedef string (Preprocessor::*FP)(const string &line);

class Preprocessor {
private:
    string code;
    map<string, string> defines;

    string addressInclude(const string &line);

    string addressDefine(const string &line);

    string addressUndef(const string &line);

    int addressIfdef(const string &line);

    int addressIfndef(const string &line);

    int addressIf(const string &line);

    string macroReplace(const string &line);

    static bool startsWith(const string &str, const string &start, int i);

    static string deleteSpace(const string &str);

    int numOfParenthese(const string &line, int m);

    void buildMap();

public:
    Preprocessor(const string &initCode);

    ~Preprocessor();

    string preCompile();
};

#endif //OOPLAB2_PREPROCESSOR_H
