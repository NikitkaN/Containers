#include "../s21_stack.h"
#include "gtest/gtest.h"

TEST(StackTest, EmptyConstructor) {
  s21::stack<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, InitializerListConstructor) {
  s21::stack<int> s({1, 2, 3});
  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(s.top(), 3);
}

TEST(StackTest, CopyConstructor) {
  s21::stack<int> s1({1, 2, 3});
  s21::stack<int> s2(s1);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s1.top(), s2.top());
}

TEST(StackTest, MoveConstructor) {
  s21::stack<int> s1({1, 2, 3});
  s21::stack<int> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s2.top(), 3);
}

TEST(StackTest, CopyAssignment) {
  s21::stack<int> s1({1, 2, 3});
  s21::stack<int> s2;
  s2 = s1;
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s1.top(), s2.top());
}

TEST(StackTest, MoveAssignment) {
  s21::stack<int> s1({1, 2, 3});
  s21::stack<int> s2;
  s2 = std::move(s1);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s1.empty());
}

TEST(StackTest, Size) {
  s21::stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 3);
}

TEST(StackTest, Top) {
  s21::stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  EXPECT_EQ(s.top(), 3);
}

TEST(StackTest, Pop) {
  s21::stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);

  s.pop();
  EXPECT_EQ(s.top(), 2);

  s.pop();
  EXPECT_EQ(s.top(), 1);

  s.pop();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, Push) {
  s21::stack<int> s;
  s.push(1);
  s.push(2);

  EXPECT_EQ(s.top(), 2);

  s.pop();
  EXPECT_EQ(s.top(), 1);
}

TEST(StackTest, Emplace) {
  s21::stack<std::pair<int, double>> s1;
  s1.emplace(123, 2.12);
  EXPECT_EQ(s1.top().first, 123);
  EXPECT_EQ(s1.top().second, 2.12);
  s1.emplace(53, 4.222);
  EXPECT_EQ(s1.size(), 2);
  EXPECT_EQ(s1.top().first, 53);
  EXPECT_EQ(s1.top().second, 4.222);
  s1.emplace(-2147483648, 1.79769e+308);
  EXPECT_EQ(s1.top().first, -2147483648);
  EXPECT_EQ(s1.top().second, 1.79769e+308);
  s1.emplace(2147483647, -1.79769e+308);
  EXPECT_EQ(s1.top().first, 2147483647);
  EXPECT_EQ(s1.top().second, -1.79769e+308);
  EXPECT_EQ(s1.size(), 4);
}

TEST(StackTest, Swap) {
  s21::stack<int> s1;
  s21::stack<int> s2;

  s1.push(1);
  s1.push(2);

  s2.push(3);
  s2.push(4);

  s1.swap(s2);

  EXPECT_EQ(s1.top(), 4);
  EXPECT_EQ(s2.top(), 2);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}