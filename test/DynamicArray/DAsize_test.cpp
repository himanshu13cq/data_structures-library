#include <gtest/gtest.h>
#include <string>
#include "dynamic_array.h"

TEST(DynamicArray, NewArraySizeIsZero)
{
    DA<int> arr;

    EXPECT_EQ(arr.size(), 0);
}

TEST(DynamicArray, SizeAfterAppend)
{
    DA<int> arr;

    arr.append(19);
    arr.append(26);
    arr.append(109);

    EXPECT_EQ(arr.size(), 3);
}

TEST(DynamicArray, SizeAfterInsert)
{
    DA<int> arr;

    arr.append(19);
    arr.append(109);

    arr.insert(1, 26);

    EXPECT_EQ(arr.size(), 3);
}

TEST(DynamicArray, SizeAfterRemove)
{
    DA<int> arr;

    arr.append(19);
    arr.append(26);
    arr.append(109);

    arr.remove(1);

    EXPECT_EQ(arr.size(), 2);
}

TEST(DynamicArray, SizeAfterMultipleOperations)
{
    DA<int> arr;

    arr.append(10);
    arr.append(20);
    arr.append(30);

    arr.insert(1, 15);
    arr.remove(2);

    EXPECT_EQ(arr.size(), 3);
}

TEST(DynamicArray, StringArraySize)
{
    DA<std::string> arr;

    arr.append("Aaam");
    arr.append("Bandar");

    EXPECT_EQ(arr.size(), 2);
}