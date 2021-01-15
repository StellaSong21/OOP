#include <cassert>
#include <string>
#include <stdexcept>
#include "Player.h"

using namespace std;

Player::Player(const Position &position) : position(position) {}

void Player::action(const string &instruct, GameMap &gameMap) {
    assert(instruct.size() == 1 && instruct.find_first_of("WASD", 0) >= 0 && instruct.find_first_of("WASD", 0) <= 3);
    switch (instruct.at(0)) {
        case 'W':
            react(gameMap, -1, 0);
            break;
        case 'A':
            react(gameMap, 0, -1);
            break;
        case 'S':
            react(gameMap, 1, 0);
            break;
        default:
            react(gameMap, 0, 1);
            break;
    }
}

void Player::react(GameMap &gameMap, int dx, int dy) {
    Position adjacent = Position::of(this->position.getX() + dx, this->position.getY() + dy);

    Entity adjEntity = gameMap.get(adjacent);

    /* 如果玩家移动方向的前面是空地或者是目的地 */
    if (adjEntity == Entity::INNER_SPACE
        || adjEntity == Entity::DESTINATION) {
        this->position.move(dx, dy);

        return;
    }

    /* 如果玩家移动方向的前面是箱子 */
    if (adjEntity == Entity::BOX || adjEntity == Entity::BOX_ON) {
        /* 箱子前面的位置 */
        Position th = Position::of(adjacent.getX() + dx, adjacent.getY() + dy);
        if (gameMap.get(th) == Entity::INNER_SPACE) {
            gameMap.set(adjacent, adjEntity == Entity::BOX ? INNER_SPACE : DESTINATION);
            gameMap.set(th, BOX);
            this->position.move(dx, dy);
            return;
        }
        if (gameMap.get(th) == Entity::DESTINATION) {
            gameMap.set(adjacent, adjEntity == Entity::BOX ? INNER_SPACE : DESTINATION);
            gameMap.set(th, BOX_ON);
            this->position.move(dx, dy);
            return;
        }
    }
}
