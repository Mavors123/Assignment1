#include "Projectile.h"

#include "TextureManager.h"

Projectile::Projectile() {
    TextureManager::Instance()->load("../Assets/textures/mine.png", "Projectile");

    auto size = TextureManager::Instance()->getTextureSize("Projectile");
    setWidth(size.x);
    setHeight(size.y);

    getTransform()->position = glm::vec2(100.0f, 100.0f);
    getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
    getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
    getRigidBody()->isColliding = false;
    setType(PROJECTILE);
}

Projectile::~Projectile() = default;

void Projectile::draw() {
    // alias for x and y
    const auto x = getTransform()->position.x;
    const auto y = getTransform()->position.y;

    // draw the ship
    TextureManager::Instance()->draw("Projectile", x, y, 0, 255, true);
}

void Projectile::update() {
    m_move();
}

void Projectile::clean() {
}

void Projectile::m_move() {
    getRigidBody()->velocity = getRigidBody()->velocity + getRigidBody()->acceleration * (1.f / 60.f);

    if (getTransform()->position.y >= 450.f) {
        getRigidBody()->velocity = glm::vec2(0, 0);
    }
    
    getTransform()->position = getTransform()->position + getRigidBody()->velocity;
}
