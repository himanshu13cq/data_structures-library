#include <gtest/gtest.h>
#include <string>
#include "dynamic_array.h"

class DynamicArrayOperatorTest : public ::testing::Test
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

TEST_F(DynamicArrayOperatorTest, AccessFirstElement)
{
    EXPECT_EQ(arr[0], 19);
}

TEST_F(DynamicArrayOperatorTest, AccessMiddleElement)
{
    EXPECT_EQ(arr[1], 26);
}

TEST_F(DynamicArrayOperatorTest, AccessLastElement)
{
    EXPECT_EQ(arr[2], 109);
}

TEST_F(DynamicArrayOperatorTest, ModifyElementUsingSubscriptOperator)
{
    arr[1] = 230;

    EXPECT_EQ(arr[0], 19);
    EXPECT_EQ(arr[1], 230);
    EXPECT_EQ(arr[2], 109);
}

TEST_F(DynamicArrayOperatorTest, ModifyMultipleElementsUsingSubscriptOperator)
{
    arr[0] = 100;
    arr[1] = 200;
    arr[2] = 300;

    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
    EXPECT_EQ(arr[2], 300);
}

TEST_F(DynamicArrayOperatorTest, NegativeIndexThrows)
{
    EXPECT_THROW(arr[-1], std::out_of_range);
}

TEST_F(DynamicArrayOperatorTest, IndexEqualToSizeThrows)
{
    EXPECT_THROW(arr[arr.size()], std::out_of_range);
}

TEST(DynamicArray, SubscriptOperatorOnEmptyArray)
{
    DA<int> arr;

    EXPECT_THROW(arr[0], std::out_of_range);
}

TEST(DynamicArray, ModifyStringUsingSubscriptOperator)
{
    DA<std::string> arr;

    arr.append("Apple");
    arr.append("Banana");

    arr[0] = "Orange";
    arr[1] = "Mango";

    EXPECT_EQ(arr[0], "Orange");
    EXPECT_EQ(arr[1], "Mango");
}