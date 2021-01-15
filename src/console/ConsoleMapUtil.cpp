#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

#include "ConsoleMapUtil.h"
#include "../Position.h"

using namespace std;

#define PATH "../maps/"
#define SUFFIX ".map"

string ConsoleMapUtil::getSymbol(Entity entity) {
    switch (entity) {
        case OUTER_SPACE:
        case INNER_SPACE:
            return " ";
        case WALL:
            return "¡ö";
        case BOX:
            return "¡õ";
        case DESTINATION:
            return "¡ð";
        case PLAYER1:
        case PLAYER2:
        case PLAYER3:
        case PLAYER4:
            return "¡ù";
        case BOX_ON:
            return "¡ñ";
        default:
            throw std::runtime_error("invalid entity");
    }
}

void ConsoleMapUtil::display(const GameMap &map, const Position &playerPos) {
    for (int x = 0; x < map.getHeight(); x++) {
        for (int y = 0; y < map.getWidth(); y++) {
            if (Position::of(x, y).equals(playerPos)) {
                cout << getSymbol(Entity::PLAYER1) << " ";
            } else {
                cout << getSymbol(map.get(Position::of(x, y))) << " ";
            }
        }
        cout << endl;
    }
}

void ConsoleMapUtil::waitForInput(string &instruct) {
    assert(instruct.empty());
    cin >> instruct;
}

void ConsoleMapUtil::readMap(const string &fileName, vector<int> &map, Position &playerPos) {
    ifstream inFile;
    inFile.open((PATH + fileName + SUFFIX).data());
    assert(inFile.is_open());

    int num = 0;
    for (int i = 0; i < 2; i++) {
        inFile >> num;
        map.push_back(num);
    }

    string line;
    int lineNum = -1;//todo ¿ÕÐÐ£¿
    while (getline(inFile, line)) {
        for (int i = 0; i < line.size(); i++) {
            char cur = line[i] - '0';
            if (cur >= 5 && cur <= 8) {
                playerPos.move(lineNum, i);
                cur = 2;
            }
            map.push_back(cur);
        }
        lineNum++;
    }
    inFile.close();
}
