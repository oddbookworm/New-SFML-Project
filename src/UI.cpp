#include "UI.h"
#include <iostream>

namespace Interface
{
UI::UI() { std::cout << "UI created\n"; }

void UI::pushElement(UIElement* element) { m_elements.push_back(element); }
} // namespace Interface