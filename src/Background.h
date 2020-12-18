#pragma once
#include "DisplayObject.h"

class Background final : public DisplayObject {
public:
    Background();
    ~Background();

    void draw() override;
    void update() override;
    void clean() override;
};
