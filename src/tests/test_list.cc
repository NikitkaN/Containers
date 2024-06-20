#include "../s21_list.h"
#include "gtest/gtest.h"

TEST(ListTest, DefaultConstructor)
{
  s21::list<int> l;
  EXPECT_EQ(l.size(), 0);
  EXPECT_TRUE(l.empty());
}

TEST(ListTest, SizeConstructor)
{
  s21::list<int> l(5);
  EXPECT_EQ(l.size(), 5);
  EXPECT_FALSE(l.empty());
}

TEST(ListTest, InitializerListConstructor)
{
  s21::list<int> l({1, 2, 3});
  EXPECT_EQ(l.size(), 3);
  auto it = l.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
}

TEST(ListTest, CopyConstructor)
{
  s21::list<int> l({1, 2, 3});
  s21::list<int> l2(l);
  EXPECT_EQ(l2.size(), 3);
  auto it = l2.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
}

TEST(ListTest, MoveConstructor)
{
  s21::list<int> l({1, 2, 3});
  s21::list<int> l2(std::move(l));
  EXPECT_EQ(l2.size(), 3);
  auto it = l2.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
}

TEST(ListTest, CopyAssignment)
{
  s21::list<int> l({1, 2, 3});
  s21::list<int> l2;
  l2 = l;
  EXPECT_EQ(l2.size(), 3);
  auto it = l2.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
}

TEST(ListTest, MoveAssignment)
{
  s21::list<int> l({1, 2, 3});
  s21::list<int> l2;
  l2 = std::move(l);
  EXPECT_EQ(l2.size(), 3);
  auto it = l2.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
}

TEST(ListTest, FrontBack)
{
  s21::list<int> l({1, 2, 3});
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 3);
}

TEST(ListTest, Iterator)
{
  s21::list<int> l({1, 2, 3});
  auto it = l.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  it++;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, l.end());
  ++it;
  EXPECT_EQ(*it, 1);
}

TEST(ListTest, ConstIterator)
{
  s21::list<int> l({1, 2, 3});
  auto cit = l.cbegin();
  EXPECT_EQ(*cit, 1);
  ++cit;
  EXPECT_EQ(*cit, 2);
  cit++;
  EXPECT_EQ(*cit, 3);
  cit++;
  EXPECT_EQ(cit, l.cend());
  ++cit;
  EXPECT_EQ(*cit, 1);
}

TEST(ListTest, PushPopFront)
{
  s21::list<int> l;
  l.push_front(1);
  l.push_front(2);
  EXPECT_EQ(l.front(), 2);
  l.pop_front();
  EXPECT_EQ(l.front(), 1);
}

TEST(ListTest, PushPopBack)
{
  s21::list<int> l;
  l.push_back(1);
  l.push_back(2);
  EXPECT_EQ(l.back(), 2);
  l.pop_back();
  EXPECT_EQ(l.back(), 1);
}

TEST(ListTest, InsertMany)
{
  s21::list<std::pair<int, double>> l1;
  l1.insert_many_back(163, 55.78);
  s21::list<std::pair<int, double>>::iterator it = l1.begin();
  l1.insert_many(it, 123, 2.12);
  it--;
  EXPECT_EQ((*it).first, 123);
  EXPECT_EQ((*it).second, 2.12);
  l1.insert_many(it, 53, 4.222);
  it--;
  EXPECT_EQ(l1.size(), 3);
  EXPECT_EQ((*it).first, 53);
  EXPECT_EQ((*it).second, 4.222);
}

TEST(ListTest, InserBack)
{
  s21::list<std::pair<int, double>> l1;
  l1.insert_many_back(123, 2.12);
  l1.insert_many_back(53, 4.222);
  EXPECT_EQ(l1.size(), 2);
  EXPECT_EQ(l1.front().first, 123);
  EXPECT_EQ(l1.front().second, 2.12);
  EXPECT_EQ(l1.back().first, 53);
  EXPECT_EQ(l1.back().second, 4.222);
  l1.insert_many_back(-2147483648, 1.79769e+308);
  EXPECT_EQ(l1.back().first, -2147483648);
  EXPECT_EQ(l1.back().second, 1.79769e+308);
  l1.insert_many_back(2147483647, -1.79769e+308);
  EXPECT_EQ(l1.back().first, 2147483647);
  EXPECT_EQ(l1.back().second, -1.79769e+308);
  EXPECT_EQ(l1.size(), 4);
}

