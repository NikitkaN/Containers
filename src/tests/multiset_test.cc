#include <gtest/gtest.h>

#include "../s21_containersplus.h"

TEST(multisetTest, constructor) {
  s21::multiset<int> multiset1;
  std::multiset<int> multiset2;
  s21::multiset<int> multiset3 = {1, 2, 3};
  s21::multiset<int> multiset4 = multiset3;
  s21::multiset<int> multiset5 = std::move(multiset4);
  const s21::multiset<int> multiset_const = {1, 2, 3};
  const s21::multiset<int> multiset_const2 = {1, 2, 3};
  auto it1 = multiset_const.begin();
  auto it2 = multiset_const2.begin();
  for (size_t i = 0; i < multiset_const2.size(); it1++, it2++, i++) {
    EXPECT_EQ(*it1, *it2);
  }
  const std::multiset<int> multiset_const3 = {1, 2, 3};
  auto it4 = multiset_const.end();
  it4--;
  auto it3 = multiset_const3.end();
  it3--;
  EXPECT_EQ(*it4, *it3);
  EXPECT_EQ(multiset1.size(), multiset2.size());
}

TEST(multisetTest, defaultConstructor) {
  s21::multiset<int> s21_multiset;
  std::multiset<int> std_multiset;

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
}

TEST(multisetTest, parameterizedConstructor) {
  s21::multiset<int> s21_multiset = {1, 2, 3};
  std::multiset<int> std_multiset = {1, 2, 3};

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());

  auto s21_it = s21_multiset.begin();
  for (auto std_it = std_multiset.begin(); std_it != std_multiset.end();
       std_it++, s21_it++) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(multisetTest, copyConstructor) {
  s21::multiset<int> s21_multiset = {1, 2, 3};
  s21::multiset<int> s21_multisetTest(s21_multiset);
  std::multiset<int> std_multiset = {1, 2, 3};
  std::multiset<int> std_multisetTest(std_multiset);

  EXPECT_EQ(s21_multiset.size(), s21_multisetTest.size());
  EXPECT_EQ(std_multiset.size(), std_multisetTest.size());
  EXPECT_EQ(s21_multisetTest.size(), std_multisetTest.size());
  EXPECT_EQ(s21_multisetTest.empty(), std_multisetTest.empty());

  auto s21_it = s21_multiset.begin();
  for (auto std_it = std_multiset.begin(); std_it != std_multiset.end();
       std_it++, s21_it++) {
    EXPECT_EQ(*s21_it, *std_it);
  }

  auto t_it = s21_multisetTest.begin();
  for (auto s21_it = s21_multiset.begin(); s21_it != s21_multiset.end();
       t_it++, s21_it++) {
    EXPECT_EQ(*s21_it, *t_it);
  }

  auto std_t_it = std_multisetTest.begin();
  for (auto std_it = std_multiset.begin(); std_it != std_multiset.end();
       std_it++, std_t_it++) {
    EXPECT_EQ(*std_it, *std_t_it);
  }
}

TEST(multisetTest, moveConstructor) {
  s21::multiset<int> s21_multiset = {1, 2, 3};
  s21::multiset<int> s21_multisetTest(std::move(s21_multiset));
  std::multiset<int> std_multiset = {1, 2, 3};
  std::multiset<int> std_multisetTest(std::move(std_multiset));

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multisetTest.size(), std_multisetTest.size());

  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multisetTest.empty(), std_multisetTest.empty());

  auto s21_it = s21_multisetTest.begin();
  for (auto std_it = std_multisetTest.begin(); std_it != std_multisetTest.end();
       std_it++, s21_it++) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(multisetTest, test1) {
  s21::multiset<char> multiset1 = {'a', '2', 'c'};
  std::multiset<char> multiset2 = {'a', '2', 'c'};
  multiset1.max_size();
  multiset2.max_size();

  EXPECT_EQ(*(multiset2.find('a')), *(multiset1.find('a')));
  const s21::multiset<char> multiset3 = {'a', '2', 'c'};
  const std::multiset<char> multiset4 = {'a', '2', 'c'};
  EXPECT_EQ(*(multiset3.find('a')), *(multiset4.find('a')));
}

TEST(multisetTest, test2) {
  s21::multiset<int> multiset1 = {1, 53, 6345, 123, -124};
  std::multiset<int> multiset2 = {1, 53, 6345, 123, -124};
  auto a = multiset1.begin();
  auto b = multiset2.begin();
  EXPECT_EQ(multiset1.size(), multiset2.size());
  for (; a != multiset1.end(); a++, b++) {
    EXPECT_EQ(*a, *b);
  }
}

