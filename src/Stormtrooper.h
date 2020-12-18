#pragma once
#include "DisplayObject.h"

class Stormtrooper : public DisplayObject {
public:
    Stormtrooper();
    ~Stormtrooper();

    // Inherited via GameObject
    void draw() override;
    void update() override;
    void clean() override;

};
