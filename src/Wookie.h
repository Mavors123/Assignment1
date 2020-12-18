#pragma once
#include "DisplayObject.h"

class Wookie : public DisplayObject {
public:
    Wookie();
    ~Wookie();

    // Inherited via GameObject
    void draw() override;
    void update() override;
    void clean() override;
};
