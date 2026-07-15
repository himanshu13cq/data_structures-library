#include <gtest/gtest.h>
#include <string>
#include "hash_map.h"

class HashMapAssignmentOperatorTest : public ::testing::Test
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

TEST_F(HashMapAssignmentOperatorTest, AssignEmptyMap)
{
    HashMap<int, std::string> empty;
    HashMap<int, std::string> assigned;

    assigned = empty;

    EXPECT_TRUE(assigned.isEmpty());
    EXPECT_EQ(assigned.size(), 0);
}

TEST_F(HashMapAssignmentOperatorTest, AssignNonEmptyMap)
{
    HashMap<int, std::string> assigned;
    assigned = map;
    EXPECT_EQ(assigned.size(), map.size());

    EXPECT_EQ(assigned.get(1), "Oppo");
    EXPECT_EQ(assigned.get(2), "Vivo");
    EXPECT_EQ(assigned.get(3), "Apple");
}

TEST_F(HashMapAssignmentOperatorTest, OriginalModificationDoesNotAffectAssignedMap)
{
    HashMap<int, std::string> assigned;

    assigned = map;

    map.insert(4, "Samsung");
    map.insert(2, "OnePlus");
    map.remove(1);

    EXPECT_EQ(assigned.size(), 3);

    EXPECT_TRUE(assigned.contains(1));
    EXPECT_TRUE(assigned.contains(2));
    EXPECT_TRUE(assigned.contains(3));

    EXPECT_EQ(assigned.get(2), "Vivo");
    EXPECT_FALSE(assigned.contains(4));
}

TEST_F(HashMapAssignmentOperatorTest, AssignedMapModificationDoesNotAffectOriginal)
{
    HashMap<int, std::string> assigned;

    assigned = map;

    assigned.insert(4, "Samsung");
    assigned.insert(3, "Google");
    assigned.remove(1);

    EXPECT_EQ(map.size(), 3);

    EXPECT_TRUE(map.contains(1));
    EXPECT_FALSE(map.contains(4));
    EXPECT_EQ(map.get(3), "Apple");
}

TEST_F(HashMapAssignmentOperatorTest, SelfAssignment)
{
    map = map;

    EXPECT_EQ(map.size(), 3);

    EXPECT_EQ(map.get(1), "Oppo");
    EXPECT_EQ(map.get(2), "Vivo");
    EXPECT_EQ(map.get(3), "Apple");
}

TEST_F(HashMapAssignmentOperatorTest, AssignAfterRehash)
{
    for(int i = 4; i < 20; ++i)
    {
        map.insert(i, "Value" + std::to_string(i));
    }

    HashMap<int, std::string> assigned;

    assigned = map;

    EXPECT_EQ(assigned.size(), map.size());

    for(int i = 1; i < 20; ++i)
    {
        EXPECT_TRUE(assigned.contains(i));
    }
}

TEST(HashMap, AssignmentOperatorWithStringKeys)
{
    HashMap<std::string, int> map;

    map.insert("Light", 10);
    map.insert("Berkly", 20);

    HashMap<std::string, int> assigned;

    assigned = map;

    EXPECT_EQ(assigned.size(), 2);

    EXPECT_EQ(assigned.get("Light"), 10);
    EXPECT_EQ(assigned.get("Berkly"), 20);
}