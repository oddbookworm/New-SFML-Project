#include "UIElement.h"

#include <iostream>

namespace Interface
{

UIElement::UIElement() : m_texturePtr(), m_sprite() { std::cout << "UIElement created\n"; }

} // namespace Interface