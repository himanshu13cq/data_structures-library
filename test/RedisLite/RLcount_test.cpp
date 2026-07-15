#include <gtest/gtest.h>
#include "redis_lite.h"

class RedisLiteCountTest : public ::testing::Test
{
protected:
    RedisLite redis;
};

TEST_F(RedisLiteCountTest, CountInitiallyZero)
{
    EXPECT_EQ(redis.executeCommand("COUNT"), "0");
}

TEST_F(RedisLiteCountTest, CountAfterInsertions)
{
    redis.executeCommand("SET Name Himanshu");
    redis.executeCommand("SET College CQ");
    redis.executeCommand("SET Language Cpp");

    EXPECT_EQ(redis.executeCommand("COUNT"), "3");
}

TEST_F(RedisLiteCountTest, CountAfterDeletion)
{
    redis.executeCommand("SET Name Himanshu");
    redis.executeCommand("SET College CQ");

    redis.executeCommand("DEL Name");

    EXPECT_EQ(redis.executeCommand("COUNT"), "1");
}

TEST_F(RedisLiteCountTest, CountAfterClear)
{
    redis.executeCommand("SET Name Himanshu");
    redis.executeCommand("SET College CQ");

    redis.executeCommand("CLEAR");

    EXPECT_EQ(redis.executeCommand("COUNT"), "0");
}

TEST_F(RedisLiteCountTest, CommandIsCaseInsensitive)
{
    redis.executeCommand("SET Name Himanshu");
    redis.executeCommand("SET College CQ");

    EXPECT_EQ(redis.executeCommand("count"), "2");
    EXPECT_EQ(redis.executeCommand("CoUnT"), "2");
}