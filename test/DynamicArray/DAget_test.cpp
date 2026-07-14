#include <gtest/gtest.h>
#include <string>
#include "dynamic_array.h"

class DynamicArrayGetTest : public ::testing::Test
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

TEST_F(DynamicArrayGetTest, GetFirstElement)
{
    EXPECT_EQ(arr.get(0), 19);
}

TEST_F(DynamicArrayGetTest, GetMiddleElement)
{
    EXPECT_EQ(arr.get(1), 26);
}

TEST_F(DynamicArrayGetTest, GetLastElement)
{
    EXPECT_EQ(arr.get(2), 109);
}

TEST_F(DynamicArrayGetTest, GetNegativeIndex)
{
    EXPECT_THROW(arr.get(-1), std::out_of_range);
}

TEST_F(DynamicArrayGetTest, GetIndexEqualToSize)
{
    EXPECT_THROW(arr.get(arr.size()), std::out_of_range);
}

TEST(DynamicArray, GetFromEmptyArray)
{
    DA<int> arr;

    EXPECT_THROW(arr.get(0), std::out_of_range);
}

TEST(DynamicArray, GetStringElements)
{
    DA<std::string> arr;

    arr.append("Aasman");
    arr.append("Bandar");
    arr.append("Chaand");

    EXPECT_EQ(arr.get(0), "Aasman");
    EXPECT_EQ(arr.get(1), "Bandar");
    EXPECT_EQ(arr.get(2), "Chaand");
}

TEST(DynamicArray, GetStringInvalidIndex)
{
    DA<std::string> arr;

    arr.append("anar");

    EXPECT_THROW(arr.get(arr.size()), std::out_of_range);
}