#include <gtest/gtest.h>
#include <string>
#include "hash_map.h"

class HashMapInsertTest : public :: testing::Test
{
    protected:
        HashMap<int, std::string> map;
};

TEST_F(HashMapInsertTest, InsertSingleElement)
{
    map.insert(1,"Laptop");
    EXPECT_EQ(map.size(), 1);
    EXPECT_TRUE(map.contains(1));
    EXPECT_EQ(map.get(1), "Laptop");
}

TEST_F(HashMapInsertTest, InsertMultipleElements)
{
    map.insert(1, "Hello");
    map.insert(2, "Aarzu");
    map.insert(3, "Eyes");

    EXPECT_EQ(map.size(), 3);

    EXPECT_EQ(map.get(1), "Hello");
    EXPECT_EQ(map.get(2), "Aarzu");
    EXPECT_EQ(map.get(3), "Eyes");
}

TEST_F(HashMapInsertTest, InsertDuplicateKeyUpdatesValue)
{
    map.insert(1, "Ear");
    map.insert(1, "time");

    EXPECT_EQ(map.size(), 1);

    EXPECT_TRUE(map.contains(1));
    EXPECT_EQ(map.get(1), "time");
}

TEST_F(HashMapInsertTest, InsertKeysWithCollision)
{
    map.insert(1, "Apple");
    map.insert(9, "Banana");

    EXPECT_EQ(map.size(), 2);

    EXPECT_EQ(map.get(1), "Apple");
    EXPECT_EQ(map.get(9), "Banana");
}

TEST_F(HashMapInsertTest, InsertManyElements)
{
    for(int i = 0; i < 7; ++i)
    {
        map.insert(i, std::to_string(i));
    }
    EXPECT_EQ(map.size(), 7);
    for(int i = 0; i < 7; ++i)
    {
        EXPECT_TRUE(map.contains(i));
        EXPECT_EQ(map.get(i), std::to_string(i));
    }
}

TEST(HashMap, InsertStringKeys)
{
    HashMap<std::string, int> map;

    map.insert("Himanshu", 19);
    map.insert("Divyansh", 17);

    EXPECT_EQ(map.size(), 2);

    EXPECT_TRUE(map.contains("Himanshu"));
    EXPECT_TRUE(map.contains("Divyansh"));

    EXPECT_EQ(map.get("Himanshu"), 19);
    EXPECT_EQ(map.get("Divyansh"), 17);
}