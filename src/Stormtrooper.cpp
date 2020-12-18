#include "Stormtrooper.h"

#include "TextureManager.h"

Stormtrooper::Stormtrooper() {
    TextureManager::Instance()->load("../Assets/textures/Stormtrooper.jpg","Stormtrooper");

    auto size = TextureManager::Instance()->getTextureSize("Stormtrooper");
    setWidth(size.x);
    setHeight(size.y);

    getTransform()->position = glm::vec2(400.0f, 300.0f);
    getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
    getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
    getRigidBody()->isColliding = false;
    setType(STORMTROOPER);
}

Stormtrooper::~Stormtrooper() = default;

void Stormtrooper::draw() {
    // alias for x and y
    const auto x = getTransform()->position.x;
    const auto y = getTransform()->position.y;

    // draw the ship
    TextureManager::Instance()->draw("Stormtrooper", x, y, 0, 255, true);
}

void Stormtrooper::update() {
}

void Stormtrooper::clean() {
}
