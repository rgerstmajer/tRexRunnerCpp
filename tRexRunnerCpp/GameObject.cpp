#include "GameObject.h"



GameObject::GameObject()
{
    sprite = new sf::Sprite;
}

void GameObject::Draw(sf::RenderWindow* window) // Display the sprite
{
    window->draw(*sprite);
}

sf::Sprite* GameObject::LoadShape(sf::Texture* texture, const int height, const int width, const unsigned char* shape)
{
    sf::Uint8* pixels = new sf::Uint8[height * width * 4];
    int row, column, position, color;
    bool pixelPresent;
    for (register int i = 0; i < height * width; i++)
    {
        row = i / (width * 8);
        column = i % width;
        position = 1 << (0 + ((i / width) % 8));
        pixelPresent = (shape[row + column + row * width] & (position));
        color = pixelPresent ? 255 : 0;
        pixels[i * 4] = color;
        pixels[i * 4 + 1] = color;
        pixels[i * 4 + 2] = color;
        pixels[i * 4 + 3] = color;
    }
    texture->create(width, height);
    texture->update(pixels);
    return (new sf::Sprite(*texture));
}

GameObject::~GameObject()
{

}
