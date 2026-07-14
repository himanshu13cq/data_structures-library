#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "dynamic_array.h"

class DynamicArrayRemoveTest:public::testing::Test
{
protected:
    DA<int> arr;
    void SetUp() override
    {
        arr.append(10);
        arr.append(20);
        arr.append(30);
        arr.append(40);
        arr.append(50);
    }
};

TEST_F(DynamicArrayRemoveTest,RemoveFromBeginning)
{
    arr.remove(0);

    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0], 20);
    EXPECT_EQ(arr[1], 30);
    EXPECT_EQ(arr[2], 40);
    EXPECT_EQ(arr[3], 50);
}

TEST_F(DynamicArrayRemoveTest, RemoveFromMiddle)
{
    arr.remove(2);

    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 40);
    EXPECT_EQ(arr[3], 50);
}

TEST_F(DynamicArrayRemoveTest, RemoveFromEnd)
{
    arr.remove(arr.size() - 1);

    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
    EXPECT_EQ(arr[3], 40);
}

TEST_F(DynamicArrayRemoveTest, RemoveNegativeIndexThrows)
{
    EXPECT_THROW(arr.remove(-1), std::out_of_range);
}

TEST_F(DynamicArrayRemoveTest, RemoveIndexEqualToSizeThrows)
{
    EXPECT_THROW(arr.remove(arr.size()), std::out_of_range);
}

TEST_F(DynamicArrayRemoveTest, RemoveIndexPastEndThrows)
{
    EXPECT_THROW(arr.remove(arr.size() + 5), std::out_of_range);
}

TEST(DynamicArrayRemoveStandalone, RemoveFromEmptyArrayThrows)
{
    DA<int> arr;
    EXPECT_THROW(arr.remove(0), std::out_of_range);
}

TEST(DynamicArrayRemoveStandalone, RemoveOnlyElementLeavesArrayEmpty)
{
    DA<int> arr;
    arr.append(99);

    arr.remove(0);

    EXPECT_EQ(arr.size(), 0);
    EXPECT_TRUE(arr.isEmpty());
}

TEST(DynamicArrayRemoveNonTrivialType, RemoveShiftsWithoutCrashing)
{
    DA<std::string> arr;
    arr.append("a");
    arr.append("b");
    arr.append("c");
    arr.append("d");

    arr.remove(1);

    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], "a");
    EXPECT_EQ(arr[1], "c");
    EXPECT_EQ(arr[2], "d");
}

TEST(DynamicArrayRemoveStandalone, RemoveLargeDataset)
{
    DA<int> arr;
    for(int i = 0; i < 1000; ++i)
    {
        arr.append(i);
    }
    arr.remove(500);

    EXPECT_EQ(arr.size(), 999);
    for(int i = 0; i < 500; ++i)
    {
        EXPECT_EQ(arr[i], i);
    }
    for(int i = 500; i < 999; ++i)
    {
        EXPECT_EQ(arr[i], i + 1);
    }
}