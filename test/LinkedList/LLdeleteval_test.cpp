#include <gtest/gtest.h>
#include <string>
#include "linked_list.h"

class LinkedListDeleteValueTest : public ::testing::Test
{
protected:
    LinkedList<int> list;
    void SetUp() override
    {
        list.insertBack(19);
        list.insertBack(26);
        list.insertBack(109);
        list.insertBack(230);
    }
};

TEST_F(LinkedListDeleteValueTest, DeleteFirstValue)
{
    EXPECT_TRUE(list.deleteValue(19));
    EXPECT_EQ(list.size(), 3);
    int expected[] = {26, 109, 230};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}

TEST_F(LinkedListDeleteValueTest, DeleteMiddleValue)
{
    EXPECT_TRUE(list.deleteValue(26));

    EXPECT_EQ(list.size(), 3);

    int expected[] = {19, 109, 230};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}

TEST_F(LinkedListDeleteValueTest, DeleteLastValue)
{
    EXPECT_TRUE(list.deleteValue(230));

    EXPECT_EQ(list.size(), 3);

    int expected[] = {19, 26, 109};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}

TEST_F(LinkedListDeleteValueTest, DeleteValueNotPresent)
{
    EXPECT_FALSE(list.deleteValue(500));

    EXPECT_EQ(list.size(), 4);

    int expected[] = {19, 26, 109, 230};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}

TEST(LinkedList, DeleteOnlyValue)
{
    LinkedList<int> list;

    list.insertBack(19);

    EXPECT_TRUE(list.deleteValue(19));

    EXPECT_EQ(list.size(), 0);
    EXPECT_FALSE(list.begin() != list.end());
}

TEST(LinkedList, DeleteStringValue)
{
    LinkedList<std::string> list;

    list.insertBack("Time");
    list.insertBack("is");
    list.insertBack("Money");

    EXPECT_TRUE(list.deleteValue("Money"));

    EXPECT_EQ(list.size(), 2);

    std::string expected[] = {"Time", "is"};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}