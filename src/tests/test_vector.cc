#include <gtest/gtest.h>

#include "../s21_vector.h"

TEST(Vector, Creation)
{
  s21::Vector<int> test_vector;
  ASSERT_EQ(test_vector.size(), 0);
  test_vector.~Vector();
}

TEST(Vector, Unvalid_creation)
{
  EXPECT_ANY_THROW(s21::Vector<int> test_vector(-1));
}

TEST(Vector, Parameter_creation)
{
  s21::Vector<int> test_vector(5);
  ASSERT_EQ(test_vector.size(), 5);
  ASSERT_EQ(test_vector.capacity(), 5);
}

TEST(Vector, Initializer_list)
{
  s21::Vector<double> test_vector = {
      1,
      0.2,
      0.03,
      -4, 5};
  std::vector<double> orig_Vector = {
      1,
      0.2,
      0.03,
      -4, 5};

  for (size_t i = 0; i < test_vector.size(); i++)
  {
    ASSERT_EQ(test_vector[i] == orig_Vector[i], 1);
  }
}

TEST(Vector, Copy)
{
  s21::Vector<double> test_vector = {
      1,
      0.2,
      0.03,
      -4, 5};
  s21::Vector<double> copy_vector(test_vector);
  for (size_t i = 0; i < copy_vector.size(); i++)
  {
    ASSERT_EQ(test_vector[i] == copy_vector[i], 1);
  }
}

TEST(Vector, Move)
{
  s21::Vector<double> test_vector = {
      1,
      0.2,
      0.03,
      -4, 5};
  s21::Vector<double> temp(test_vector);
  s21::Vector<double> copy_vector(std::move(test_vector));
  for (size_t i = 0; i < copy_vector.size(); i++)
  {
    ASSERT_EQ(temp[i] == copy_vector[i], 1);
  }
  ASSERT_EQ(test_vector.size(), 0);
}

TEST(Vector, Equals)
{
  s21::Vector<double> test_vector = {
      1,
      0.2,
      0.03,
      -4, 5};
  s21::Vector<double> copy_vector = {6, 7, -8, 9};
  s21::Vector<double> temp(test_vector);
  copy_vector = std::move(test_vector);

  for (size_t i = 0; i < copy_vector.size(); i++)
  {
    ASSERT_EQ(temp[i] == copy_vector[i], 1);
  }

  s21::Vector<double> const const_test_vector = {
      1,
      0.2,
      0.03,
      -4, 5};
  s21::Vector<double> const_copy_vector = {6, 7, -8, 9};
  const_copy_vector = const_test_vector;

  for (size_t i = 0; i < const_test_vector.size(); i++)
  {
    ASSERT_EQ(const_test_vector[i] == const_copy_vector[i], 1);
  }
}

TEST(Vector, Front_Back)
{
  s21::Vector<double> test_vector = {
      1,
      0.2,
      0.03,
      -4, 5};
  ASSERT_EQ(test_vector.front(), test_vector[0]);
  ASSERT_EQ(test_vector.back(), test_vector[test_vector.size() - 1]);
}

TEST(Vector, Arr)
{
  s21::Vector<double> test_vector = {
      1,
      0.2,
      0.03,
      -4, 5};
  for (size_t i = 0; i < test_vector.size(); i++)
  {
    ASSERT_EQ(test_vector[i] == test_vector.data()[i], 1);
  }
}

TEST(Vector, Iterator)
{
  s21::Vector<double> test_vector = {
      0.01,
      0.2,
      0.03,
      -4, 5};
  std::vector<double> orig_vector = {
      0.01,
      0.2,
      0.03,
      -4, 5};
  s21::VectorIterator<double> s21_iter = test_vector.begin();
  std::vector<double>::iterator orig_iter = orig_vector.begin();

  while (s21_iter != test_vector.end())
  {
    double &value = *s21_iter;
    EXPECT_EQ(value, *orig_iter);
    EXPECT_EQ(*s21_iter, *orig_iter);
    ++s21_iter;
    ++orig_iter;
  }
  --s21_iter;
  --orig_iter;
  EXPECT_EQ(*s21_iter, *orig_iter);
}

TEST(Vector, ConstIterator)
{
  s21::Vector<double> const test_vector = {
      1,
      0.2,
      0.03,
      -4, 5};
  std::vector<double> const orig_vector = {
      1,
      0.2,
      0.03,
      -4, 5};
  s21::VectorConstIterator<double> s21_iter = test_vector.cbegin();
  std::vector<double>::const_iterator orig_iter = orig_vector.cbegin();
  while (s21_iter != test_vector.cend())
  {
    double const &value = *s21_iter;
    EXPECT_EQ(value, *orig_iter);
    EXPECT_EQ(*s21_iter, *orig_iter);
    ++s21_iter;
    ++orig_iter;
  }
  --s21_iter;
  --orig_iter;
  EXPECT_EQ(*s21_iter, *orig_iter);
}

