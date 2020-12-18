#include "Background.h"

#include "TextureManager.h"

Background::Background() {
    TextureManager::Instance()->load("../Assets/textures/background.png", "background");

    const auto size = TextureManager::Instance()->getTextureSize("background");
    setWidth(size.x);
    setHeight(size.y);

    getTransform()->position = glm::vec2(0, 0);
    setType(BACKGROUND);
}

Background::~Background() = default;

void Background::draw() {
    TextureManager::Instance()->draw("background", 0, 0, 0, 255, false);
}

void Background::update() {
}

void Background::clean() {
}
