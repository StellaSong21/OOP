#include <vector>
#include "Session.h"

using namespace std;

Session::Session(const vector<int> &mapInfo, const Position &playerPos) : gameMap(mapInfo), player(playerPos), onFinished(
        false) {
}

bool Session::finished() const {
    return gameMap.box_all_on();
}


