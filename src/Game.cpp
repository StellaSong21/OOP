#include <cassert>
#include <vector>

#include "Game.h"

using namespace std;

Session Game::startSession(const vector<int> &mapInfo, const Position &playerPos) {
    assert(currentSession == nullptr);
    currentSession = new Session(mapInfo,playerPos);
    return *currentSession;
//    return Session(mapInfo, playerPos);
}

void Game::finishSession() {
//    sessions.push_back(*currentSession);
    delete currentSession;
    currentSession = nullptr;
}
