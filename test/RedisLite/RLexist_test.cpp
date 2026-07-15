#include <gtest/gtest.h>
#include "redis_lite.h"

class RedisLiteExistsTest : public ::testing::Test
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

TEST_F(RedisLiteExistsTest, ExistingKey)
{
    EXPECT_EQ(redis.executeCommand("EXISTS Name"), "1");
    EXPECT_EQ(redis.executeCommand("EXISTS College"), "1");
    EXPECT_EQ(redis.executeCommand("EXISTS Language"), "1");
}

TEST_F(RedisLiteExistsTest, NonExistingKey)
{
    EXPECT_EQ(redis.executeCommand("EXISTS Phone"), "0");
}

TEST_F(RedisLiteExistsTest, ExistsAfterDeletion)
{
    redis.executeCommand("DEL College");

    EXPECT_EQ(redis.executeCommand("EXISTS College"), "0");
    EXPECT_EQ(redis.executeCommand("EXISTS Name"), "1");
}

TEST_F(RedisLiteExistsTest, WrongNumberOfArguments)
{
    EXPECT_EQ(
        redis.executeCommand("EXISTS"),
        "(error) Wrong number of arguments for EXISTS"
    );

    EXPECT_EQ(
        redis.executeCommand("EXISTS Name Extra"),
        "(error) Wrong number of arguments for EXISTS"
    );
}

TEST_F(RedisLiteExistsTest, CommandIsCaseInsensitive)
{
    EXPECT_EQ(redis.executeCommand("exists Name"), "1");
    EXPECT_EQ(redis.executeCommand("ExIsTs Phone"), "0");
}

TEST_F(RedisLiteExistsTest, ExtraSpacesBetweenArguments)
{
    EXPECT_EQ(
        redis.executeCommand("EXISTS      Language"),
        "1"
    );
}