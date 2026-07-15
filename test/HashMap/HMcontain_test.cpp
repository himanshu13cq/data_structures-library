#include <gtest/gtest.h>
#include <string>
#include "hash_map.h"

class HashMapContainsTest : public ::testing::Test
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

TEST_F(HashMapContainsTest, ContainsExistingKey)
{
    EXPECT_TRUE(map.contains(1));
    EXPECT_TRUE(map.contains(2));
    EXPECT_TRUE(map.contains(3));
}

TEST_F(HashMapContainsTest, ContainsNonExistingKey)
{
    EXPECT_FALSE(map.contains(10));
    EXPECT_FALSE(map.contains(20));
}

TEST_F(HashMapContainsTest, ContainsAfterInsertion)
{
    EXPECT_FALSE(map.contains(100));

    map.insert(100, "Samsung");

    EXPECT_TRUE(map.contains(100));
}

TEST_F(HashMapContainsTest, ContainsAfterRemoval)
{
    EXPECT_TRUE(map.contains(2));

    map.remove(2);

    EXPECT_FALSE(map.contains(2));
}

TEST(HashMap, ContainsOnEmptyMap)
{
    HashMap<int, std::string> map;

    EXPECT_FALSE(map.contains(1));
}

TEST(HashMap, ContainsWithStringKey)
{
    HashMap<std::string, int> map;

    map.insert("Light", 10);
    map.insert("Berkly", 20);

    EXPECT_TRUE(map.contains("Light"));
    EXPECT_TRUE(map.contains("Berkly"));
    EXPECT_FALSE(map.contains("Apple"));
}