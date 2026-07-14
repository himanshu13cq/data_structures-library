#include <gtest/gtest.h>
#include <string>
#include "dynamic_array.h"

TEST(DynamicArray, CopyConstructorCreatesExactCopy)
{
    DA<int> arr;

    arr.append(19);
    arr.append(26);
    arr.append(109);

    DA<int> copy(arr);

    EXPECT_EQ(copy.size(), arr.size());
    EXPECT_EQ(copy.capacity(), arr.capacity());

    EXPECT_EQ(copy[0], 19);
    EXPECT_EQ(copy[1], 26);
    EXPECT_EQ(copy[2], 109);
}

TEST(DynamicArray, CopyConstructorPerformsDeepCopy)
{
    DA<int> arr;

    arr.append(19);
    arr.append(26);
    arr.append(109);

    DA<int> copy(arr);

    copy[1] = 230;

    EXPECT_EQ(arr[1], 26);
    EXPECT_EQ(copy[1], 230);
}

TEST(DynamicArray, CopyConstructorCopiesEmptyArray)
{
    DA<int> arr;

    DA<int> copy(arr);

    EXPECT_EQ(copy.size(), 0);
    EXPECT_EQ(copy.capacity(), 0);
    EXPECT_TRUE(copy.isEmpty());
}

TEST(DynamicArray, CopyConstructorIndependentAfterRemove)
{
    DA<int> arr;

    arr.append(19);
    arr.append(26);
    arr.append(109);

    DA<int> copy(arr);

    copy.remove(1);

    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(copy.size(), 2);

    EXPECT_EQ(arr[1], 26);
    EXPECT_EQ(copy[1], 109);
}

TEST(DynamicArray, CopyConstructorIndependentAfterInsert)
{
    DA<int> arr;

    arr.append(19);
    arr.append(109);

    DA<int> copy(arr);

    copy.insert(1, 26);

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(copy.size(), 3);

    EXPECT_EQ(arr[0], 19);
    EXPECT_EQ(arr[1], 109);

    EXPECT_EQ(copy[0], 19);
    EXPECT_EQ(copy[1], 26);
    EXPECT_EQ(copy[2], 109);
}

TEST(DynamicArray, CopyConstructorWithString)
{
    DA<std::string> arr;

    arr.append("aaloo");
    arr.append("Baingan");

    DA<std::string> copy(arr);

    copy[0] = "Baingan";

    EXPECT_EQ(arr[0], "aaloo");
    EXPECT_EQ(copy[0], "Baingan");
}