TEST(Vector, Iterator_Eq)
{
  s21::Vector<double> test_vector = {
      1,
      0.2,
      0.03,
      -4, 5};

  s21::Vector<double> const const_test_vector = {
      1,
      0.2,
      0.03,
      -4, 5};

  s21::VectorIterator<double> first_iter;
  s21::VectorIterator<double> second_iter;
  s21::VectorConstIterator<double> first_const_iter = test_vector.cbegin();
  s21::VectorConstIterator<double> second_const_iter = test_vector.cbegin();
  s21::VectorConstIterator<double> third_const_iter;

  ASSERT_EQ(first_iter == second_iter, 1);
  ASSERT_EQ(first_const_iter == second_const_iter, 1);
  ASSERT_EQ(third_const_iter == second_const_iter, 0);
}

TEST(Vector, Empty)
{
  s21::Vector<double> test_vector = {
      1,
      0.2,
      0.03,
      -4, 5};
  s21::Vector<double> empty_vector;
  ASSERT_EQ(test_vector.empty(), false);
  ASSERT_EQ(empty_vector.empty(), true);
  test_vector.~Vector();
  ASSERT_EQ(test_vector.empty(), true);
}

TEST(Vector, Reserve)
{
  s21::Vector<double> test_vector = {
      1,
      0.2,
      0.03,
      -4, 5};
  test_vector.reserve(2);
  ASSERT_EQ(test_vector.capacity(), 5);
  test_vector.reserve(10);
  ASSERT_EQ(test_vector.capacity(), 10);
}

TEST(Vector, Max) // почекать тесты на других системах
{
  s21::Vector<double> s21_vector = {
      1,
      0.2,
      0.03,
      -4, 5};
  std::vector<double> orig_vector = {
      1,
      0.2,
      0.03,
      -4, 5};
  ASSERT_EQ(s21_vector.max_size() == orig_vector.max_size(), true);
}

TEST(Vector, Shrink)
{
  s21::Vector<double> s21_vector(5);
  s21_vector.pop_back();
  s21_vector.shrink_to_fit();
  ASSERT_EQ(s21_vector.capacity(), 4);
}

TEST(Vector, Clear)
{
  s21::Vector<double> s21_vector(5);
  s21_vector.clear();
  ASSERT_EQ(s21_vector.size(), 0);
}

TEST(Vector, Insert)
{
  s21::Vector<double> s21_vector = {
      1,
      0.2,
      0.03,
      -4, 5};
  auto s21_iter = s21_vector.end();
  --s21_iter;
  s21_vector.insert(s21_iter, 3.9);
  ASSERT_EQ(s21_vector[4], 3.9);
}

TEST(Vector, Erase)
{
  s21::Vector<double> s21_vector = {
      1,
      0.2,
      0.03,
      -4, 5};
  auto s21_iter = s21_vector.begin();
  ++s21_iter;
  s21_vector.erase(s21_iter);
  ASSERT_EQ(s21_vector[1], 0.03);
}

TEST(Vector, Push_Back)
{
  s21::Vector<double> s21_vector = {
      1,
      0.2,
      0.03,
      -4, 5};
  s21_vector.push_back(14);
  ASSERT_EQ(s21_vector[s21_vector.size() - 1], 14);
}

TEST(Vector, Swap)
{
  s21::Vector<double> s21_vector = {
      1,
      0.2,
      0.03,
      -4, 5};
  s21::Vector<double> swap_vector = {
      6,
      7,
      8,
      9};
  s21_vector.swap(swap_vector);
  ASSERT_EQ((s21_vector[0] == 6 && swap_vector[0] == 1), 1);
}

TEST(Vector, Emplace)
{
  s21::Vector<double> v2 = {-2, 6, 5, 8};

  auto pos2 = v2.end();
  pos2 -= 1;
  v2.emplace(pos2, 9, -1);

  EXPECT_EQ(v2.size(), 6);
  EXPECT_EQ(v2.at(0), -2);
  EXPECT_EQ(v2.at(4), -1);

  for (size_t i = 0; i < v2.size(); ++i)
  {
    EXPECT_EQ(v2.at(i), v2.at(i));
  }
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
