//
// Created by lenovo on 2019/6/1.
//

#ifndef OOPLAB4_FILEUTIL_H
#define OOPLAB4_FILEUTIL_H

#include <string>
#include <map>
#include "Matrix.h"

class FileUtil {
    static std::map<std::string, int> const opera;

    static std::map<std::string, int> initOpera() {
        std::map<std::string, int> operat;
        operat.insert(std::make_pair("+=", 0));
        operat.insert(std::make_pair("-=", 0));
        operat.insert(std::make_pair("+", 1));
        operat.insert(std::make_pair("-", 1));
        operat.insert(std::make_pair("*", 2));
        operat.insert(std::make_pair("/", 2));
        operat.insert(std::make_pair("~", 3));
        return operat;
    }

    static void getRNP(const std::vector<std::string> &, std::vector<std::string> &);

    static void split(const std::string &, std::vector<std::string> &);

public:
    static void readMatrix(const std::string &file, std::map<std::string, Matrix> &);

    static void readExpression(const std::string &file, std::vector<std::vector<std::string>> &);

    static void writeMatrix(const std::string &file, const Matrix &matrix);
};

#endif //OOPLAB4_FILEUTIL_H
