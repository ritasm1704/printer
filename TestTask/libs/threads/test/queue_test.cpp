#include <gtest/gtest.h>
#include "threads/myQueue.h"
#include "threads/dataMsg.h"

class QueueTest : public ::testing::Test {

    void SetUp() override {

        q1_.put(0);

        q2_.put(1);
        q2_.put(2);
    }

protected:
    MyQueue<int> q0_;
    MyQueue<int> q1_;
    MyQueue<int> q2_;
};


TEST_F(QueueTest, isEmptyTest) {

    EXPECT_EQ(q0_.isEmpty(), true);
    EXPECT_EQ(q1_.isEmpty(), false);
    EXPECT_EQ(q2_.isEmpty(), false);
}

TEST_F(QueueTest, getValueTest) {

    EXPECT_EQ(q1_.getValue(), 0);
    EXPECT_EQ(q2_.getValue(), 1);
}


