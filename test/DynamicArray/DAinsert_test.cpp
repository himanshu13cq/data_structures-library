#include <gtest/gtest.h>
#include <stdexcept>
#include "dynamic_array.h"

class DynamicArrayInsertTest : public ::testing::Test
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

TEST_F(DynamicArrayInsertTest, InsertAtBeginning)
{
    arr.insert(0, 230);

    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0],230);
    EXPECT_EQ(arr[1],19);
    EXPECT_EQ(arr[2],26);
    EXPECT_EQ(arr[3],109);
}

TEST_F(DynamicArrayInsertTest, InsertAtMiddle)
{
    arr.insert(1,89);

    EXPECT_EQ(arr.size(),4);
    EXPECT_EQ(arr[0],19);
    EXPECT_EQ(arr[1],89);
    EXPECT_EQ(arr[2],26);
    EXPECT_EQ(arr[3],109);
}

TEST_F(DynamicArrayInsertTest, InsertAtEnd)
{
    arr.insert(arr.size(),500);

    EXPECT_EQ(arr.size(),4);
    EXPECT_EQ(arr[0],19);
    EXPECT_EQ(arr[1],26);
    EXPECT_EQ(arr[2],109);
    EXPECT_EQ(arr[3],500);
}

TEST(DynamicArray, InsertIntoEmptyArray)
{
    DA<int> arr;

    arr.insert(0,10);

    EXPECT_EQ(arr.size(),1);
    EXPECT_EQ(arr[0],10);
}

TEST_F(DynamicArrayInsertTest, InsertWithNegativeIndex)
{
    EXPECT_THROW(arr.insert(-1,100), std::out_of_range);
}

TEST_F(DynamicArrayInsertTest, InsertWithIndexGreaterThanSize)
{
    EXPECT_THROW(arr.insert(arr.size() + 1,100), std::out_of_range);
}