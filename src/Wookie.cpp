#include "Wookie.h"

#include "TextureManager.h"

Wookie::Wookie() {
    TextureManager::Instance()->load("../Assets/textures/wookie.jpg","wookie");

    auto size = TextureManager::Instance()->getTextureSize("wookie");
    setWidth(size.x);
    setHeight(size.y);

    getTransform()->position = glm::vec2(400.0f, 300.0f);
    getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
    getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
    getRigidBody()->isColliding = false;
    setType(WOOKIE);
}

Wookie::~Wookie() = default;

void Wookie::draw() {
    // alias for x and y
    const auto x = getTransform()->position.x;
    const auto y = getTransform()->position.y;

    // draw the ship
    TextureManager::Instance()->draw("wookie", x, y, 0, 255, true);
}

void Wookie::update() {
}

void Wookie::clean() {
}
