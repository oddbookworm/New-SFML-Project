#include "UIElement.h"

#include <iostream>

namespace Interface
{

UIElement::UIElement() : m_texturePtr(), m_sprite(), m_visible(false) {}

UIElement::~UIElement() {}

void UIElement::handleEvents(const std::vector<sf::Event>& events) { (void)events; }

void UIElement::update() {}

void UIElement::setVisible(bool visible) { m_visible = visible; }

void UIElement::draw(sf::RenderTarget& target) const
{
    if (m_visible)
    {
        target.draw(m_sprite);
    }
}

} // namespace Interface