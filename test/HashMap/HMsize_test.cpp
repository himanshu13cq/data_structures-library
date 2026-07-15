#include <gtest/gtest.h>
#include <string>
#include "hash_map.h"

class HashMapSizeTest : public ::testing::Test
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

TEST_F(HashMapSizeTest, SizeAfterConstruction)
{
    HashMap<int, std::string> emptyMap;
    EXPECT_EQ(emptyMap.size(), 0);
}

TEST_F(HashMapSizeTest, SizeAfterInsertion)
{
    EXPECT_EQ(map.size(), 3);
    map.insert(4, "Samsung");
    EXPECT_EQ(map.size(), 4);
}

TEST_F(HashMapSizeTest, SizeAfterDuplicateInsertion)
{
    map.insert(2, "OnePlus");
    EXPECT_EQ(map.size(), 3);
}

TEST_F(HashMapSizeTest, SizeAfterRemoval)
{
    map.remove(2);
    EXPECT_EQ(map.size(), 2);
}

TEST_F(HashMapSizeTest, SizeAfterGetCreatesNewKey)
{
    map.get(10);
    EXPECT_EQ(map.size(), 4);
}

TEST(HashMap, SizeWithStringKey)
{
    HashMap<std::string, int> map;

    EXPECT_EQ(map.size(), 0);

    map.insert("Light", 10);
    map.insert("Berkly", 20);

    EXPECT_EQ(map.size(), 2);

    map.remove("Light");

    EXPECT_EQ(map.size(), 1);
}