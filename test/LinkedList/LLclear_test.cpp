#include <gtest/gtest.h>
#include "linked_list.h"

class LinkedListClearTest : public ::testing::Test
{
protected:
    LinkedList<int> list;

    void SetUp() override
    {
        list.insertBack(10);
        list.insertBack(20);
        list.insertBack(30);
    }
};

TEST_F(LinkedListClearTest, ClearNonEmptyList)
{
    list.clear();

    EXPECT_EQ(list.size(), 0);
}

TEST_F(LinkedListClearTest, InsertAfterClear)
{
    list.clear();

    list.insertBack(40);

    EXPECT_EQ(list.size(), 1);

    auto it = list.begin();
    EXPECT_EQ(*it, 40);
}

TEST_F(LinkedListClearTest, FindAfterClear)
{
    list.clear();

    EXPECT_EQ(list.find(10), nullptr);
    EXPECT_EQ(list.find(20), nullptr);
    EXPECT_EQ(list.find(30), nullptr);
}

TEST_F(LinkedListClearTest, ClearTwice)
{
    list.clear();
    list.clear();

    EXPECT_EQ(list.size(), 0);
}

TEST(LinkedList, ClearEmptyList)
{
    LinkedList<int> list;

    list.clear();

   
    EXPECT_EQ(list.size(), 0);
}