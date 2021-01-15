#include "Position.h"

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

Position Position::of(int x, int y) {
    return Position(x, y);
}

bool Position::equals(Position p) {
    return this->x == p.x && this->y == p.y;
}
