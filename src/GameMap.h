#ifndef SOKOBANGAME_GAMEMAP_H
#define SOKOBANGAME_GAMEMAP_H

#include <vector>

#include "Entity.h"
#include "Position.h"

class GameMap {
    int height;
    int width;
    std::vector<Entity> gameMap;
public:
    /**
     * 初始化
     * @param mapInfo 包含地图的高度和宽度，以及具体地图
     */
    explicit GameMap(const std::vector<int> &mapInfo);

    int getWidth() const { return width; }

    int getHeight() const { return height; }

    /**
     * 得到position位置上的entity
     */
    Entity get(const Position &position) const { return gameMap[position.getX() * width + position.getY()]; }

    /**
     * 将position位置设置为entity
     */
    void set(const Position &position, Entity entity) { gameMap[position.getX() * width + position.getY()] = entity; }

    /**
     * 游戏结束的判断条件：所有的箱子都在目标地
     */
    bool box_all_on() const;
};


#endif //SOKOBANGAME_GAMEMAP_H