TEST(multisetTest, test3) {
  s21::multiset<int> multiset1 = {1, 53, 6345, 123, -124};
  std::multiset<int> multiset2 = {1, 53, 6345, 123, -124};
  auto b = std::move(multiset1);
  auto a = std::move(multiset2);
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(multiset1.size(), multiset2.size());
}

TEST(multisetTest, test4) {
  s21::multiset<int> multiset1 = {1, 53, 6345, 123, -124};
  std::multiset<int> multiset2 = {1, 53, 6345, 123, -124};
  EXPECT_EQ(multiset1.empty(), multiset2.empty());
  multiset1.clear();
  multiset2.clear();
  EXPECT_EQ(multiset1.empty(), multiset2.empty());
}

TEST(multisetTest, test5) {
  const s21::multiset<int> multiset1 = {1, 53, 6345, 123, -124};
  s21::multiset<int> multiset2;
  multiset2 = multiset1;
  const std::multiset<int> multiset3 = {1, 53, 6345, 123, -124};
  auto it1 = multiset2.begin();
  auto it2 = multiset3.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST(multisetTest, test6) {
  s21::multiset<char> multiset1 = {'a', '2', 'c', '4'};
  std::multiset<char> multiset2 = {'a', '2', 'c', '4'};
  auto it1 = multiset1.end();
  auto it2 = multiset2.end();
  it1--;
  it2--;
  EXPECT_EQ(*it2, *it1);
}

TEST(multisetTest, test7) {
  s21::multiset<double> multiset1 = {21.123, 452.124, 0.124, 6475.134};
  std::multiset<double> multiset2 = {21.123, 452.124, 0.124, 6475.134};
  EXPECT_EQ(multiset1.size(), multiset2.size());
  EXPECT_EQ(multiset1.empty(), multiset1.empty());
  multiset1.clear();
  multiset2.clear();
  EXPECT_EQ(multiset1.size(), multiset2.size());
  EXPECT_EQ(multiset1.empty(), multiset1.empty());
}

TEST(multisetTest, test8) {
  s21::multiset<double> multiset1 = {21.123, 452.124, 0.124, 6475.134};
  std::multiset<double> multiset2 = {21.123, 452.124, 0.124, 6475.134};
  EXPECT_EQ(multiset1.size(), multiset2.size());
  EXPECT_EQ(multiset1.empty(), multiset1.empty());
  multiset1.clear();
  multiset2.clear();
  EXPECT_EQ(multiset1.size(), multiset2.size());
  EXPECT_EQ(multiset1.empty(), multiset1.empty());
  multiset1.insert(1124.21);
  multiset2.insert(123.123);
  EXPECT_EQ(multiset1.size(), multiset2.size());
  EXPECT_EQ(multiset1.empty(), multiset1.empty());
}

TEST(multisetTest, test9) {
  s21::multiset<double> multiset1 = {21.123, 452.124, 0.124, 6475.134};
  std::multiset<double> multiset2 = {21.123, 452.124, 0.124, 6475.134};
  s21::multiset<double> multiset3 = {21.123, 141.765, 214, 1.24};
  std::multiset<double> multiset4 = {21.123, 141.765, 214, 1.24};
  multiset1.merge(multiset3);
  multiset2.merge(multiset4);
  auto it1 = multiset1.begin();
  auto it2 = multiset2.begin();
  auto it3 = multiset3.begin();
  auto it4 = multiset4.begin();
  for (size_t i = 0; i < multiset1.size(); it1++, it2++, i++)
    EXPECT_EQ(*it1, *it2);
  for (size_t i = 0; i < multiset3.size(); it3++, it4++, i++)
    EXPECT_EQ(*it3, *it4);
}

TEST(multisetTest, test10) {
  s21::multiset<double> multiset1 = {21.123, 452.124, 0.124, 6475.134};
  EXPECT_EQ(multiset1.contains(21.123), true);
  EXPECT_EQ(multiset1.contains(212412.123), false);
  EXPECT_EQ(multiset1.contains(0.124), true);
  EXPECT_EQ(multiset1.contains(213.123), false);
}

TEST(multisetTest, test11) {
  s21::multiset<double> multiset1 = {21.123, 452.124, 0.124, 6475.134};
  std::multiset<double> multiset2 = {21.123, 452.124, 0.124, 6475.134};
  s21::multiset<double> multiset3 = {21.123, 141.765, 214, 1.24};
  std::multiset<double> multiset4 = {21.123, 141.765, 214, 1.24};
  multiset2.swap(multiset4);
  multiset1.swap(multiset3);
  auto it1 = multiset1.begin();
  auto it2 = multiset2.begin();
  auto it3 = multiset3.begin();
  auto it4 = multiset4.begin();
  for (size_t i = 0; i < multiset1.size(); it1++, it2++, i++)
    EXPECT_EQ(*it1, *it2);
  for (size_t i = 0; i < multiset3.size(); it3++, it4++, i++)
    EXPECT_EQ(*it3, *it4);
}

TEST(multisetTest, test12) {
  s21::multiset<char> multiset1 = {'a', '2', 'c', '4'};
  std::multiset<char> multiset2 = {'a', '2', 'c', '4'};
  auto it1 = multiset1.begin();
  auto it2 = multiset2.begin();
  multiset1.erase(it1);
  multiset2.erase(it2);
  EXPECT_EQ(multiset1.size(), multiset2.size());
}

TEST(multisetTest, test13) {
  s21::multiset<char> multiset1 = {'a', '2', 'c', '4'};
  std::multiset<char> multiset2 = {'a', '2', 'c', '4'};
  EXPECT_EQ(multiset1.size(), multiset2.size());
  auto it1 = multiset1.begin();
  auto it2 = multiset2.begin();
  multiset1.erase(it1);
  multiset2.erase(it2);
  EXPECT_EQ(multiset1.size(), multiset2.size());
}

TEST(multisetTest, test14) {
  s21::multiset<char> multiset1 = {'a', '2', 'c'};
  std::multiset<char> multiset2 = {'a', '2', 'c'};
  multiset1.max_size();
  multiset2.max_size();

  EXPECT_EQ(*(multiset2.find('a')), *(multiset1.find('a')));
  const s21::multiset<char> multiset3 = {'a', '2', 'c'};
  const std::multiset<char> multiset4 = {'a', '2', 'c'};
  EXPECT_EQ(*(multiset3.find('a')), *(multiset4.find('a')));
}

TEST(multisetTest, test15) {
  s21::multiset<char> multiset1 = {'a', '2', 'c', '4'};
  std::multiset<char> multiset2 = {'a', '2', 'c', '4'};
  auto it1 = multiset1.begin();
  auto it2 = multiset2.begin();
  multiset1.erase(it1);
  multiset2.erase(it2);
  EXPECT_EQ(multiset1.size(), multiset2.size());
}

TEST(multisetTest, test16) {
  s21::multiset<char> multiset1 = {'a', '2', 'c', '4'};
  std::multiset<char> multiset2 = {'a', '2', 'c', '4'};
  EXPECT_EQ(multiset1.size(), multiset2.size());
  auto it1 = multiset1.begin();
  auto it2 = multiset2.begin();
  multiset1.erase(it1);
  multiset2.erase(it2);
  EXPECT_EQ(multiset1.size(), multiset2.size());
}

TEST(multisetTest, test17) {
  s21::multiset<char> multiset1 = {'a', '2', 'c', '4'};
  std::multiset<char> multiset2 = {'a', '2', 'c', '4'};
  s21::multiset<char> a;
  std::multiset<char> b;
  multiset1.swap(a);
  multiset2.swap(b);
  EXPECT_EQ(multiset1.size(), multiset2.size());
  EXPECT_EQ(a.size(), b.size());
  auto it1 = a.begin();
  for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
  multiset1 = {'a', '2', 'c', '4'};
  multiset2 = {'a', '2', 'c', '4'};
  multiset1.swap(a);
  multiset2.swap(b);
  EXPECT_EQ(multiset1.size(), multiset2.size());
  EXPECT_EQ(a.size(), b.size());
  it1 = a.begin();
  for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(multisetTest, test18) {
  s21::multiset<char> multiset1 = {'a', '2', 'c', '4'};
  std::multiset<char> multiset2 = {'a', '2', 'c', '4'};
  s21::multiset<char> a = {'e', '6', 'g', '8'};
  std::multiset<char> b = {'e', '6', 'g', '8'};
  multiset1.merge(a);
  multiset2.merge(b);
  EXPECT_EQ(multiset1.size(), multiset2.size());
  EXPECT_EQ(a.size(), b.size());
  auto it1 = multiset1.begin();
  for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(multisetTest, test19) {
  s21::multiset<char> multiset1 = {'a', '2', 'c', '4'};
  std::multiset<char> multiset2 = {'a', '2', 'c', '4'};
  s21::multiset<char> a = {'a', '2', 'c', '4'};
  std::multiset<char> b = {'a', '2', 'c', '4'};
  multiset1.merge(a);
  multiset2.merge(b);
  EXPECT_EQ(multiset1.size(), multiset2.size());
  EXPECT_EQ(a.size(), b.size());
  auto it1 = multiset1.begin();
  for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(multisetTest, test20) {
  s21::multiset<char> multiset1 = {'a', '2', 'c', '4'};
  std::multiset<char> multiset2 = {'a', '2', 'c', '4'};
  s21::multiset<char> a = {'a', '2', 'c', '4', 'a', '2'};
  std::multiset<char> b = {'a', '2', 'c', '4', 'a', '2'};
  multiset1.merge(a);
  multiset2.merge(b);
  EXPECT_EQ(multiset1.size(), multiset2.size());
  EXPECT_EQ(a.size(), b.size());
  auto it1 = multiset1.begin();
  for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(multisetTest, test21) {
  s21::multiset<char> multiset1 = {'a', '2', 'c', '4', 'e', '6'};
  s21::multiset<char> multiset2 = {'a', '2', 'c', '4', 'e', '6'};
  auto it1 = multiset1.begin();
  auto it2 = multiset2.begin();
  for (int i = 0; i < 6; i++) {
    it1++, it2++;
  }
  it1 = multiset1.end();
  it2 = multiset2.end();
  for (int i = 0; i < 6; i++) {
    it1--, it2--;
  }
  EXPECT_EQ(*it1, *it2);
}

TEST(multisetTest, test22) {
  s21::multiset<char> multiset1 = {'a', '2', 'c', '4', 'e', '6'};
  s21::multiset<char> multiset2 = {'a', '2', 'c', '4', 'e', '6'};
  auto it1 = multiset1.begin();
  auto it2 = multiset2.begin();
  it1++;
  EXPECT_EQ(it1 != it2, true);
  auto it3 = multiset1.end();
  auto it4 = multiset2.end();
  for (int i = 0; i < 3; i++) {
    it3--, it4--;
  }
  EXPECT_EQ(it3 == it4, false);
  EXPECT_EQ(*it3, *it4);
}

TEST(multisetTest, swap3) {
  s21::multiset<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::multiset<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  s21::multiset<double> v1 = {100, 200, 300, 400, 500};
  std::multiset<double> vc1 = {100, 200, 300, 400, 500};
  v.swap(v1);
  vc.swap(vc1);
  v.max_size();

  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    EXPECT_EQ(*x, *y);
  }
}

TEST(multisetTest, operatorEqMove) {
  s21::multiset<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  s21::multiset<double> v1 = {100, 200, 300, 400, 500};
  v = std::move(v1);
  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(*(v.find(100)), 100);
  EXPECT_EQ(*(v.find(200)), 200);
  EXPECT_EQ(*(v.find(300)), 300);
  EXPECT_EQ(*(v.find(400)), 400);
  EXPECT_EQ(*(v.find(500)), 500);
}

TEST(multisetTest, equal_range) {
  s21::multiset<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1, 8, 8, 8};
  auto x = v.equal_range(8);
  ASSERT_EQ(*x.first, 8);
  ASSERT_EQ(*x.second, 20);
}

TEST(multisetTest, lower_bound) {
  s21::multiset<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1};
  s21::multiset<double>::iterator x = v.lower_bound(8);
  --x;
  ASSERT_EQ(*x, 2);
}

TEST(multisetTest, insertErase) {
  s21::multiset<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1, 8, 8, 8};
  std::multiset<double> vc = {2,  -3, 20, -5, 1, -6, 8, 42,
                              26, 1,  1,  1,  8, 8,  8};
  v.insert(15);
  vc.insert(15);
  v.erase(v.begin());
  vc.erase(vc.begin());
  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(multisetTest, test23) {
  s21::multiset<int> one = {1, 1, 1, 1, 1, 1, 43, 413, 123, 4135};
  auto res = one.equal_range(43);
  EXPECT_EQ(*(res.first), 43);
  EXPECT_EQ(*(res.second), 123);
}

TEST(multisetTest, test24) {
  const s21::multiset<int> one = {1, 1, 1, 1, 1, 1, 43, 413, 123, 4135};
  auto res = one.equal_range(43);
  EXPECT_EQ(*(res.first), 43);
  EXPECT_EQ(*(res.second), 123);
}

TEST(multisetTest, test25) {
  s21::multiset<int> one = {1, 1, 1, 1, 1, 1, 43, 413, 123, 4135,
                            2, 2, 2, 2, 2, 2, 2,  2,   2};
  auto res = one.count(1);
  EXPECT_EQ(res, 6);
  res = one.count(43);
  EXPECT_EQ(res, 1);
  res = one.count(2);
  EXPECT_EQ(res, 9);
}

TEST(multisetTest, test26) {
  s21::multiset<int> one = {1, 1, 1, 1, 1, 1, 43, 413, 123, 4135,
                            2, 2, 2, 2, 2, 2, 2,  2,   2};
  EXPECT_EQ(one.contains(1), true);
  EXPECT_EQ(one.contains(43), true);
  EXPECT_EQ(one.contains(2), true);
  EXPECT_EQ(one.contains(14134), false);
  EXPECT_EQ(one.contains(124124), false);
}

TEST(multisetTest, test27) {
  const s21::multiset<int> one = {1, 1, 1, 1, 1, 1, 43, 413, 123, 4135};
  auto res = one.equal_range(4135);
  EXPECT_EQ(*(res.first), 4135);
  EXPECT_EQ(*(res.second), 0);
}

TEST(multisetTest, insert_many) {
  s21::multiset<int> s21_multiset = {2, 2, 1, 3};
  s21::multiset<int> s21_exm = {0, 1, 2, 2, 3, 4, 4};

  s21_multiset.insert_many(4, 4, 0);

  EXPECT_EQ(s21_multiset.size(), s21_exm.size());
  auto exm_it = s21_exm.begin();
  for (auto s21_it = s21_multiset.begin(); s21_it != s21_multiset.end();
       s21_it++, exm_it++) {
    EXPECT_EQ(*s21_it, *exm_it);
  }
}

TEST(multisetTest, insert_many2) {
  s21::multiset<char> s21_multiset = {'b', 'b', 'f', 'f', 'e', 'e'};
  s21::multiset<char> s21_exm = {'a', 'b', 'b', 'c', 'd',
                                 'e', 'e', 'f', 'f', 'g'};

  s21_multiset.insert_many('c', 'g', 'd', 'a');

  EXPECT_EQ(s21_multiset.size(), s21_exm.size());
  auto exm_it = s21_exm.begin();
  for (auto s21_it = s21_multiset.begin(); s21_it != s21_multiset.end();
       s21_it++, exm_it++) {
    EXPECT_EQ(*s21_it, *exm_it);
  }
}

TEST(multisetTest, insert_many_3) {
  s21::multiset<std::string> s21_multiset = {"Cats", "Are"};
  s21::multiset<std::string> s21_exm = {"Are", "Best", "Best", "Cats",
                                        "The", "The",  "!",    "!"};

  s21_multiset.insert_many("The", "The", "Best", "Best", "!", "!");

  EXPECT_EQ(s21_multiset.size(), s21_exm.size());
  auto exm_it = s21_exm.begin();
  for (auto s21_it = s21_multiset.begin(); s21_it != s21_multiset.end();
       s21_it++, exm_it++) {
    EXPECT_EQ(*s21_it, *exm_it);
  }
}

TEST(multisetTest, insert_many4) {
  s21::multiset<double> v = {2, -3, 20, -5, 1, -6};
  v.insert_many(8, 42, 26, 1, 1, 1);
  s21::multiset<double>::iterator x = v.lower_bound(8);
  --x;
  ASSERT_EQ(*x, 2);
}

TEST(multisetTest, insert_many_5) {
  s21::multiset<double> s21_multiset = {2.13, 2.13, 1.23};
  s21::multiset<double> s21_exm = {1.23, 2.13, 2.13, 3.12, 3.12,
                                   4.12, 4.12, 5.12, 5.12};

  s21_multiset.insert_many(5.12, 5.12, 3.12, 3.12, 4.12, 4.12);

  EXPECT_EQ(s21_multiset.size(), s21_exm.size());
  auto exm_it = s21_exm.begin();
  for (auto s21_it = s21_multiset.begin(); s21_it != s21_multiset.end();
       s21_it++, exm_it++) {
    EXPECT_EQ(*s21_it, *exm_it);
  }
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}