#include <gtest/gtest.h>
#include "redis_lite.h"

class RedisLiteSetTest : public ::testing::Test
{
protected:
    RedisLite redis;
};

TEST_F(RedisLiteSetTest, InsertNewKey)
{
    EXPECT_EQ(redis.executeCommand("SET Name Himanshu"), "Ok");

    EXPECT_EQ(redis.executeCommand("GET Name"), "Himanshu");
}

TEST_F(RedisLiteSetTest, UpdateExistingKey)
{
    redis.executeCommand("SET Phone Oppo");

    EXPECT_EQ(redis.executeCommand("SET Phone Samsung"), "Ok");

    EXPECT_EQ(redis.executeCommand("GET Phone"), "Samsung");
}

TEST_F(RedisLiteSetTest, MultipleInsertions)
{
    redis.executeCommand("SET A 10");
    redis.executeCommand("SET B 20");
    redis.executeCommand("SET C 30");

    EXPECT_EQ(redis.executeCommand("GET A"), "10");
    EXPECT_EQ(redis.executeCommand("GET B"), "20");
    EXPECT_EQ(redis.executeCommand("GET C"), "30");
}

TEST_F(RedisLiteSetTest, WrongNumberOfArgumentsLess)
{
    EXPECT_EQ(
        redis.executeCommand("SET Name"),
        "(error) Wrong number of arguments for set"
    );
}

TEST_F(RedisLiteSetTest, WrongNumberOfArgumentsMore)
{
    EXPECT_EQ(
        redis.executeCommand("SET Name Himanshu Extra"),
        "(error) Wrong number of arguments for set"
    );
}

TEST_F(RedisLiteSetTest, LowerCaseCommand)
{
    EXPECT_EQ(redis.executeCommand("set City Delhi"), "Ok");

    EXPECT_EQ(redis.executeCommand("GET City"), "Delhi");
}

TEST_F(RedisLiteSetTest, MixedCaseCommand)
{
    EXPECT_EQ(redis.executeCommand("SeT Country India"), "Ok");

    EXPECT_EQ(redis.executeCommand("GET Country"), "India");
}

TEST_F(RedisLiteSetTest, ExtraSpacesBetweenArguments)
{
    EXPECT_EQ(
        redis.executeCommand("SET     College      CQ"),
        "Ok"
    );

    EXPECT_EQ(redis.executeCommand("GET College"), "CQ");
}

TEST_F(RedisLiteSetTest, LeadingAndTrailingSpaces)
{
    EXPECT_EQ(
        redis.executeCommand("   SET   OS   Fedora   "),
        "Ok"
    );

    EXPECT_EQ(redis.executeCommand("GET OS"), "Fedora");
}