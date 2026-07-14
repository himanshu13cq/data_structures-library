#include <gtest/gtest.h>
#include <string>
#include "dynamic_array.h"

TEST(DynamicArray, InitialCapacityIsZero)
{
    DA<int> arr;

    EXPECT_EQ(arr.capacity(), 0);
}

TEST(DynamicArray, CapacityIncreasesAfterFirstAppend)
{
    DA<int> arr;

    arr.append(19);

    EXPECT_GT(arr.capacity(), 0);
}

TEST(DynamicArray, CapacityNeverLessThanSize)
{
    DA<int> arr;

    for(int i = 0; i < 10; i++)
    {
        arr.append(i);
    }

    EXPECT_GE(arr.capacity(), arr.size());
}

TEST(DynamicArray, CapacityDoesNotDecreaseAfterRemove)
{
    DA<int> arr;

    for(int i = 0; i < 5; i++)
    {
        arr.append(i);
    }

    int oldCapacity = arr.capacity();

    arr.remove(2);

    EXPECT_EQ(arr.capacity(), oldCapacity);
}

TEST(DynamicArray, CapacityAfterMultipleOperations)
{
    DA<int> arr;

    arr.append(10);
    arr.append(20);
    arr.append(30);

    arr.insert(1, 15);
    arr.remove(0);

    EXPECT_GE(arr.capacity(), arr.size());
}

TEST(DynamicArray, StringArrayCapacity)
{
    DA<std::string> arr;

    arr.append("Apple");

    EXPECT_GT(arr.capacity(), 0);
}