#pragma once
#include "DisplayObject.h"

class Projectile : public DisplayObject{
public:
    Projectile();
    ~Projectile();

    // Inherited via GameObject
    void draw() override;
    void update() override;
    void clean() override;


    void m_move();
};
