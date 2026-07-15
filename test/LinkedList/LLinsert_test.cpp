#include <gtest/gtest.h>
#include <string>
#include "linked_list.h"

class LinkedListInsertTest : public ::testing::Test
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

TEST_F(LinkedListInsertTest, InsertAtBeginning)
{
    list.insert(0, 230);
    EXPECT_EQ(list.size(), 4);
    int expected[] = {230, 19, 26, 109};
    int index = 0;
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}

TEST_F(LinkedListInsertTest, InsertAtMiddle)
{
    list.insert(1, 230);
    EXPECT_EQ(list.size(), 4);
    int expected[] = {19, 230, 26, 109};
    int index = 0;
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}

TEST_F(LinkedListInsertTest, InsertAtEnd)
{
    list.insert(list.size(), 230);
    EXPECT_EQ(list.size(), 4);
    int expected[] = {19, 26, 109, 230};
    int index = 0;
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}

TEST_F(LinkedListInsertTest, InsertWithNegativeIndex)
{
    EXPECT_THROW(list.insert(-1, 230), std::out_of_range);
}

TEST_F(LinkedListInsertTest, InsertWithIndexGreaterThanSize)
{
    EXPECT_THROW(list.insert(list.size() + 1, 230), std::out_of_range);
}

TEST(LinkedList, InsertIntoEmptyList)
{
    LinkedList<int> list;
    list.insert(0, 230);
    EXPECT_EQ(list.size(), 1);
    auto it = list.begin();
    EXPECT_EQ(*it, 230);
}


TEST(LinkedList, InsertStringElement)
{
    LinkedList<std::string> list;
    list.insertBack("Apple");
    list.insertBack("Cherry");
    list.insert(1, "Banana");
    EXPECT_EQ(list.size(), 3);
    std::string expected[] = {"Apple", "Banana", "Cherry"};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}