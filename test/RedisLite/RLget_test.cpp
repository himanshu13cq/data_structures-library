#include <gtest/gtest.h>
#include "redis_lite.h"

class RedisLiteGetTest : public ::testing::Test
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

TEST_F(RedisLiteGetTest, GetExistingKey)
{
    EXPECT_EQ(redis.executeCommand("GET Name"), "Himanshu");
    EXPECT_EQ(redis.executeCommand("GET College"), "CQ");
    EXPECT_EQ(redis.executeCommand("GET Language"), "Cpp");
}

TEST_F(RedisLiteGetTest, GetNonExistingKey)
{
    EXPECT_EQ(redis.executeCommand("GET Phone"), "Nill");
}

TEST_F(RedisLiteGetTest, GetAfterUpdatingValue)
{
    redis.executeCommand("SET Name KitKat");

    EXPECT_EQ(redis.executeCommand("GET Name"), "KitKat");
}

TEST_F(RedisLiteGetTest, WrongNumberOfArgumentsLess)
{
    EXPECT_EQ(
        redis.executeCommand("GET"),
        "(error) Wrong number of arguments for GET"
    );
}

TEST_F(RedisLiteGetTest, WrongNumberOfArgumentsMore)
{
    EXPECT_EQ(
        redis.executeCommand("GET Name Extra"),
        "(error) Wrong number of arguments for GET"
    );
}

TEST_F(RedisLiteGetTest, LowerCaseCommand)
{
    EXPECT_EQ(
        redis.executeCommand("get Name"),
        "Himanshu"
    );
}

TEST_F(RedisLiteGetTest, MixedCaseCommand)
{
    EXPECT_EQ(
        redis.executeCommand("GeT College"),
        "CQ"
    );
}

TEST_F(RedisLiteGetTest, ExtraSpacesBetweenArguments)
{
    EXPECT_EQ(
        redis.executeCommand("GET      Language"),
        "Cpp"
    );
}