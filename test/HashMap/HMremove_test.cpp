#include <gtest/gtest.h>
#include <string>
#include "hash_map.h"

class HashMapRemoveTest : public ::testing::Test
{
protected:
    HashMap<int, std::string> map;

    void SetUp() override
    {
        map.insert(1, "Oppo");
        map.insert(2, "Vivo");
        map.insert(3, "Apple");
        map.insert(9, "Samsung"); 
    }
};

TEST_F(HashMapRemoveTest, RemoveExistingKey)
{
    EXPECT_TRUE(map.remove(2));

    EXPECT_EQ(map.size(), 3);
    EXPECT_FALSE(map.contains(2));

    EXPECT_TRUE(map.contains(1));
    EXPECT_TRUE(map.contains(3));
    EXPECT_TRUE(map.contains(9));
}

TEST_F(HashMapRemoveTest, RemoveNonExistingKey)
{
    EXPECT_FALSE(map.remove(100));

    EXPECT_EQ(map.size(), 4);

    EXPECT_TRUE(map.contains(1));
    EXPECT_TRUE(map.contains(2));
    EXPECT_TRUE(map.contains(3));
    EXPECT_TRUE(map.contains(9));
}

TEST_F(HashMapRemoveTest, RemoveKeyInCollisionChain)
{
    EXPECT_TRUE(map.remove(1));

    EXPECT_EQ(map.size(), 3);

    EXPECT_FALSE(map.contains(1));
    EXPECT_TRUE(map.contains(9));

    EXPECT_EQ(map.get(9), "Samsung");
}

TEST_F(HashMapRemoveTest, RemoveAllElements)
{
    EXPECT_TRUE(map.remove(1));
    EXPECT_TRUE(map.remove(2));
    EXPECT_TRUE(map.remove(3));
    EXPECT_TRUE(map.remove(9));

    EXPECT_TRUE(map.isEmpty());
    EXPECT_EQ(map.size(), 0);
}

TEST(HashMap, RemoveFromEmptyMap)
{
    HashMap<int, std::string> map;

    EXPECT_FALSE(map.remove(1));

    EXPECT_TRUE(map.isEmpty());
    EXPECT_EQ(map.size(), 0);
}

TEST(HashMap, RemoveStringKey)
{
    HashMap<std::string, int> map;

    map.insert("Light", 10);
    map.insert("Berkly", 20);

    EXPECT_TRUE(map.remove("Light"));

    EXPECT_EQ(map.size(), 1);

    EXPECT_FALSE(map.contains("Light"));
    EXPECT_TRUE(map.contains("Berkly"));
}