#include <gtest/gtest.h>
#include <string>
#include "hash_map.h"

class HashMapClearTest : public ::testing::Test
{
protected:
    HashMap<int, std::string> map;

    void SetUp() override
    {
        map.insert(1, "Oppo");
        map.insert(2, "Vivo");
        map.insert(3, "Apple");
    }
};

TEST_F(HashMapClearTest, ClearNonEmptyMap)
{
    map.clear();

    EXPECT_TRUE(map.isEmpty());
    EXPECT_EQ(map.size(), 0);
}

TEST_F(HashMapClearTest, InsertAfterClear)
{
    map.clear();

    map.insert(10, "Samsung");

    EXPECT_EQ(map.size(), 1);
    EXPECT_EQ(map.get(10), "Samsung");
}

TEST_F(HashMapClearTest, ContainsAfterClear)
{
    map.clear();

    EXPECT_FALSE(map.contains(1));
    EXPECT_FALSE(map.contains(2));
    EXPECT_FALSE(map.contains(3));
}

TEST_F(HashMapClearTest, ClearTwice)
{
    map.clear();
    map.clear();

    EXPECT_TRUE(map.isEmpty());
    EXPECT_EQ(map.size(), 0);
}

TEST(HashMap, ClearEmptyMap)
{
    HashMap<int, std::string> map;

    map.clear();

    EXPECT_TRUE(map.isEmpty());
    EXPECT_EQ(map.size(), 0);
}