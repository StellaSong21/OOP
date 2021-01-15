#ifndef SOKOBANGAME_POSITION_H
#define SOKOBANGAME_POSITION_H

class Position {
private:
    int x;
    int y;
public:
    /**
     *
     * @param x 横坐标，默认为0
     * @param y 纵坐标，默认为0
     */
    explicit Position(int x = 0, int y = 0);

    /**
     * @return Position(x,y)
     */
    static Position of(int x, int y);

    /**
     * 两个坐标是否相等：x与y的值都相等
     */
    bool equals(Position p);

    int getX() const { return x; }

    int getY() const { return y; }

    /**
     * 移动相对距离
     */
    void move(int dx, int dy) {
        this->x += dx;
        this->y += dy;
    }
};


#endif //SOKOBANGAME_POSITION_H
