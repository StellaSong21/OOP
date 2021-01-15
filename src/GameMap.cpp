#include <map>
#include <vector>
#include "GameMap.h"

using namespace std;

GameMap::GameMap(const vector<int> &mapInfo) {
    this->width = mapInfo[0];
    this->height = mapInfo[1];
    for (int i = 2; i < mapInfo.size(); i++) {
        gameMap.push_back(static_cast<Entity> (mapInfo[i]));
    }
}

bool GameMap::box_all_on() const {
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            if (get(Position::of(x, y)) == Entity::BOX) {
                return false;
            }
        }
    }
    return true;
}
