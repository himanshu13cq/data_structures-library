#include <gtest/gtest.h>
#include <string>
#include "linked_list.h"

class LinkedListDeleteAtTest : public ::testing::Test
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

TEST_F(LinkedListDeleteAtTest, DeleteFirstElement)
{
    list.deleteAt(0);
    EXPECT_EQ(list.size(), 2);
    int expected[] = {26, 109};
    int index = 0;
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}

TEST_F(LinkedListDeleteAtTest, DeleteMiddleElement)
{
    list.insertBack(230);

    list.deleteAt(1);

    EXPECT_EQ(list.size(), 3);

    int expected[] = {19, 109, 230};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}

TEST_F(LinkedListDeleteAtTest, DeleteLastElement)
{
    list.deleteAt(2);

    EXPECT_EQ(list.size(), 2);

    int expected[] = {19, 26};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}

TEST(LinkedList, DeleteOnlyElementUsingDeleteAt)
{
    LinkedList<int> list;

    list.insertBack(19);

    list.deleteAt(0);

    EXPECT_EQ(list.size(), 0);
    EXPECT_FALSE(list.begin() != list.end());
}

TEST_F(LinkedListDeleteAtTest, DeleteNegativeIndex)
{
    EXPECT_THROW(list.deleteAt(-1), std::out_of_range);
}

TEST_F(LinkedListDeleteAtTest, DeleteIndexEqualToSize)
{
    EXPECT_THROW(list.deleteAt(list.size()), std::out_of_range);
}

TEST(LinkedList, DeleteStringElementUsingDeleteAt)
{
    LinkedList<std::string> list;

    list.insertBack("Aaam");
    list.insertBack("kela");
    list.insertBack("nimbu");

    list.deleteAt(1);

    EXPECT_EQ(list.size(), 2);

    std::string expected[] = {"Aaam", "nimbu"};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}