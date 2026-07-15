#include <gtest/gtest.h>
#include <string>
#include "linked_list.h"

TEST(LinkedList, AssignmentOperatorCreatesExactCopy)
{
    LinkedList<int> list1;
    list1.insertBack(19);
    list1.insertBack(26);
    list1.insertBack(109);

    LinkedList<int> list2;
    list2 = list1;

    EXPECT_EQ(list2.size(), list1.size());

    auto it1 = list1.begin();
    auto it2 = list2.begin();

    while(it1 != list1.end() && it2 != list2.end())
    {
        EXPECT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }
}

TEST(LinkedList, AssignmentOperatorPerformsDeepCopy)
{
    LinkedList<int> list1;

    list1.insertBack(19);
    list1.insertBack(26);
    list1.insertBack(109);

    LinkedList<int> list2;

    list2 = list1;

    list2.deleteFront();
    list2.insertBack(230);

    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list2.size(), 3);

    int expected1[] = {19, 26, 109};
    int index = 0;

    for(auto it = list1.begin(); it != list1.end(); ++it)
    {
        EXPECT_EQ(*it, expected1[index++]);
    }

    int expected2[] = {26, 109, 230};
    index = 0;

    for(auto it = list2.begin(); it != list2.end(); ++it)
    {
        EXPECT_EQ(*it, expected2[index++]);
    }
}

TEST(LinkedList, AssignmentOperatorCopiesEmptyList)
{
    LinkedList<int> list1;
    LinkedList<int> list2;

    list2 = list1;

    EXPECT_EQ(list2.size(), 0);

    int count = 0;

    for(auto it = list2.begin(); it != list2.end(); ++it)
    {
        count++;
    }

    EXPECT_EQ(count, 0);
}

TEST(LinkedList, AssignmentOperatorListsRemainIndependent)
{
    LinkedList<int> list1;

    list1.insertBack(19);
    list1.insertBack(26);

    LinkedList<int> list2;

    list2 = list1;

    list2.insertFront(10);

    EXPECT_EQ(list1.size(), 2);
    EXPECT_EQ(list2.size(), 3);

    int expected1[] = {19, 26};
    int index = 0;
    for(auto it = list1.begin(); it != list1.end(); ++it)
    {
        EXPECT_EQ(*it, expected1[index++]);
    }

    int expected2[] = {10, 19, 26};
    index = 0;

    for(auto it = list2.begin(); it != list2.end(); ++it)
    {
        EXPECT_EQ(*it, expected2[index++]);
    }
}

TEST(LinkedList, SelfAssignment)
{
    LinkedList<int> list;

    list.insertBack(19);
    list.insertBack(26);
    list.insertBack(109);

    list = list;

    EXPECT_EQ(list.size(), 3);

    int expected[] = {19, 26, 109};
    int index = 0;

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}


TEST(LinkedList, AssignmentOperatorWithString)
{
    LinkedList<std::string> list1;

    list1.insertBack("Apple");
    list1.insertBack("Banana");

    LinkedList<std::string> list2;

    list2 = list1;

    list2.deleteFront();
    list2.insertBack("Cherry");

    EXPECT_EQ(list1.size(), 2);
    EXPECT_EQ(list2.size(), 2);

    std::string expected[] = {"Banana", "Cherry"};
    int index = 0;

    for(auto it = list2.begin(); it != list2.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index++]);
    }
}