TEST(ListTest, InsertFront)
{
  s21::list<std::pair<int, double>> l1;
  l1.insert_many_front(123, 2.12);
  EXPECT_EQ(l1.size(), 1);
  EXPECT_EQ(l1.front().first, 123);
  EXPECT_EQ(l1.front().second, 2.12);
  l1.insert_many_front(53, 4.222);
  EXPECT_EQ(l1.size(), 2);
  EXPECT_EQ(l1.front().first, 53);
  EXPECT_EQ(l1.front().second, 4.222);
  EXPECT_EQ(l1.back().first, 123);
  EXPECT_EQ(l1.back().second, 2.12);
  l1.insert_many_front(-2147483648, 1.79769e+308);
  EXPECT_EQ(l1.size(), 3);
  EXPECT_EQ(l1.front().first, -2147483648);
  EXPECT_EQ(l1.front().second, 1.79769e+308);
  l1.insert_many_front(2147483647, -1.79769e+308);
  EXPECT_EQ(l1.size(), 4);
  EXPECT_EQ(l1.front().first, 2147483647);
  EXPECT_EQ(l1.front().second, -1.79769e+308);
}

TEST(ListTest, InsertErase)
{
  s21::list<int> l({1, 2, 3});
  auto it = l.insert(l.begin(), 10);
  EXPECT_EQ(*it, 10);
  EXPECT_EQ(l.size(), 4);
  it = l.erase(it);
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(l.size(), 3);
}

TEST(ListTest, Clear)
{
  s21::list<int> l({1, 2, 3});
  l.clear();
  EXPECT_EQ(l.size(), 0);
  EXPECT_TRUE(l.empty());
}

TEST(ListTest, Resize)
{
  s21::list<int> l({1, 2});
  l.resize(4);
  EXPECT_EQ(l.size(), 4);
  auto it = l.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 0);
  EXPECT_EQ(*it++, 0);
  l.resize(2);
  EXPECT_EQ(l.size(), 2);
}

TEST(ListTest, Merge)
{
  s21::list<int> l1({1, 3, 5});
  s21::list<int> l2({2, 4});
  l1.merge(l2);
  EXPECT_EQ(l1.size(), 5);
  auto it = l1.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 5);
}

TEST(ListTest, Splice)
{
  s21::list<int> l1({1, 3, 5});
  s21::list<int> l2({2, 4});
  auto it = l1.begin();
  ++it;
  l1.splice(it, l2);
  EXPECT_EQ(l1.size(), 5);
  auto lit = l1.begin();
  EXPECT_EQ(*lit++, 1);
  EXPECT_EQ(*lit++, 2);
  EXPECT_EQ(*lit++, 4);
  EXPECT_EQ(*lit++, 3);
  EXPECT_EQ(*lit++, 5);
}

TEST(ListTest, Reverse)
{
  s21::list<int> l({1, 2, 3});
  l.reverse();
  EXPECT_EQ(l.front(), 3);
  EXPECT_EQ(l.back(), 1);
}

TEST(ListTest, Unique)
{
  s21::list<int> l({1, 1, 2, 3, 3});
  l.unique();
  EXPECT_EQ(l.size(), 3);
  auto it = l.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
}

TEST(ListTest, Sort)
{
  s21::list<int> l({3, 1, 2});
  l.sort();
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 3);
}

TEST(ListTest, PopFrontOnEmpty)
{
  s21::list<int> l;
  EXPECT_THROW(l.pop_front(), std::out_of_range);
}

TEST(ListTest, PopBackOnEmpty)
{
  s21::list<int> l;
  EXPECT_THROW(l.pop_back(), std::out_of_range);
}

TEST(ListTest, MergeWithEmpty)
{
  s21::list<int> l1({1, 3, 5});
  s21::list<int> l2;
  l1.merge(l2);
  EXPECT_EQ(l1.size(), 3);
}

TEST(ListTest, SpliceWithEmpty)
{
  s21::list<int> l1({1, 3, 5});
  s21::list<int> l2;
  auto it = l1.begin();
  ++it;
  l1.splice(it, l2);
  EXPECT_EQ(l1.size(), 3);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
