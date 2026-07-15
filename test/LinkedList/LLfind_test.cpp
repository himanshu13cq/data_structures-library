#include <gtest/gtest.h>
#include <string>
#include "linked_list.h"

class LinkedListFindTest : public ::testing::Test
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

TEST_F(LinkedListFindTest, FindFirstElement)
{
    int* value = list.find(19);
    EXPECT_NE(value, nullptr);
    EXPECT_EQ(*value, 19);
}

TEST_F(LinkedListFindTest, FindMiddleElement)
{
    int* value = list.find(26);
    EXPECT_NE(value, nullptr);
    EXPECT_EQ(*value, 26);
}

TEST_F(LinkedListFindTest, FindLastElement)
{
    int* value = list.find(109);

    EXPECT_NE(value, nullptr);
    EXPECT_EQ(*value, 109);
}

TEST_F(LinkedListFindTest, FindValueNotPresent)
{
    EXPECT_EQ(list.find(230), nullptr);
}

TEST(LinkedList, FindInEmptyList)
{
    LinkedList<int> list;

    EXPECT_EQ(list.find(19), nullptr);
}

TEST(LinkedList, FindStringElement)
{
    LinkedList<std::string> list;

    list.insertBack("ID");
    list.insertBack("Banana");
    list.insertBack("Card");

    std::string* value = list.find("Banana");

    EXPECT_NE(value, nullptr);
    EXPECT_EQ(*value, "Banana");
}