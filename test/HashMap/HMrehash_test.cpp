#include <gtest/gtest.h>
#include <string>
#include "hash_map.h"

class HashMapRehashTest : public ::testing::Test
{
protected:
    HashMap<int, std::string> map;
};

TEST_F(HashMapRehashTest, RehashRetainsEveryElement)
{
    for(int i = 0; i < 8; ++i)
    {
        map.insert(i, "Value" + std::to_string(i));
    }

    EXPECT_EQ(map.size(), 8);

    for(int i = 0; i < 8; ++i)
    {
        EXPECT_TRUE(map.contains(i));
        EXPECT_EQ(map.get(i), "Value" + std::to_string(i));
    }
}

TEST_F(HashMapRehashTest, RehashRedistributesCollidingKeys)
{
    map.insert(0, "Zero");
    map.insert(8, "Eight");
    map.insert(16, "Sixteen");
    map.insert(24, "TwentyFour");

    for(int i = 1; i <= 4; ++i)
    {
        map.insert(100 + i, "Dummy");
    }

    EXPECT_EQ(map.size(), 8);

    EXPECT_EQ(map.get(0), "Zero");
    EXPECT_EQ(map.get(8), "Eight");
    EXPECT_EQ(map.get(16), "Sixteen");
    EXPECT_EQ(map.get(24), "TwentyFour");
}

TEST_F(HashMapRehashTest, RehashDoesNotDuplicateElements)
{
    for(int i = 0; i < 8; ++i)
    {
        map.insert(i, "Value");
    }

    EXPECT_EQ(map.size(), 8);

    for(int i = 0; i < 8; ++i)
    {
        EXPECT_TRUE(map.contains(i));
    }
}

TEST_F(HashMapRehashTest, MultipleRehashes)
{
    for(int i = 0; i < 100; ++i)
    {
        map.insert(i, "Value" + std::to_string(i));
    }

    EXPECT_EQ(map.size(), 100);

    for(int i = 0; i < 100; ++i)
    {
        EXPECT_TRUE(map.contains(i));
        EXPECT_EQ(map.get(i), "Value" + std::to_string(i));
    }
}

TEST_F(HashMapRehashTest, OperationsContinueNormallyAfterRehash)
{
    for(int i = 0; i < 8; ++i)
    {
        map.insert(i, "Value" + std::to_string(i));
    }

    map.insert(50, "Fifty");

    map.insert(3, "Updated");

    EXPECT_TRUE(map.remove(5));

    map.get(75) = "SeventyFive";

    EXPECT_EQ(map.size(), 9);

    EXPECT_EQ(map.get(3), "Updated");
    EXPECT_EQ(map.get(50), "Fifty");
    EXPECT_EQ(map.get(75), "SeventyFive");

    EXPECT_FALSE(map.contains(5));
}

TEST(HashMap, RehashWithStringKeys)
{
    HashMap<std::string, int> map;

    for(int i = 0; i < 8; ++i)
    {
        map.insert("Key" + std::to_string(i), i);
    }

    EXPECT_EQ(map.size(), 8);

    for(int i = 0; i < 8; ++i)
    {
        EXPECT_TRUE(map.contains("Key" + std::to_string(i)));
        EXPECT_EQ(map.get("Key" + std::to_string(i)), i);
    }
}