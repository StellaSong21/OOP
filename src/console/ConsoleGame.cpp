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

/* �����������Чʱ����ʾ��Ϣ */
void printError();

void printHelp();

/* �����˳�ʱ����ӡ��ʾ��� */
void printExit();

/* ��Ϸ���� */
void printWon();

/* ��ʾ��һ������ */
void printNext();

/**
 * �����û����������
 * @return ��ʽ��ʼ��Ϸ��ʱ���û��������Ƿ�Ϊwasd��
 * ����ǣ��ύ�����ʵ����action�������������ڸ�����ֱ�Ӵ���
 */
int addressInstruct(const string &instruct);

//void addressInstruct1(const string &instruct);
//
//bool addressInstruct2(const string &instruct);

int main() {
    while (!toEnd) {
        ::printWelcome();
        string instruct;
        ConsoleMapUtil::waitForInput(instruct);/* �ȴ��û��������� */
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
        if (result == 0) /* �����WASD������action�������� */
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
    cout << "�� ����С�ˣ��� ����ǽ�壬�� ����Ŀ��ص㣬�� �������ӣ����㽫�����Ƶ�Ŀ��ص�֮�󣬡� �ͻ���" << endl;
    cout << "��ѽ����ѽ���������~" << endl;
    cout << "H������ʾ��������������1-9ѡ��ؿ�������Q�˳���Ϸ" << endl;
}

void printError() {
    cout << "��Ч������~~" << endl;
    cout << endl;
}

void printHelp() {
    cout << "1.H������ʾ��������������1-9ѡ��ؿ�������Q�˳���Ϸ" << endl;
    cout << "2.�� ����С�ˣ��� ���� ǽ�壬�� ����Ŀ��ص㣬�� �������ӣ����㽫�����Ƶ�Ŀ��ص�֮ �󣬡� �ͻ��ɡ�" << endl;
    cout << "3.ʹ�� WASD ���������ϡ��������¡������ƶ������ǰ������û���谭������һ���ƶ�һ��" << endl;
    cout << "4.��Ϸһ����ʼ��������ѡ��" << endl;
    cout << "5.��Ϸ�����п���ͨ��H�鿴������Ϣ��Q�˳���Ϸ" << endl;
}

void printExit() {
    cout << "��Ϸ�����˳�������" << endl;
}

void printWon() {
    cout << "���سɹ�������" << endl;
    cout << endl;
}

void printNext() {
    cout << "���������";
}

int addressInstruct(const string &instruct) {
    /* ���ȴ���1���ڴ˴�ʵ�����ǲ��Ϸ��� */
    if (instruct.size() != 1) {
        printError();
        return -1;
    }
    if (instruct == "H") {
        printHelp();
        return -1;
    }
    if (instruct == "Q") {
        toEnd = true;/* �����˳�Ϊtrue */
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
    /* �����ƶ�ʱ */
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
