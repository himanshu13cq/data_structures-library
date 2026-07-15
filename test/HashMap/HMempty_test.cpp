#include <gtest/gtest.h>
#include <string>
#include "hash_map.h"

class HashMapIsEmptyTest : public ::testing::Test
{
protected:
    HashMap<int, std::string> map;
};

TEST_F(HashMapIsEmptyTest, EmptyAfterConstruction)
{
    EXPECT_TRUE(map.isEmpty());
    EXPECT_EQ(map.size(), 0);
}

TEST_F(HashMapIsEmptyTest, NotEmptyAfterInsertion)
{
    map.insert(1, "Oppo");

    EXPECT_FALSE(map.isEmpty());
    EXPECT_EQ(map.size(), 1);
}

TEST_F(HashMapIsEmptyTest, EmptyAfterRemovingOnlyElement)
{
    map.insert(1, "Oppo");

    map.remove(1);

    EXPECT_TRUE(map.isEmpty());
    EXPECT_EQ(map.size(), 0);
}

TEST_F(HashMapIsEmptyTest, NotEmptyAfterDuplicateInsertion)
{
    map.insert(1, "Oppo");
    map.insert(1, "Samsung");

    EXPECT_FALSE(map.isEmpty());
    EXPECT_EQ(map.size(), 1);
}

TEST(HashMap, IsEmptyWithStringKey)
{
    HashMap<std::string, int> map;

    EXPECT_TRUE(map.isEmpty());

    map.insert("Light", 10);

    EXPECT_FALSE(map.isEmpty());

    map.remove("Light");

    EXPECT_TRUE(map.isEmpty());
}