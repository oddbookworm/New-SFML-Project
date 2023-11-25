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

TEST_F(UITest, EmptyMapOnCreation) { EXPECT_EQ(ui.getElementNames().size(), 0U); }
} // namespace