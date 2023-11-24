#include <gtest/gtest.h>

#include "UI.h"
#include "UIElement.h"

namespace
{
class UITest : public ::testing::Test
{
  protected:
    Interface::UI ui;

    UITest() {}

    virtual ~UITest() {}

    virtual void SetUp() { ui = Interface::UI(); }

    virtual void TearDown() {}
};

TEST_F(UITest, EmptyVectorOnCreation) { EXPECT_EQ(ui.getElementVector().size(), 0U); }

TEST_F(UITest, PushIncreasesVectorSizeByOne)
{
    unsigned long currentSize = 0U;

    while (currentSize < 100U)
    {
        Interface::UIElement* element = new Interface::UIElement();
        ui.pushElement(element);
        EXPECT_EQ(ui.getElementVector().size(), ++currentSize);
    }
}
} // namespace