#include "UI.h"
#include <iostream>

namespace Interface
{
UI::UI() {}

std::vector<UIElement*> UI::getElementVector() const { return m_elements; }

void UI::pushElement(UIElement* element) { m_elements.push_back(element); }
} // namespace Interface