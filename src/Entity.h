//
// Created by lenovo on 2019/6/18.
//

#ifndef SOKOBANGAME_ENTITY_H
#define SOKOBANGAME_ENTITY_H

/* 表示地图中的实体 */
enum Entity {
    OUTER_SPACE = 0,
    WALL,
    INNER_SPACE,
    BOX,
    DESTINATION,
    PLAYER1,/* 5，6，7，8都表示玩家 */
    PLAYER2,
    PLAYER3,
    PLAYER4,
    BOX_ON
};

#endif //SOKOBANGAME_ENTITY_H
