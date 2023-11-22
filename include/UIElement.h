#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "SFML/Graphics.hpp"

#include "ResourceManager.h"

namespace Interface
{
class UIElement
{
  public:
    UIElement();

  private:
    /**
     * @brief Disallow copy
     */
    UIElement(const UIElement& other) = delete;

    /**
     * @brief Disallow assignment
     */
    void operator=(const UIElement& rhs) = delete;

    Utils::WeakTexPtr m_texturePtr; //!< weak pointer to the Texture for the sprite
    sf::Sprite m_sprite;            //!< sprite for drawing
};
} // namespace Interface

#endif // UIELEMENT_H