#include <gtest/gtest.h>
#include "redis_lite.h"

class RedisLiteClearTest : public ::testing::Test
{
protected:
    RedisLite redis;

    void SetUp() override
    {
        redis.executeCommand("SET Name Himanshu");
        redis.executeCommand("SET College CQ");
        redis.executeCommand("SET Language Cpp");
    }
};

TEST_F(RedisLiteClearTest, ClearRemovesAllKeys)
{
    EXPECT_EQ(redis.executeCommand("CLEAR"), "Ok");

    EXPECT_EQ(redis.executeCommand("COUNT"), "0");
    EXPECT_EQ(redis.executeCommand("GET Name"), "Nill");
    EXPECT_EQ(redis.executeCommand("GET College"), "Nill");
    EXPECT_EQ(redis.executeCommand("GET Language"), "Nill");
}

TEST_F(RedisLiteClearTest, ClearEmptyDatabase)
{
    redis.executeCommand("CLEAR");

    EXPECT_EQ(redis.executeCommand("CLEAR"), "Ok");
    EXPECT_EQ(redis.executeCommand("COUNT"), "0");
}

TEST_F(RedisLiteClearTest, CanInsertAfterClear)
{
    redis.executeCommand("CLEAR");

    EXPECT_EQ(redis.executeCommand("SET Phone Samsung"), "Ok");
    EXPECT_EQ(redis.executeCommand("GET Phone"), "Samsung");
    EXPECT_EQ(redis.executeCommand("COUNT"), "1");
}

TEST_F(RedisLiteClearTest, CommandIsCaseInsensitive)
{
    EXPECT_EQ(redis.executeCommand("clear"), "Ok");
    EXPECT_EQ(redis.executeCommand("COUNT"), "0");
}

TEST_F(RedisLiteClearTest, ClearActuallyRemovesExistingKeys)
{
    redis.executeCommand("CLEAR");

    EXPECT_EQ(redis.executeCommand("EXISTS Name"), "0");
    EXPECT_EQ(redis.executeCommand("EXISTS College"), "0");
    EXPECT_EQ(redis.executeCommand("EXISTS Language"), "0");
}