#ifndef UI_H
#define UI_H

#include <vector>

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

    void pushElement(UIElement* element);

    std::vector<UIElement*> getElementVector() const;

  private:
    std::vector<UIElement*> m_elements; //!< contains pointers to the UI's elements
};
} // namespace Interface

#endif // UI_H