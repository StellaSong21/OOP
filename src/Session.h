#ifndef SOKOBANGAME_SESSION_H
#define SOKOBANGAME_SESSION_H

#include <vector>
#include "GameMap.h"
#include "Player.h"

/**
 * 游戏地图中并不包括玩家的位置，这样方便对玩家走到目标地的处理
 */

class Session {
private:
    GameMap gameMap;
    Player player;
    bool onFinished;
public:
    explicit Session(const std::vector<int> &mapInfo, const Position &playerPos);

    ~Session() = default;

    /**
     * 判断游戏是否结束
     * @return 结束返回true，否则返回false
     */
    bool finished() const;

    /**
     * @return 游戏的地图，其中不包括玩家的位置，以引用返回，要根据玩家的命令做相应的改变
     */
    GameMap &getGameMap() { return gameMap; }

    /**
     * @return 玩家，玩家的位置会发生变化，因此引用返回
     */
    Player &getPlayer() { return player; }

    void setOnFinished() { this->onFinished = true; }

    int getOnFinished() {
        return onFinished;
    }
};


#endif //SOKOBANGAME_SESSION_H
