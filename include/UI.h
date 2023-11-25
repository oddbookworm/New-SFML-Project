#ifndef UI_H
#define UI_H

#include <unordered_map>
#include <vector>

#include "SFML/Graphics.hpp"

#include "UIElement.h"

namespace Interface
{
class UI
{
  public:
    /**
     * @brief Construct a new UI object
     */
    UI();

    /**
     * @brief Destructs UI
     */
    virtual ~UI();

    /**
     * @brief Handles the events passed in
     *
     * @param events a vector of events to process
     */
    virtual void handleEvents(const std::vector<sf::Event>& events);

    /**
     * @brief updates the UI
     */
    virtual void update();

    /**
     * @brief Draws the UI
     *
     * @param target the destination to draw onto
     */
    virtual void draw(sf::RenderTarget& target);

    /**
     * @brief Gets a vector of the element names
     *
     * @return std::vector<std::string> names of the elements
     */
    std::vector<std::string> getElementNames() const;

  private:
    /**
     * @brief Adds an element to the map
     *
     * @param name name of the element
     * @param element the element
     * @return true if successful
     * @return false otherwise
     */
    bool addElement(const std::string& name, UIElement& element);

    std::unordered_map<std::string, UIElement>
        m_elements; //!< contains pointers to the UI's elements
};
} // namespace Interface

#endif // UI_H