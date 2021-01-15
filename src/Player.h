#ifndef SOKOBANGAME_PLAYER_H
#define SOKOBANGAME_PLAYER_H
#pragma once

#include <string>

#include "Position.h"
#include "GameMap.h"

class Player {
private:
    Position position;

    /**
     * 由action调用，具体判断对gameMap的改变
     * @param gameMap 地图
     * @param dx dy 移动方向上相邻位置与相当前位置的相对位置
     */
    void react(GameMap &gameMap, int dx, int dy);

public:
    /**
     * 用玩家的位置初始化玩家
     * 因为玩家的位置并没有保存在地图中，所以玩家必须有一个表示位置的属性position
     */
    explicit Player(const Position &position);

    /**
     * 根据instruct合理移动
     * @param instruct 命令->wasd
     * @param gameMap 地图
     */
    void action(const std::string &instruct, GameMap &gameMap);

    /**
     * @return 玩家的位置，返回值，表示不可改变
     */
    Position getPosition() const { return this->position; };
};

#endif //SOKOBANGAME_PLAYER_H
