#include <gtest/gtest.h>
#include <string>
#include "dynamic_array.h"

TEST(DynamicArray, NewArrayIsEmpty)
{
    DA<int> arr;

    EXPECT_TRUE(arr.isEmpty());
}

TEST(DynamicArray, ArrayIsNotEmptyAfterAppend)
{
    DA<int> arr;

    arr.append(19);

    EXPECT_FALSE(arr.isEmpty());
}

TEST(DynamicArray, ArrayBecomesEmptyAfterRemovingAllElements)
{
    DA<int> arr;

    arr.append(19);
    arr.append(26);

    arr.remove(0);
    arr.remove(0);

    EXPECT_TRUE(arr.isEmpty());
}

TEST(DynamicArray, InsertMakesArrayNonEmpty)
{
    DA<int> arr;

    arr.insert(0, 100);

    EXPECT_FALSE(arr.isEmpty());
}

TEST(DynamicArray, StringArrayIsEmpty)
{
    DA<std::string> arr;

    EXPECT_TRUE(arr.isEmpty());
}

TEST(DynamicArray, StringArrayIsNotEmptyAfterAppend)
{
    DA<std::string> arr;

    arr.append("Apple");

    EXPECT_FALSE(arr.isEmpty());
}