#include <gtest/gtest.h>

#include "../s21_array.h"

TEST(Array, Creation) {
  s21::Array<int, 5> test_array;
  ASSERT_EQ(test_array.size(), 5);
}

TEST(Array, InitList) {
  s21::Array<double, 5> test_array = {0.1, 2, -3, 0.04, 5};
  std::array<double, 5> orig_array = {0.1, 2, -3, 0.04, 5};
  for (size_t i = 0; i < orig_array.size(); i++) {
    ASSERT_EQ(test_array[i] == orig_array[i], 1);
  }
}

TEST(Array, Copy) {
  s21::Array<double, 5> test_array = {0.1, 2, -3, 0.04, 5};
  s21::Array<double, 5> copy_array(test_array);
  for (size_t i = 0; i < test_array.size(); i++) {
    ASSERT_EQ(copy_array[i] == test_array[i], 1);
  }
}

TEST(Array, Move) {
  s21::Array<double, 5> test_array = {0.1, 2, -3, 0.04, 5};
  s21::Array<double, 5> copy_array(std::move(test_array));
  for (size_t i = 0; i < test_array.size(); i++) {
    ASSERT_EQ(copy_array[i] == test_array[i], 1);
  }
}

TEST(Array, Equals) {
  s21::Array<double, 5> test_array = {0.1, 2, -3, 0.04, 5};
  s21::Array<double, 5> copy_array = {6, 7, 8, 9, 10};
  copy_array = test_array;
  for (size_t i = 0; i < test_array.size(); i++) {
    ASSERT_EQ(copy_array[i] == test_array[i], 1);
  }
}

TEST(Array, Equals_move) {
  s21::Array<double, 5> test_array = {0.1, 2, -3, 0.04, 5};
  s21::Array<double, 5> copy_array = {6, 7, 8, 9, 10};
  copy_array = std::move(test_array);
  for (size_t i = 0; i < test_array.size(); i++) {
    ASSERT_EQ(copy_array[i] == test_array[i], 1);
  }
}

TEST(Array, Equals_Const) {
  s21::Array<double, 5> const test_array = {0.1, 2, -3, 0.04, 5};
  ASSERT_EQ(test_array[2], -3);
}

TEST(Array, Front) {
  s21::Array<double, 5> test_array = {0.1, 2, -3, 0.04, 5};
  ASSERT_EQ(test_array.front(), test_array[0]);
}

TEST(Array, End) {
  s21::Array<double, 5> test_array = {0.1, 2, -3, 0.04, 5};
  ASSERT_EQ(test_array.back(), test_array[test_array.size() - 1]);
}

TEST(Array, Data) {
  s21::Array<double, 5> test_array = {0.1, 2, -3, 0.04, 5};
  for (size_t i = 0; i < test_array.max_size(); i++) {
    ASSERT_EQ(test_array[i] == test_array.data()[i], 1);
  }
}

TEST(Array, Empty) {
  s21::Array<double, 5> test_array = {0.1, 2, -3, 0.04, 5};
  ASSERT_EQ(test_array.empty(), false);
  s21::Array<double, 0> empty_array;
  ASSERT_EQ(empty_array.empty() && empty_array.begin() == empty_array.end(),
            true);
}

TEST(Array, Swap) {
  s21::Array<double, 5> test_array = {0.1, 2, -3, 0.04, 5};
  s21::Array<double, 5> second_array = {6, 7, 8, 9, 10};
  test_array.swap(second_array);
  ASSERT_EQ((test_array[2] == 8 && second_array[2] == -3), true);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}