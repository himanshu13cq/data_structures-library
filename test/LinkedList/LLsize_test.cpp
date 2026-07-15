#include <gtest/gtest.h>
#include <string>
#include "linked_list.h"

TEST(LinkedList, NewListSizeIsZero)
{
    LinkedList<int> list;

    EXPECT_EQ(list.size(), 0);
}

TEST(LinkedList, SizeAfterInsertFront)
{
    LinkedList<int> list;

    list.insertFront(19);
    list.insertFront(26);
    list.insertFront(109);

    EXPECT_EQ(list.size(), 3);
}

TEST(LinkedList, SizeAfterInsertBack)
{
    LinkedList<int> list;

    list.insertBack(19);
    list.insertBack(26);
    list.insertBack(109);

    EXPECT_EQ(list.size(), 3);
}

TEST(LinkedList, SizeAfterInsertAt)
{
    LinkedList<int> list;

    list.insertBack(19);
    list.insertBack(109);

    list.insert(1, 26);

    EXPECT_EQ(list.size(), 3);
}

TEST(LinkedList, SizeAfterDeleteOperations)
{
    LinkedList<int> list;

    list.insertBack(19);
    list.insertBack(26);
    list.insertBack(109);

    list.deleteFront();
    EXPECT_EQ(list.size(), 2);

    list.deleteAt(1);
    EXPECT_EQ(list.size(), 1);

    list.deleteValue(26);
    EXPECT_EQ(list.size(), 0);
}

TEST(LinkedList, StringListSize)
{
    LinkedList<std::string> list;

    list.insertBack("Apple");
    list.insertBack("Banana");

    EXPECT_EQ(list.size(), 2);
}