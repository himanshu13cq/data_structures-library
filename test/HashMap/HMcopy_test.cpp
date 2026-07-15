#include <gtest/gtest.h>
#include <string>
#include "hash_map.h"

class HashMapCopyConstructorTest : public ::testing::Test
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

TEST_F(HashMapCopyConstructorTest, CopyEmptyMap)
{
    HashMap<int, std::string> empty;
    HashMap<int, std::string> copy(empty);

    EXPECT_TRUE(copy.isEmpty());
    EXPECT_EQ(copy.size(), 0);
}

TEST_F(HashMapCopyConstructorTest, CopyPreservesAllElements)
{
    HashMap<int, std::string> copy(map);

    EXPECT_EQ(copy.size(), map.size());

    EXPECT_EQ(copy.get(1), "Oppo");
    EXPECT_EQ(copy.get(2), "Vivo");
    EXPECT_EQ(copy.get(3), "Apple");
}

TEST_F(HashMapCopyConstructorTest, OriginalModificationDoesNotAffectCopy)
{
    HashMap<int, std::string> copy(map);

    map.insert(4, "Samsung");
    map.insert(2, "OnePlus");
    map.remove(1);

    EXPECT_EQ(copy.size(), 3);

    EXPECT_TRUE(copy.contains(1));
    EXPECT_TRUE(copy.contains(2));
    EXPECT_TRUE(copy.contains(3));

    EXPECT_EQ(copy.get(2), "Vivo");
    EXPECT_FALSE(copy.contains(4));
}

TEST_F(HashMapCopyConstructorTest, CopyModificationDoesNotAffectOriginal)
{
    HashMap<int, std::string> copy(map);

    copy.insert(4, "Samsung");
    copy.insert(3, "Google");
    copy.remove(1);

    EXPECT_EQ(map.size(), 3);

    EXPECT_TRUE(map.contains(1));
    EXPECT_FALSE(map.contains(4));
    EXPECT_EQ(map.get(3), "Apple");
}

TEST_F(HashMapCopyConstructorTest, CopyAfterRehash)
{
    for(int i = 4; i < 20; ++i)
    {
        map.insert(i, "Value" + std::to_string(i));
    }

    HashMap<int, std::string> copy(map);

    EXPECT_EQ(copy.size(), map.size());

    for(int i = 1; i < 20; ++i)
    {
        EXPECT_TRUE(copy.contains(i));
    }
}

TEST(HashMap, CopyConstructorWithStringKeys)
{
    HashMap<std::string, int> map;

    map.insert("Light", 10);
    map.insert("Berkly", 20);

    HashMap<std::string, int> copy(map);

    EXPECT_EQ(copy.size(), 2);

    EXPECT_EQ(copy.get("Light"), 10);
    EXPECT_EQ(copy.get("Berkly"), 20);
}