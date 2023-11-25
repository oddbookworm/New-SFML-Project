#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "SFML/Graphics.hpp"

#include "ResourceManager.h"

namespace Interface
{
class UIElement
{
  public:
    /**
     * @brief Construct a new UIElement object
     */
    UIElement();

    /**
     * @brief Destructs the UIElement
     */
    virtual ~UIElement();

    /**
     * @brief Handles the events passed in
     *
     * @param events a vector of events to process
     */
    virtual void handleEvents(const std::vector<sf::Event>& events);

    /**
     * @brief Updates the UIElement
     */
    virtual void update();

    /**
     * @brief Set whether UIElement is visible or not
     *
     * @param visible True if visible, false otherwise
     */
    void setVisible(bool visible);

    /**
     * @brief Draws the UIElement
     *
     * @param target the target to draw onto
     */
    virtual void draw(sf::RenderTarget& target) const;

  private:
    // /**
    //  * @brief Disallow copy
    //  */
    // UIElement(const UIElement& other) = delete;

    // /**
    //  * @brief Disallow assignment
    //  */
    // void operator=(const UIElement& rhs) = delete;

    Utils::WeakTexPtr m_texturePtr; //!< weak pointer to the Texture for the sprite
    sf::Sprite m_sprite;            //!< sprite for drawing
    bool m_visible;                 //!< True if to be drawn, false otherwise
};
} // namespace Interface

#endif // UIELEMENT_H