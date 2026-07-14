#include <gtest/gtest.h>
#include <string>
#include "dynamic_array.h"

TEST(DynamicArray, AssignmentOperatorCreatesExactCopy)
{
    DA<int> arr1;

    arr1.append(19);
    arr1.append(26);
    arr1.append(109);

    DA<int> arr2;

    arr2 = arr1;

    EXPECT_EQ(arr2.size(), arr1.size());
    EXPECT_EQ(arr2.capacity(), arr1.capacity());

    EXPECT_EQ(arr2[0], 19);
    EXPECT_EQ(arr2[1], 26);
    EXPECT_EQ(arr2[2], 109);
}

TEST(DynamicArray, AssignmentOperatorPerformsDeepCopy)
{
    DA<int> arr1;

    arr1.append(19);
    arr1.append(26);
    arr1.append(109);

    DA<int> arr2;

    arr2 = arr1;

    arr2[1] = 230;

    EXPECT_EQ(arr1[1], 26);
    EXPECT_EQ(arr2[1], 230);
}

TEST(DynamicArray, AssignmentOperatorCopiesEmptyArray)
{
    DA<int> arr1;
    DA<int> arr2;

    arr2 = arr1;

    EXPECT_TRUE(arr2.isEmpty());
    EXPECT_EQ(arr2.size(), 0);
    EXPECT_EQ(arr2.capacity(), 0);
}

TEST(DynamicArray, AssignmentOperatorIndependentAfterInsert)
{
    DA<int> arr1;

    arr1.append(19);
    arr1.append(109);

    DA<int> arr2;

    arr2 = arr1;

    arr2.insert(1, 26);

    EXPECT_EQ(arr1.size(), 2);
    EXPECT_EQ(arr2.size(), 3);

    EXPECT_EQ(arr1[0], 19);
    EXPECT_EQ(arr1[1], 109);

    EXPECT_EQ(arr2[0], 19);
    EXPECT_EQ(arr2[1], 26);
    EXPECT_EQ(arr2[2], 109);
}

TEST(DynamicArray, AssignmentOperatorIndependentAfterRemove)
{
    DA<int> arr1;

    arr1.append(19);
    arr1.append(26);
    arr1.append(109);

    DA<int> arr2;

    arr2 = arr1;

    arr2.remove(1);

    EXPECT_EQ(arr1.size(), 3);
    EXPECT_EQ(arr2.size(), 2);

    EXPECT_EQ(arr1[1], 26);
    EXPECT_EQ(arr2[1], 109);
}

TEST(DynamicArray, SelfAssignment)
{
    DA<int> arr;

    arr.append(19);
    arr.append(26);
    arr.append(109);

    arr = arr;

    EXPECT_EQ(arr.size(), 3);

    EXPECT_EQ(arr[0], 19);
    EXPECT_EQ(arr[1], 26);
    EXPECT_EQ(arr[2], 109);
}

TEST(DynamicArray, AssignmentOperatorWithString)
{
    DA<std::string> arr1;

    arr1.append("la la la");
    arr1.append("ba ba ba");

    DA<std::string> arr2;

    arr2 = arr1;

    arr2[0] = "ba ba ba";

    EXPECT_EQ(arr1[0], "la la la");
    EXPECT_EQ(arr2[0], "ba ba ba");
}