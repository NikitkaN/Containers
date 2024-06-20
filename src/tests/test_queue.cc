#include "gtest/gtest.h"
#include "../s21_queue.h"

TEST(QueueTest, EmptyConstructor)
{
  s21::queue<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, InitializerListConstructor)
{
  s21::queue<int> q({1, 2, 3});
  EXPECT_EQ(q.size(), 3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, CopyConstructor)
{
  s21::queue<int> q1({1, 2, 3});
  s21::queue<int> q2(q1);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q1.front(), q2.front());
  EXPECT_EQ(q1.back(), q2.back());
}

TEST(QueueTest, MoveConstructor)
{
  s21::queue<int> q1({1, 2, 3});
  s21::queue<int> q2(std::move(q1));
  EXPECT_EQ(q2.size(), 3);
  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, CopyAssignment)
{
  s21::queue<int> q1({1, 2, 3});
  s21::queue<int> q2;
  q2 = q1;
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q1.front(), q2.front());
  EXPECT_EQ(q1.back(), q2.back());
}

TEST(QueueTest, MoveAssignment)
{
  s21::queue<int> q1({1, 2, 3});
  s21::queue<int> q2;
  q2 = std::move(q1);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, Size)
{
  s21::queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 3);
}

TEST(QueueTest, FrontBack)
{
  s21::queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, PushPop)
{
  s21::queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);

  q.pop();
  EXPECT_EQ(q.front(), 2);

  q.pop();
  EXPECT_EQ(q.front(), 3);

  q.pop();
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, InsertMany)
{
  s21::queue<std::pair<int, double>> q1;
  q1.insert_many(123, 2.12);
  q1.insert_many(53, 4.222);
  EXPECT_EQ(q1.size(), 2);
  EXPECT_EQ(q1.front().first, 123);
  EXPECT_EQ(q1.front().second, 2.12);
  EXPECT_EQ(q1.back().first, 53);
  EXPECT_EQ(q1.back().second, 4.222);
  q1.insert_many(-2147483648, 1.79769e+308);
  EXPECT_EQ(q1.back().first, -2147483648);
  EXPECT_EQ(q1.back().second, 1.79769e+308);
  q1.insert_many(2147483647, -1.79769e+308);
  EXPECT_EQ(q1.back().first, 2147483647);
  EXPECT_EQ(q1.back().second, -1.79769e+308);
  EXPECT_EQ(q1.size(), 4);
}

TEST(QueueTest, Swap)
{
  s21::queue<int> q1;
  s21::queue<int> q2;

  q1.push(1);
  q1.push(2);

  q2.push(3);
  q2.push(4);

  q1.swap(q2);

  EXPECT_EQ(q1.front(), 3);
  EXPECT_EQ(q2.front(), 1);
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}