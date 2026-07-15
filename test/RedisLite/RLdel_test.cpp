#include <gtest/gtest.h>
#include "redis_lite.h"

class RedisLiteDelTest : public ::testing::Test
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

TEST_F(RedisLiteDelTest, DeleteExistingKey)
{
    EXPECT_EQ(redis.executeCommand("DEL Name"), "1");

    EXPECT_EQ(redis.executeCommand("GET Name"), "Nill");
    EXPECT_EQ(redis.executeCommand("COUNT"), "2");
}

TEST_F(RedisLiteDelTest, DeleteNonExistingKey)
{
    EXPECT_EQ(redis.executeCommand("DEL Phone"), "0");

    EXPECT_EQ(redis.executeCommand("COUNT"), "3");
}

TEST_F(RedisLiteDelTest, DeleteSameKeyTwice)
{
    EXPECT_EQ(redis.executeCommand("DEL College"), "1");
    EXPECT_EQ(redis.executeCommand("DEL College"), "0");

    EXPECT_EQ(redis.executeCommand("COUNT"), "2");
}

TEST_F(RedisLiteDelTest, WrongNumberOfArgumentsLess)
{
    EXPECT_EQ(
        redis.executeCommand("DEL"),
        "(error) Wrong number of arguments for DEL"
    );
}

TEST_F(RedisLiteDelTest, WrongNumberOfArgumentsMore)
{
    EXPECT_EQ(
        redis.executeCommand("DEL Name Extra"),
        "(error) Wrong number of arguments for DEL"
    );
}

TEST_F(RedisLiteDelTest, LowerCaseCommand)
{
    EXPECT_EQ(redis.executeCommand("del Language"), "1");

    EXPECT_EQ(redis.executeCommand("GET Language"), "Nill");
}

TEST_F(RedisLiteDelTest, MixedCaseCommand)
{
    EXPECT_EQ(redis.executeCommand("DeL Name"), "1");

    EXPECT_EQ(redis.executeCommand("GET Name"), "Nill");
}

TEST_F(RedisLiteDelTest, ExtraSpacesBetweenArguments)
{
    EXPECT_EQ(
        redis.executeCommand("DEL      College"),
        "1"
    );

    EXPECT_EQ(redis.executeCommand("GET College"), "Nill");
}