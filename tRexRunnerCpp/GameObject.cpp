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
}

void GameObject::Draw(sf::RenderWindow* window)
{
  m_sprite->setScale(GAME_SCALE, GAME_SCALE);
  window->draw(*m_sprite);
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
  delete [] pixels;
  pixels = NULL;
  try {
    return (new sf::Sprite(*texture));
  }
  catch (...)
  {
    printf("Could not create sprite");
    return NULL;
  }
}

bool GameObject::Colliding(GameObject* obstacle)
{
  m_shrunkBounds = m_sprite->getGlobalBounds();
  m_shrunkBounds.left += (1 / 6) * m_shrunkBounds.width;
  m_shrunkBounds.width /= 1.5;
  return m_shrunkBounds.intersects(obstacle->m_sprite->getGlobalBounds());
}

GameObject::~GameObject()
{
}
