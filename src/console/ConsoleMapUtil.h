#ifndef SOKOBANGAME_CONSOLEMAPUTIL_H
#define SOKOBANGAME_CONSOLEMAPUTIL_H

#include <vector>
#include "../Entity.h"
#include "../GameMap.h"

class ConsoleMapUtil {
private:
    static std::string getSymbol(Entity entity);

public:
    static void display(const GameMap &map, const Position &playerPos);

    static void waitForInput(std::string &instruct);

    static void readMap(const std::string &fileName, std::vector<int> &map, Position &playerPos);
};


#endif //SOKOBANGAME_CONSOLEMAPUTIL_H
