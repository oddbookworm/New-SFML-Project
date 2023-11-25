#include <string>

#include "CommonFunctions.h"
#include "ErrorLogger.h"
#include "UI.h"

namespace Interface
{
UI::UI() {}

UI::~UI() {}

void UI::handleEvents(const std::vector<sf::Event>& events)
{
    for (auto& element : m_elements)
    {
        element.second.handleEvents(events);
    }
}

void UI::update()
{
    for (auto& element : m_elements)
    {
        element.second.update();
    }
}

void UI::draw(sf::RenderTarget& target)
{
    for (auto& element : m_elements)
    {
        element.second.draw(target);
    }
}

std::vector<std::string> UI::getElementNames() const
{
    std::vector<std::string> names;
    for (auto& name : m_elements)
    {
        names.push_back(name.first);
    }

    return names;
}

bool UI::addElement(const std::string& name, UIElement& element)
{
    if (Utils::mapHasKey(m_elements, name))
    {
        std::string outStr = "Map already has UIElement with name " + name;
        outStr += std::string(". Replacing existing element with new element.");
        WARN(outStr);

        m_elements.erase(name);
    }

    if (!m_elements.emplace(name, element).second)
    {
        std::string err = "Failed to insert UIElement with name ";
        ERROR(err + name);
        return false;
    }

    return true;
}
} // namespace Interface