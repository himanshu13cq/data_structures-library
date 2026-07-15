#include <gtest/gtest.h>
#include <string>
#include "hash_map.h"

class HashMapGetTest : public ::testing::Test
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

TEST_F(HashMapGetTest, GetExistingKey)
{
    EXPECT_EQ(map.get(1), "Oppo");
    EXPECT_EQ(map.get(2), "Vivo");
    EXPECT_EQ(map.get(3), "Apple");
}

TEST_F(HashMapGetTest, GetReturnsReference)
{
    map.get(2) = "Samsung";

    EXPECT_EQ(map.get(2), "Samsung");
    EXPECT_EQ(map.size(), 3);
}

TEST_F(HashMapGetTest, GetCreatesMissingKey)
{
    std::string& value = map.get(10);

    EXPECT_EQ(value, "");
    EXPECT_TRUE(map.contains(10));
    EXPECT_EQ(map.size(), 4);
}

TEST_F(HashMapGetTest, ModifyNewlyCreatedValue)
{
    map.get(100) = "Mango";

    EXPECT_TRUE(map.contains(100));
    EXPECT_EQ(map.get(100), "Mango");
    EXPECT_EQ(map.size(), 4);
}

TEST(HashMap, GetFromEmptyMap)
{
    HashMap<int, std::string> map;

    EXPECT_EQ(map.size(), 0);

    EXPECT_EQ(map.get(5), "");

    EXPECT_TRUE(map.contains(5));
    EXPECT_EQ(map.size(), 1);
}

TEST(HashMap, GetWithStringKey)
{
    HashMap<std::string, int> map;

    map.insert("Light", 10);

    EXPECT_EQ(map.get("Light"), 10);

    map.get("Berkly") = 20;

    EXPECT_TRUE(map.contains("Berkly"));
    EXPECT_EQ(map.get("Berkly"), 20);
    EXPECT_EQ(map.size(), 2);
}