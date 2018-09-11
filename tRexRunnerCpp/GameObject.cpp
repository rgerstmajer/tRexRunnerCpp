//! GameObject.cpp
/*!
* Implementation of the GameObject class
*
* Created: 20.08.2018.
* Author : Robert Gerstmajer
*/
#include "GameObject.h"

GameObject::GameObject()
{
    sprite = new sf::Sprite;
}

void GameObject::Draw(sf::RenderWindow* window)
{
    sprite->setScale(GAME_SCALE, GAME_SCALE);
    window->draw(*sprite);
}

sf::Sprite* GameObject::LoadShape(sf::Texture* texture,
                                  const int height,
                                  const int width,
                                  const unsigned char* shape,
                                  bool isBump)
{
    sf::Uint8* pixels = new sf::Uint8[height * width * 4];
    int row, column, position, color;
    bool pixelPresent;
    for (register int i = 0; i < height * width; i++)
    {
        row = i / (width * BITS_IN_BYTE);
        column = i % width;
        position = 1 << (0 + ((i / width) % BITS_IN_BYTE));
        pixelPresent = (shape[column + row * width] & (position));
        color = pixelPresent ? WHITE : BLACK;
        pixels[i * 4] = color;
        pixels[i * 4 + 1] = color;
        pixels[i * 4 + 2] = color;
        pixels[i * 4 + 3] = isBump ? WHITE : color;
    }
    texture->create(width, height);
    texture->update(pixels);
    sf::Sprite* tempSprite = new sf::Sprite(*texture);
    return (new sf::Sprite(*texture));
}

bool GameObject::Colliding(GameObject* obstacle)
{
    obstacle->sprite->getTexture();
    return this->sprite->getGlobalBounds().intersects(obstacle->sprite->getGlobalBounds());
}

GameObject::~GameObject()
{

}