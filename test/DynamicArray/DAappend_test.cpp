#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "dynamic_array.h"

class DynamicArrayAppendTest:public::testing::Test
{
protected:
    DA<int> arr;

    void SetUp() override
    {
        arr.append(19);
        arr.append(26);
        arr.append(109);
    }
};

TEST(DynamicArrayAppendStandalone,AppendToEmptyArray)
{
    DA<int> arr;

    arr.append(42);

    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 42);
}

TEST_F(DynamicArrayAppendTest,AppendPreservesExistingOrder)
{
    arr.append(500);

    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0], 19);
    EXPECT_EQ(arr[1], 26);
    EXPECT_EQ(arr[2], 109);
    EXPECT_EQ(arr[3], 500);
}

TEST(DynamicArrayAppendStandalone,AppendTriggersResizeFromEmpty)
{
    DA<int> arr;
    int oldCap = arr.capacity();

    arr.append(1);

    EXPECT_GT(arr.capacity(), oldCap);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 1);
}

TEST(DynamicArrayAppendStandalone,AppendTriggersResizeWhenFull)
{
    DA<int> arr;
    arr.append(1);
    arr.append(2);

    int oldCap = arr.capacity();
    ASSERT_EQ(arr.size(), arr.capacity());

    arr.append(3);

    EXPECT_GT(arr.capacity(), oldCap);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0],1);
    EXPECT_EQ(arr[1],2);
    EXPECT_EQ(arr[2],3);
}

TEST(DynamicArrayAppendStandalone, AppendDoesNotTouchExistingElementsOnResize)
{
    DA<int> arr;
    for(int i = 0; i < 10; ++i)
    {
        arr.append(i);
    }

    for(int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr[i], i);
    }
}

TEST(DynamicArrayAppendNonTrivialType, AppendWithSlackCapacityDoesNotCrash)
{
    DA<std::string> arr;
    arr.append("a");
    arr.append("b");
    arr.append("c");

    ASSERT_GT(arr.capacity(), arr.size());

    arr.append("d");

    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0], "a");
    EXPECT_EQ(arr[1], "b");
    EXPECT_EQ(arr[2], "c");
    EXPECT_EQ(arr[3], "d");
}

TEST(DynamicArrayAppendStandalone, AppendLargeDataset)
{
    DA<int> arr;
    for(int i = 0; i < 1000; ++i)
    {
        arr.append(i);
    }

    EXPECT_EQ(arr.size(), 1000);
    for(int i = 0; i < 1000; ++i)
    {
        EXPECT_EQ(arr[i], i);
    }
}