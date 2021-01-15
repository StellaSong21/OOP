//
// Created by lenovo on 2019/6/20.
//

#ifndef SOKOBANGAME_GAME_H
#define SOKOBANGAME_GAME_H

#include <vector>

#include "Session.h"

//typedef std::vector<Session> sessionList;

class Game {
private:
//    sessionList sessions;
    Session *currentSession = nullptr;
public:
    /* 开始一局游戏，创建一个session */
    Session startSession(const std::vector<int> &mapInfo, const Position &playerPos);

    /* 游戏结束的处理 */
    void finishSession();

    Session &getCurrentSession() { return *currentSession; }
};

#endif //SOKOBANGAME_GAME_H
