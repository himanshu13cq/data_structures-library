#include <gtest/gtest.h>
#include <string>
#include "linked_list.h"

class LinkedListDeleteFrontTest : public ::testing::Test
{
protected:
    LinkedList<int> list;

    void SetUp() override
    {
        list.insertBack(19);
        list.insertBack(26);
        list.insertBack(109);
    }
};

TEST_F(LinkedListDeleteFrontTest, DeleteFrontFromMultipleElements)
{
    list.deleteFront();
    EXPECT_EQ(list.size(), 2);
    int expected[] = {26, 109};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}

TEST_F(LinkedListDeleteFrontTest, DeleteFrontUntilOneElementRemains)
{
    list.deleteFront();
    list.deleteFront();

    EXPECT_EQ(list.size(), 1);
    auto it = list.begin();
    EXPECT_EQ(*it, 109);
}

TEST(LinkedList, DeleteOnlyElement)
{
    LinkedList<int> list;

    list.insertBack(19);
    list.deleteFront();
    EXPECT_EQ(list.size(), 0);
    EXPECT_FALSE(list.begin() != list.end());
}

TEST(LinkedList, DeleteFrontFromEmptyList)
{
    LinkedList<int> list;

    EXPECT_THROW(list.deleteFront(), std::out_of_range);
}


TEST(LinkedList, DeleteFrontWithString)
{
    LinkedList<std::string> list;

    list.insertBack("lion");
    list.insertBack("mouse");

    list.deleteFront();

    EXPECT_EQ(list.size(), 1);

    auto it = list.begin();
    EXPECT_EQ(*it, "mouse");
}