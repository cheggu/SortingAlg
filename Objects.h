#pragma once
#include "includes.h"

class Objects {
public:
    std::vector<sf::Drawable*> objList = {};

    int getObjectCount() {
        return objList.size();
    }
private:
};
