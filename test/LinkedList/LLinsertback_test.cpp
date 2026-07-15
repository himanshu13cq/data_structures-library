#include <gtest/gtest.h>
#include <string>
#include "linked_list.h"

class LinkedListInsertBackTest : public ::testing::Test
{
protected:
    LinkedList<int> list;
};

TEST_F(LinkedListInsertBackTest, InsertSingleElement)
{
    list.insertBack(19);

    EXPECT_EQ(list.size(), 1);

    int* value = list.find(19);

    EXPECT_NE(value, nullptr);
    EXPECT_EQ(*value, 19);
}

TEST_F(LinkedListInsertBackTest, InsertMultipleElements)
{
    list.insertBack(19);
    list.insertBack(26);
    list.insertBack(109);

    EXPECT_EQ(list.size(), 3);

    int expected[] = {19, 26, 109};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}

TEST_F(LinkedListInsertBackTest, InsertDuplicateElements)
{
    list.insertBack(19);
    list.insertBack(19);

    EXPECT_EQ(list.size(), 2);

    EXPECT_NE(list.find(19), nullptr);
}

TEST_F(LinkedListInsertBackTest, SizeIncreasesAfterInsertion)
{
    EXPECT_EQ(list.size(), 0);

    list.insertBack(10);
    EXPECT_EQ(list.size(), 1);

    list.insertBack(20);
    EXPECT_EQ(list.size(), 2);

    list.insertBack(30);
    EXPECT_EQ(list.size(), 3);
}

TEST_F(LinkedListInsertBackTest, InsertMaintainsInsertionOrder)
{
    list.insertBack(100);
    list.insertBack(200);
    list.insertBack(300);
    list.insertBack(400);

    int expected[] = {100, 200, 300, 400};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}

TEST(LinkedList, InsertBackWithString)
{
    LinkedList<std::string> list;

    list.insertBack("Ample");
    list.insertBack("Banana");

    EXPECT_EQ(list.size(), 2);

    std::string expected[] = {"Ample", "Banana"};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}