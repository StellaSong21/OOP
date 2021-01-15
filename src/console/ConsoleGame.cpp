#include "ConsoleGame.h"
#include "../Game.h"
#include "ConsoleMapUtil.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool toEnd = false;

bool canMove = false;

Game game;

void printWelcome();

/* 输入的命令无效时，提示信息 */
void printError();

void printHelp();

/* 程序退出时，打印提示语句 */
void printExit();

/* 游戏过关 */
void printWon();

/* 提示下一步操作 */
void printNext();

/**
 * 处理用户输入的命令
 * @return 正式开始游戏的时候，用户的命令是否为wasd，
 * 如果是，会交给玩家实例的action方法处理，否则在该类中直接处理
 */
int addressInstruct(const string &instruct);

//void addressInstruct1(const string &instruct);
//
//bool addressInstruct2(const string &instruct);

int main() {
    while (!toEnd) {
        ::printWelcome();
        string instruct;
        ConsoleMapUtil::waitForInput(instruct);/* 等待用户输入命令 */
        addressInstruct(instruct);
    }
    game.finishSession();
    printExit();
    return 0;
}

void ConsoleGame::playOneSession(Session &s) {
    while (!s.finished() && !toEnd && !s.getOnFinished()) {
        ConsoleMapUtil::display(s.getGameMap(), s.getPlayer().getPosition());
        printNext();
        string instruct;
        ConsoleMapUtil::waitForInput(instruct);
        int result = addressInstruct(instruct);
        if (result == 0) /* 如果是WASD，调用action函数处理 */
            s.getPlayer().action(instruct, s.getGameMap());
        if (result >= 1) {
            s.setOnFinished();
        }
    }
    if (!toEnd && !s.getOnFinished()) {
        ConsoleMapUtil::display(s.getGameMap(), s.getPlayer().getPosition());
        printWon();
    }
}

void printWelcome() {
    cout << "※ 代表小人，■ 代表墙体，○ 代表目标地点，□ 代表箱子，当你将箱子推到目标地点之后，○ 就会变成" << endl;
    cout << "来呀，来呀，来玩儿啊~" << endl;
    cout << "H代表显示帮助，输入数字1-9选择关卡，输入Q退出游戏" << endl;
}

void printError() {
    cout << "无效的命令~~" << endl;
    cout << endl;
}

void printHelp() {
    cout << "1.H代表显示帮助，输入数字1-9选择关卡，输入Q退出游戏" << endl;
    cout << "2.※ 代表小人，■ 代表 墙体，○ 代表目标地点，□ 代表箱子，当你将箱子推到目标地点之 后，○ 就会变成●。" << endl;
    cout << "3.使用 WASD 来代表向上、向左、向下、向右移动，如果前进方向没有阻碍，可以一次移动一格；" << endl;
    cout << "4.游戏一旦开始，不可以选关" << endl;
    cout << "5.游戏过程中可以通过H查看帮助信息，Q退出游戏" << endl;
}

void printExit() {
    cout << "游戏正在退出。。。" << endl;
}

void printWon() {
    cout << "闯关成功！！！" << endl;
    cout << endl;
}

void printNext() {
    cout << "请输入命令：";
}

int addressInstruct(const string &instruct) {
    /* 长度大于1，在此次实现中是不合法的 */
    if (instruct.size() != 1) {
        printError();
        return -1;
    }
    if (instruct == "H") {
        printHelp();
        return -1;
    }
    if (instruct == "Q") {
        toEnd = true;/* 设置退出为true */
        return -1;
    }
    if (instruct.find_first_of("123456789", 0) >= 0 && instruct.find_first_of("123456789", 0) <= 8) {
        game.finishSession();
        vector<int> map;
        Position playerPos;
        ConsoleMapUtil::readMap(instruct, map, playerPos);
        canMove = true;
        Session s = game.startSession(map, playerPos);
        ConsoleGame::playOneSession(game.getCurrentSession());
        game.finishSession();
        canMove = false;
        return instruct.at(0) - '0';
    }
    /* 可以移动时 */
    if (canMove)
        if (instruct.find_first_of("WASD", 0) >= 0 && instruct.find_first_of("WASD", 0) <= 3) {
            return 0;
        }

    printError();
    return -1;
}

//void addressInstruct1(const string &instruct) {
//    if (instruct.size() != 1) {
//        printError();
//        return;
//    }
//    if (instruct == "H") {
//        printHelp();
//        return;
//    }
//    if (instruct == "Q") {
//        toEnd = true;
//        return;
//    }
//    if (instruct.find_first_of("123456789", 0) >= 0 && instruct.find_first_of("123456789", 0) <= 8) {
//        vector<int> map;
//        Position playerPos;
//        ConsoleMapUtil::readMap(instruct, map, playerPos);
//        Session *s = game.startSession(map, playerPos);
//        ConsoleGame::playOneSession(*s);
//        game.finishSession();
//    }
//    printError();
//}
//
//bool addressInstruct2(const string &instruct) {
//    if (instruct.size() != 1) {
//        printError();
//        return false;
//    }
//    if (instruct == "H") {
//        printHelp();
//        return false;
//    }
//    if (instruct == "Q") {
//        toEnd = true;
//        return false;
//    }
//    if (instruct.find_first_of("wasd", 0) >= 0 && instruct.find_first_of("wasd", 0) <= 3) {
//        return true;
//    }
//
//    printError();
//    return false;
//}
