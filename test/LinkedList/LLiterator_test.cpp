#include <gtest/gtest.h>
#include <string>
#include "linked_list.h"

class LinkedListIteratorTest : public ::testing::Test
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

TEST_F(LinkedListIteratorTest, TraverseEntireList)
{
    int expected[] = {19, 26, 109};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index]);
        index++;
    }

    EXPECT_EQ(index, 3);
}

TEST_F(LinkedListIteratorTest, IteratorVisitsEveryElementExactlyOnce)
{
    int count = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        count++;
    }

    EXPECT_EQ(count, list.size());
}

TEST(LinkedList, IteratorOnEmptyList)
{
    LinkedList<int> list;

    int count = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        count++;
    }

    EXPECT_EQ(count, 0);
}

TEST_F(LinkedListIteratorTest, ModifyElementsUsingIterator)
{
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        *it *= 10;
    }

    int expected[] = {190, 260, 1090};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}


TEST(LinkedList, TraverseStringList)
{
    LinkedList<std::string> list;

    list.insertBack("Apple");
    list.insertBack("Banana");
    list.insertBack("Cherry");

    std::string expected[] = {"Apple", "Banana", "Cherry"};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }

    EXPECT_EQ(index, 3);
}