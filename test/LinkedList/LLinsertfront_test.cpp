#include <gtest/gtest.h>
#include <string>
#include "linked_list.h"

class LinkedListInsertFrontTest : public ::testing::Test
{
protected:
    LinkedList<int> list;
};

TEST_F(LinkedListInsertFrontTest, InsertSingleElement)
{
    list.insertFront(19);

    EXPECT_EQ(list.size(), 1);

    int* value = list.find(19);

    EXPECT_NE(value, nullptr);
    EXPECT_EQ(*value, 19);
}

TEST_F(LinkedListInsertFrontTest, InsertMultipleElements)
{
    list.insertFront(19);
    list.insertFront(26);
    list.insertFront(109);

    EXPECT_EQ(list.size(), 3);

    int expected[] = {109, 26, 19};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}

TEST_F(LinkedListInsertFrontTest, InsertDuplicateElements)
{
    list.insertFront(19);
    list.insertFront(19);

    EXPECT_EQ(list.size(), 2);

    EXPECT_NE(list.find(19), nullptr);
}

TEST_F(LinkedListInsertFrontTest, SizeIncreasesAfterInsertion)
{
    EXPECT_EQ(list.size(), 0);

    list.insertFront(10);
    EXPECT_EQ(list.size(), 1);

    list.insertFront(20);
    EXPECT_EQ(list.size(), 2);

    list.insertFront(30);
    EXPECT_EQ(list.size(), 3);
}


TEST(LinkedList, InsertFrontWithString)
{
    LinkedList<std::string> list;

    list.insertFront("Code");
    list.insertFront("Quotient");

    EXPECT_EQ(list.size(), 2);

    std::string expected[] = {"Quotient", "Code"};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}