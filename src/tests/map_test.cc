#include <gtest/gtest.h>

#include <map>

#include "../s21_containers.h"

TEST(mapTest, Modifier_Insert) {
  s21::map<char, int> s21_map_1 = {{'b', 228}, {'c', 1337}};
  s21::map<char, int> s21_map_2 = {
      {'b', 228}, {'c', 1337}, {'d', 322}, {'a', 5}};
  s21_map_1 = s21_map_2;
}

TEST(mapTest, insert_or_assign) {
  s21::map<char, int> s21_map_1 = {{'b', 228}, {'c', 1337}};
  s21_map_1.insert_or_assign('b', 138);
  s21_map_1.insert_or_assign('u', 638);
  EXPECT_EQ(s21_map_1['b'], 138);
  EXPECT_EQ(s21_map_1['u'], 638);
}

TEST(mapTest, erase_3) {
  std::pair<int, int> pair1{10, 10};
  std::pair<int, int> pair2{5, 5};
  std::pair<int, int> pair3{15, 15};
  std::pair<int, int> pair4{4, 4};
  std::pair<int, int> pair5{18, 18};
  std::pair<int, int> pair6{13, 13};
  std::pair<int, int> pair7{16, 16};

  s21::map<int, int> s21_map = {pair1, pair2, pair3, pair4,
                                pair5, pair6, pair7};

  auto it = s21_map.begin();
  it++;
  it++;
  it++;
  it++;
  s21_map.erase(it);
  EXPECT_EQ((*s21_map.begin()).first, 4);
  EXPECT_EQ((*s21_map.end()).first, 0);
  EXPECT_EQ(s21_map.size(), 6U);

  it = s21_map.begin();
  s21_map.erase(it);
  EXPECT_EQ((*s21_map.begin()).first, 5);
  EXPECT_EQ((*s21_map.end()).first, 0);
  EXPECT_EQ(s21_map.size(), 5U);

  it = s21_map.begin();
  it++;
  s21_map.erase(it);
  EXPECT_EQ((*s21_map.begin()).first, 5);
  EXPECT_EQ((*s21_map.end()).first, 0);
  EXPECT_EQ(s21_map.size(), 4U);

  it = s21_map.end();
  --it;
  s21_map.erase(it);
  EXPECT_EQ((*s21_map.begin()).first, 5);
  EXPECT_EQ((*s21_map.end()).first, 0);
  EXPECT_EQ(s21_map.size(), 3U);

  it = s21_map.begin();
  it++;
  s21_map.erase(it);

  it = s21_map.begin();
  it++;
  s21_map.erase(it);

  it = s21_map.begin();
  s21_map.erase(it);

  EXPECT_EQ(s21_map.size(), 0U);
}

TEST(map_erase, case2) {
  std::pair<int, int> pair1{30, 30};
  std::pair<int, int> pair2{1543, 1543};

  s21::map<int, int> s21_map = {pair1, pair2};

  auto it = s21_map.begin();
  it++;
  s21_map.erase(it);
  it = s21_map.begin();
  s21_map.erase(it);

  EXPECT_EQ(s21_map.size(), 0U);
}

TEST(mapTest, erase_4) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hola-hola", 2};
  std::pair<std::string, int> pair4{"hola", 3};
  std::pair<std::string, int> pair5{"hello, there", 1};

  s21::map<std::string, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto it = s21_map.end();
  --it;
  s21_map.erase(it);
  EXPECT_EQ((*(--s21_map.end())).first, "hola");
  EXPECT_EQ(s21_map.size(), 4U);

  it = s21_map.end();
  --it;
  s21_map.erase(it);
  EXPECT_EQ((*(--s21_map.end())).first, "hi");
  EXPECT_EQ(s21_map.size(), 3U);

  s21_map.insert(pair3);
  s21_map.insert(pair4);
  it = s21_map.end();
  --it;
  s21_map.erase(it);
  EXPECT_EQ((*(--s21_map.end())).first, "hola");
  EXPECT_EQ(s21_map.size(), 4U);
}

TEST(mapTest, erase_6) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};
  std::pair<double, int> pair3{12.4457, 2};
  std::pair<double, int> pair4{1.44, 3};

  s21::map<double, int> s21_map = {pair1, pair2, pair3, pair4};

  auto it = s21_map.begin();
  it--;
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  EXPECT_EQ((*it).first, 12.4457);
  EXPECT_EQ(s21_map.size(), 4U);
}

TEST(mapTest, erase_7) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};
  std::pair<double, int> pair3{12.4457, 2};
  std::pair<double, int> pair4{6.84, 2};
  std::pair<double, int> pair5{1.44, 3};

  s21::map<double, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto it = s21_map.begin();
  ++it;
  ++it;
  ++it;
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ((*it).first, 44.48);
  EXPECT_EQ(s21_map.size(), 4U);
}

TEST(mapTest, erase_8) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{12.4457, 2};
  std::pair<double, int> pair3{56.84, 2};
  std::pair<double, int> pair4{941.44, 3};
  std::pair<double, int> pair5{44.48, 1};

  s21::map<double, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto it = s21_map.begin();
  ++it;
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  EXPECT_EQ((*it).first, 44.48);
  EXPECT_EQ(s21_map.size(), 4U);
}

TEST(mapTest, brackets) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};
  std::pair<int, double> pair11{78, 3.9};
  std::pair<int, double> pair22{88, 3.9};
  std::pair<int, double> pair33{108, 3.9};

  s21::map<int, double> s21_map_int{pair1,  pair2,  pair3,
                                    pair11, pair22, pair33};
  EXPECT_EQ(s21_map_int[9], 1.4);
  EXPECT_EQ(s21_map_int[23], 2.77);
  EXPECT_EQ(s21_map_int[98], 3.9);
  EXPECT_EQ(s21_map_int[78], 3.9);
  EXPECT_EQ(s21_map_int[88], 3.9);
  EXPECT_EQ(s21_map_int[108], 3.9);

  std::pair<double, std::string> pair4{1.4, "hello"};
  std::pair<double, std::string> pair5{2.77, "hi"};
  std::pair<double, std::string> pair6{3.9, "hola"};

  s21::map<double, std::string> s21_map_double{pair4, pair5, pair6};
  EXPECT_EQ(s21_map_double[1.4], "hello");
  EXPECT_EQ(s21_map_double[2.77], "hi");
  EXPECT_EQ(s21_map_double[3.9], "hola");

  std::pair<std::string, int> pair7{"hello", 1};
  std::pair<std::string, int> pair8{"hi", 2};
  std::pair<std::string, int> pair9{"hola", 3};

  s21::map<std::string, int> s21_map_string{pair7, pair8, pair9};
  EXPECT_EQ(s21_map_string["hello"], 1);
  EXPECT_EQ(s21_map_string["hi"], 2);
  EXPECT_EQ(s21_map_string["hola"], 3);
}

TEST(mapTest, constructor_1) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  auto it = map1.begin();
  for (auto it2 = map2.begin(); it2 != map2.end(); it++, it2++) {
    EXPECT_EQ((*it).second, (*it2).second);
  }
  it = map1.begin();
  for (auto it2 = map2.begin(); it2 != map2.end(); it++, it2++) {
    EXPECT_EQ((*it).first, (*it2).first);
  }
  EXPECT_EQ(map1.size(), map2.size());
}

TEST(mapTest, constructor_2) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  auto map11 = map1;
  auto map22 = map2;
  auto it = map11.begin();
  for (auto it2 = map22.begin(); it2 != map22.end(); it2++, it++) {
    EXPECT_EQ((*it).second, (*it2).second);
  }
  EXPECT_EQ(map1.size(), map2.size());
  EXPECT_EQ(map11.size(), map22.size());
}

TEST(mapTest, constructor_3) {
  s21::map<int, char> map1;
  std::map<int, char> map2;
  EXPECT_EQ(map1.size(), map2.size());
  map1.insert({1, '1'});
  map2.insert({2, '2'});
  EXPECT_EQ(map1.size(), map2.size());
}

TEST(mapTest, constructor_4) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  auto a = std::move(map1);
  auto b = std::move(map2);
  auto it = a.begin();
  for (auto it2 = b.begin(); it2 != b.end(); it2++, it++) {
    EXPECT_EQ((*it).second, (*it2).second);
  }
  EXPECT_EQ(map1.size(), map2.size());
  EXPECT_EQ(a.size(), b.size());
}

TEST(mapTest, constructor_5) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> a;
  std::map<int, char> b;
  a = std::move(map1);
  b = std::move(map2);
  auto it = a.begin();
  for (auto it2 = b.begin(); it2 != b.end(); it2++, it++) {
    EXPECT_EQ((*it).second, (*it2).second);
  }
  EXPECT_EQ(map1.size(), map2.size());
  EXPECT_EQ(a.size(), b.size());
}

TEST(mapTest, at_1) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  for (size_t it = 1; it < map1.size(); it++) {
    EXPECT_EQ(map1.at(it), map2.at(it));
  }
}

TEST(mapTest, at_2) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  EXPECT_EQ(map1.at(2), map2.at(2));
}

TEST(mapTest, at_3) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  EXPECT_ANY_THROW(map1.at(100));
  EXPECT_ANY_THROW(map2.at(100));
}

TEST(mapTest, operator1) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  EXPECT_EQ(map1[100], map2[100]);
  EXPECT_ANY_THROW(map1.at(-4) = 'd');
  EXPECT_ANY_THROW(map2.at(-4) = 'd');
  EXPECT_NO_THROW(map1[-2] = 'b');
  EXPECT_NO_THROW(map2[-2] = 'b');
  EXPECT_EQ(map1.at(-2), map2.at(-2));
}

TEST(mapTest, begin) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  auto it = map1.begin();
  auto it2 = map2.begin();
  EXPECT_EQ((*it).second, (*it2).second);
}

TEST(mapTest, end_1) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  auto it = map1.end();
  auto it2 = map2.end();
  it--, it2--;
  EXPECT_EQ((*it2).second, (*it).second);
}

TEST(mapTest, empty_1) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  map1.clear();
  map2.clear();
  EXPECT_EQ(map1.empty(), map2.empty());
  s21::map<int, char> a;
  std::map<int, char> b;
  EXPECT_EQ(map1.empty(), map2.empty());
}

TEST(mapTest, empty_2) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  EXPECT_EQ(map1.empty(), map2.empty());
}

TEST(mapTest, size2) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  EXPECT_EQ(map1.size(), map2.size());
}

TEST(mapTest, size_3) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  map1.clear();
  map2.clear();
  EXPECT_EQ(map1.size(), map2.size());
}

TEST(mapTest, clear_1) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  map1.clear();
  map2.clear();
  EXPECT_EQ(map1.empty(), map2.empty());
  EXPECT_EQ(map1.size(), map2.size());
  map1.clear();
  map2.clear();
  EXPECT_EQ(map1.size(), map2.size());
  EXPECT_EQ(map1.empty(), map2.empty());
}

TEST(mapTest, clear_2) {
  s21::map<int, char> map1;
  std::map<int, char> map2;
  map1.clear();
  map2.clear();
  EXPECT_EQ(map1.size(), map2.size());
  EXPECT_EQ(map1.empty(), map2.empty());
}

TEST(mapTest, insert_1) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::pair<int, char> pair = {6, 'c'};
  EXPECT_EQ(map1.insert(pair).second, map2.insert(pair).second);
  EXPECT_EQ(map1.size(), map2.size());
}

TEST(mapTest, insert_2) {
  s21::map<int, int> map1;
  std::map<int, int> map2;
  EXPECT_EQ(map1.empty(), map2.empty());
  std::pair<int, int> pair = {1, 1};
  EXPECT_EQ(map1.insert(pair).second, map2.insert(pair).second);
  EXPECT_EQ(map1.empty(), map2.empty());
  EXPECT_EQ(map1.size(), map2.size());
}

TEST(mapTest, insert_3) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  EXPECT_EQ(map1.empty(), map2.empty());
  std::pair<int, char> pair = {4, 'c'};
  EXPECT_EQ(map1.insert(4, 'c').second, map2.insert(pair).second);
  EXPECT_EQ(map1.empty(), map2.empty());
  EXPECT_EQ(map1.size(), map2.size());
}

TEST(mapTest, erase_1) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  EXPECT_EQ(map1.size(), map2.size());
  auto it1 = map1.begin();
  auto it2 = map2.begin();
  map1.erase(it1);
  map2.erase(it2);
  EXPECT_EQ(map1.size(), map2.size());
}

TEST(mapTest, erase_2) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  map1.erase(map1.begin());
  map2.erase(map2.begin());
  auto it = map1.begin();
  auto it2 = map2.begin();
  EXPECT_EQ((*it).second, (*it2).second);
  EXPECT_EQ(map1.size(), map2.size());
}

TEST(mapTest, swap_1) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> a;
  std::map<int, char> b;
  map1.swap(a);
  map2.swap(b);
  EXPECT_EQ(map1.size(), map2.size());
  EXPECT_EQ(a.size(), b.size());
  auto it = a.begin();
  for (auto it2 = b.begin(); it2 != b.end(); it++, it2++) {
    EXPECT_EQ((*it).second, (*it2).second);
  }
}

TEST(mapTest, swap_2) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> a = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  std::map<int, char> b = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  map1.swap(a);
  map2.swap(b);
  EXPECT_EQ(map1.size(), map2.size());
  EXPECT_EQ(a.size(), b.size());
  auto it = a.begin();
  for (auto it2 = b.begin(); it2 != b.end(); it++, it2++) {
    EXPECT_EQ((*it).second, (*it2).second);
  }
  s21::map<int, char> map11;
  std::map<int, char> map22;
  s21::map<int, char> a1;
  std::map<int, char> b1;
  map11.swap(a1);
  map22.swap(b1);
  EXPECT_EQ(map11.size(), map22.size());
  EXPECT_EQ(a1.size(), b1.size());
}

TEST(mapTest, merge_1) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> a = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  std::map<int, char> b = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  map1.merge(a);
  map2.merge(b);
  auto it = a.begin();
  EXPECT_EQ(map1.size(), map2.size());
  EXPECT_EQ(a.size(), b.size());
  for (auto it2 = b.begin(); it2 != b.end(); it++, it2++) {
    EXPECT_EQ((*it).second, (*it2).second);
  }
}

TEST(mapTest, merge_2) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  s21::map<int, char> a = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  std::map<int, char> b = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  map1.merge(a);
  map2.merge(b);
  EXPECT_EQ(map1.size(), map2.size());
  EXPECT_EQ(a.size(), b.size());
  auto it = map1.begin();
  for (auto it2 = map2.begin(); it2 != map2.end(); it++, it2++) {
    EXPECT_EQ((*it).second, (*it2).second);
  }
}

TEST(mapTest, contains_1) {
  s21::map<int, int> map1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(map1.contains(1), true);
}

TEST(mapTest, contains_2) {
  s21::map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  EXPECT_EQ(map1.contains(2), true);
}

TEST(mapTest, default_constructor) {
  s21::map<int, char> s21_map;
  std::map<int, char> std_map;

  EXPECT_EQ(s21_map.empty(), std_map.empty());
  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(mapTest, parameterized_constructor_int) {
  s21::map<int, int> s21_map = {{0, 1}, {1, 2}, {2, 3}};
  std::map<int, int> std_map = {{0, 1}, {1, 2}, {2, 3}};

  EXPECT_EQ(s21_map.empty(), std_map.empty());
  EXPECT_EQ(s21_map.size(), std_map.size());

  auto i = 0;
  for (auto it = std_map.begin(); it != std_map.end(); it++) {
    EXPECT_EQ(s21_map.at(i), std_map.at(i));
    i++;
  }
}

TEST(mapTest, parameterized_constructor_char) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  EXPECT_EQ(s21_map.empty(), std_map.empty());
  EXPECT_EQ(s21_map.size(), std_map.size());

  auto i = 0;
  for (auto it = std_map.begin(); it != std_map.end(); it++) {
    EXPECT_EQ(s21_map.at(i), std_map.at(i));
    i++;
  }
}

TEST(mapTest, parameterized_constructor_double) {
  s21::map<int, double> s21_map = {{0, 1.23}, {1, 2.13}, {2, 3.12}};
  std::map<int, double> std_map = {{0, 1.23}, {1, 2.13}, {2, 3.12}};

  EXPECT_EQ(s21_map.empty(), std_map.empty());
  EXPECT_EQ(s21_map.size(), std_map.size());

  auto i = 0;
  for (auto it = std_map.begin(); it != std_map.end(); it++) {
    EXPECT_EQ(s21_map.at(i), std_map.at(i));
    i++;
  }
}

TEST(mapTest, parameterized_constructor_string) {
  s21::map<int, std::string> s21_map = {
      {0, "Hello"}, {1, "World"}, {2, "Guys"}};
  std::map<int, std::string> std_map = {
      {0, "Hello"}, {1, "World"}, {2, "Guys"}};

  EXPECT_EQ(s21_map.empty(), std_map.empty());
  EXPECT_EQ(s21_map.size(), std_map.size());

  auto i = 0;
  for (auto it = std_map.begin(); it != std_map.end(); it++) {
    EXPECT_EQ(s21_map.at(i), std_map.at(i));
    i++;
  }
}

TEST(mapTest, copy_constructor_int) {
  s21::map<int, int> s21_map = {{0, 1}, {1, 2}, {2, 3}};
  s21::map<int, int> s21_mapTest(s21_map);
  std::map<int, int> std_map = {{0, 1}, {1, 2}, {2, 3}};
  std::map<int, int> std_mapTest(std_map);

  EXPECT_EQ(std_map.empty(), std_mapTest.empty());
  EXPECT_EQ(std_map.size(), std_mapTest.size());

  EXPECT_EQ(s21_mapTest.empty(), std_mapTest.empty());
  EXPECT_EQ(s21_mapTest.size(), std_mapTest.size());

  auto i = 0;
  for (auto it = std_mapTest.begin(); it != std_mapTest.end(); it++) {
    EXPECT_EQ(s21_map.at(i), std_map.at(i));
    EXPECT_EQ(s21_mapTest.at(i), std_mapTest.at(i));
    i++;
  }
}

TEST(mapTest, copy_constructor_char) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  s21::map<int, char> s21_mapTest(s21_map);
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_mapTest(std_map);

  EXPECT_EQ(std_map.empty(), std_mapTest.empty());
  EXPECT_EQ(std_map.size(), std_mapTest.size());

  EXPECT_EQ(s21_mapTest.empty(), std_mapTest.empty());
  EXPECT_EQ(s21_mapTest.size(), std_mapTest.size());

  auto i = 0;
  for (auto it = std_mapTest.begin(); it != std_mapTest.end(); it++) {
    EXPECT_EQ(s21_map.at(i), std_map.at(i));
    EXPECT_EQ(s21_mapTest.at(i), std_mapTest.at(i));
    i++;
  }
}

TEST(mapTest, copy_constructor_double) {
  s21::map<int, double> s21_map = {{0, 1.23}, {1, 2.13}, {2, 3.12}};
  s21::map<int, double> s21_mapTest(s21_map);
  std::map<int, double> std_map = {{0, 1.23}, {1, 2.13}, {2, 3.12}};
  std::map<int, double> std_mapTest(std_map);

  EXPECT_EQ(std_map.empty(), std_mapTest.empty());
  EXPECT_EQ(std_map.size(), std_mapTest.size());

  EXPECT_EQ(s21_mapTest.empty(), std_mapTest.empty());
  EXPECT_EQ(s21_mapTest.size(), std_mapTest.size());

  auto i = 0;
  for (auto it = std_mapTest.begin(); it != std_mapTest.end(); it++) {
    EXPECT_EQ(s21_map.at(i), std_map.at(i));
    EXPECT_EQ(s21_mapTest.at(i), std_mapTest.at(i));
    i++;
  }
}

TEST(mapTest, copy_constructor_string) {
  s21::map<int, std::string> s21_map = {
      {0, "Hello"}, {1, "World"}, {2, "Guys"}};
  s21::map<int, std::string> s21_mapTest(s21_map);
  std::map<int, std::string> std_map = {
      {0, "Hello"}, {1, "World"}, {2, "Guys"}};
  std::map<int, std::string> std_mapTest(std_map);

  EXPECT_EQ(std_map.empty(), std_mapTest.empty());
  EXPECT_EQ(std_map.size(), std_mapTest.size());

  EXPECT_EQ(s21_mapTest.empty(), std_mapTest.empty());
  EXPECT_EQ(s21_mapTest.size(), std_mapTest.size());

  auto i = 0;
  for (auto it = std_mapTest.begin(); it != std_mapTest.end(); it++) {
    EXPECT_EQ(s21_map.at(i), std_map.at(i));
    EXPECT_EQ(s21_mapTest.at(i), std_mapTest.at(i));
    i++;
  }
}

TEST(mapTest, move_constructor_int_char) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  s21::map<int, char> s21_mapTest = std::move(s21_map);
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_mapTest = std::move(std_map);

  EXPECT_EQ(s21_map.empty(), std_map.empty());
  EXPECT_EQ(s21_map.size(), std_map.size());

  EXPECT_EQ(s21_mapTest.empty(), std_mapTest.empty());
  EXPECT_EQ(s21_mapTest.size(), std_mapTest.size());

  auto i = 0;
  for (auto it = std_mapTest.begin(); it != std_mapTest.end(); it++) {
    EXPECT_EQ(s21_mapTest.at(i), std_mapTest.at(i));
    i++;
  }
}

TEST(mapTest, move_constructor_string_double) {
  s21::map<std::string, double> s21_map = {
      {"Hello", 1.23}, {"World", 2.13}, {"Guys", 3.12}};
  s21::map<std::string, double> s21_mapTest = std::move(s21_map);
  std::map<std::string, double> std_map = {
      {"Hello", 1.23}, {"World", 2.13}, {"Guys", 3.12}};
  std::map<std::string, double> std_mapTest = std::move(std_map);

  EXPECT_EQ(s21_map.empty(), std_map.empty());
  EXPECT_EQ(s21_map.size(), std_map.size());

  EXPECT_EQ(s21_mapTest.empty(), std_mapTest.empty());
  EXPECT_EQ(s21_mapTest.size(), std_mapTest.size());

  EXPECT_EQ(s21_mapTest.at("Hello"), std_mapTest.at("Hello"));
  EXPECT_EQ(s21_mapTest.at("World"), std_mapTest.at("World"));
  EXPECT_EQ(s21_mapTest.at("Guys"), std_mapTest.at("Guys"));
}

TEST(mapTest, assigment_operator) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  s21::map<int, char> s21_mapTest;
  s21_mapTest = s21_map;
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_mapTest;
  std_mapTest = std_map;

  EXPECT_EQ(std_map.empty(), std_mapTest.empty());
  EXPECT_EQ(std_map.size(), std_mapTest.size());

  EXPECT_EQ(s21_mapTest.empty(), std_mapTest.empty());
  EXPECT_EQ(s21_mapTest.size(), std_mapTest.size());

  auto i = 0;
  for (auto it = std_mapTest.begin(); it != std_mapTest.end(); it++) {
    EXPECT_EQ(s21_map.at(i), std_map.at(i));
    EXPECT_EQ(s21_mapTest.at(i), std_mapTest.at(i));
    i++;
  }
}

TEST(mapTest, ass_move_operator) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  s21::map<int, char> s21_mapTest;
  s21_mapTest = std::move(s21_map);
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_mapTest;
  std_mapTest = std::move(std_map);

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_mapTest.size(), std_mapTest.size());

  EXPECT_EQ(s21_map.empty(), std_map.empty());
  EXPECT_EQ(s21_mapTest.empty(), std_mapTest.empty());

  auto i = 0;
  for (auto it = std_mapTest.begin(); it != std_mapTest.end(); it++) {
    EXPECT_EQ(s21_mapTest.at(i), std_mapTest.at(i));
    i++;
  }
}

// map element access

TEST(mapTest, at) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  EXPECT_EQ(s21_map.at(0), 'a');
  EXPECT_EQ(s21_map.at(1), 'b');
  EXPECT_EQ(s21_map.at(2), 'c');
}

TEST(mapTest, at_throw) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  EXPECT_ANY_THROW(s21_map.at(4));
}

TEST(mapTest, at_throw_2) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  EXPECT_ANY_THROW(s21_map.at(-1));
}

TEST(mapTest, at_const) {
  const s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  EXPECT_EQ(s21_map.at(0), 'a');
  EXPECT_EQ(s21_map.at(1), 'b');
  EXPECT_EQ(s21_map.at(2), 'c');
}

TEST(mapTest, at_const_throw) {
  const s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  EXPECT_ANY_THROW(s21_map.at(4));
}

TEST(mapTest, at_const_throw_2) {
  const s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  EXPECT_ANY_THROW(s21_map.at(-1));
}

TEST(mapTest, operator_sq_brackets) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  EXPECT_EQ(s21_map[0], 'a');
  EXPECT_EQ(s21_map[1], 'b');
  EXPECT_EQ(s21_map[2], 'c');
}

TEST(mapTest, operator_sq_brackets_2) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  s21_map[3] = 'd';

  EXPECT_EQ(s21_map[0], 'a');
  EXPECT_EQ(s21_map[1], 'b');
  EXPECT_EQ(s21_map[2], 'c');
  EXPECT_EQ(s21_map[3], 'd');
}

TEST(mapTest, operator_sq_brackets_3) {
  s21::map<std::string, double> s21_map = {
      {"Hello", 1.23}, {"World", 2.13}, {"Guys", 3.12}};
  s21_map["LooooL"] = 4.123;

  EXPECT_EQ(s21_map["Hello"], 1.23);
  EXPECT_EQ(s21_map["World"], 2.13);
  EXPECT_EQ(s21_map["Guys"], 3.12);
  EXPECT_EQ(s21_map["LooooL"], 4.123);
}

// map iterators

TEST(mapTest, begin_2) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  auto s21_it = s21_map.begin();

  EXPECT_EQ((*s21_it).second, 'a');
}

TEST(mapTest, begin_21) {
  s21::map<char, std::string> s21_map = {
      {'a', "Hello"}, {'b', "World"}, {'c', "Guys"}};
  auto s21_it = s21_map.begin();
  s21_it++;

  EXPECT_EQ((*s21_it).second, "World");
}

TEST(mapTest, begin_const) {
  const s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  auto s21_it = s21_map.begin();

  EXPECT_EQ((*s21_it).second, 'a');
}

TEST(mapTest, end) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  auto s21_it = s21_map.end();
  s21_it--;

  EXPECT_EQ((*s21_it).second, 'c');
}

TEST(mapTest, end_2) {
  s21::map<char, double> s21_map = {{'a', 1.23}, {'b', 2.13}, {'c', 3.12}};
  auto s21_it = s21_map.end();
  s21_it--;

  EXPECT_EQ((*s21_it).second, 3.12);
}

TEST(mapTest, end_const) {
  const s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  auto s21_it = s21_map.end();
  s21_it--;

  EXPECT_EQ((*s21_it).second, 'c');
}

// map capacity

TEST(mapTest, empty) {
  s21::map<int, char> s21_map;
  std::map<int, char> std_map;

  EXPECT_TRUE(s21_map.empty());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(mapTest, not_empty) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  EXPECT_FALSE(s21_map.empty());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(mapTest, size_empty) {
  s21::map<int, char> s21_map;
  std::map<int, char> std_map;

  EXPECT_EQ(s21_map.size(), 0);
  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(mapTest, size) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  EXPECT_EQ(s21_map.size(), 3);
  EXPECT_EQ(s21_map.size(), std_map.size());
}

// map modifiers

TEST(mapTest, clear) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  s21_map.clear();
  std_map.clear();

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(mapTest, insert_value) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  s21_map.insert({3, 'd'});
  std_map.insert({3, 'd'});

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());

  auto i = 0;
  for (auto it = std_map.begin(); it != std_map.end(); it++) {
    EXPECT_EQ(s21_map.at(i), std_map.at(i));
    i++;
  }
}

TEST(mapTest, insert_value_2) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  s21_map.insert({2, 'd'});
  std_map.insert({2, 'd'});

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());

  auto i = 0;
  for (auto it = std_map.begin(); it != std_map.end(); it++) {
    EXPECT_EQ(s21_map.at(i), std_map.at(i));
    i++;
  }
}

TEST(mapTest, insert_value_3) {
  s21::map<std::string, char> s21_map = {
      {"Hello", 'a'}, {"World", 'b'}, {"Guys", 'c'}};
  std::map<std::string, char> std_map = {
      {"Hello", 'a'}, {"World", 'b'}, {"Guys", 'c'}};

  s21_map.insert({"LoooL", 'd'});
  std_map.insert({"LoooL", 'd'});

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());

  EXPECT_EQ(s21_map.at("Hello"), std_map.at("Hello"));
  EXPECT_EQ(s21_map.at("World"), std_map.at("World"));
  EXPECT_EQ(s21_map.at("Guys"), std_map.at("Guys"));
  EXPECT_EQ(s21_map.at("LoooL"), std_map.at("LoooL"));
}

TEST(mapTest, insert_key_obj) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  std::pair<int, char> pair = {3, 'd'};

  s21_map.insert(3, 'd');
  std_map.insert(pair);
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());

  auto i = 0;
  for (auto it = std_map.begin(); it != std_map.end(); it++) {
    EXPECT_EQ(s21_map.at(i), std_map.at(i));
    i++;
  }
}

TEST(mapTest, insert_key_obj_2) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  std::pair<int, char> pair = {2, 'd'};

  s21_map.insert(2, 'd');
  std_map.insert(pair);
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());

  auto i = 0;
  for (auto it = std_map.begin(); it != std_map.end(); it++) {
    EXPECT_EQ(s21_map.at(i), std_map.at(i));
    i++;
  }
}

TEST(mapTest, insert_or_assign1) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  s21_map.insert_or_assign(3, 'd');
  std_map.insert_or_assign(3, 'd');
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());

  auto i = 0;
  for (auto it = std_map.begin(); it != std_map.end(); it++) {
    EXPECT_EQ(s21_map.at(i), std_map.at(i));
    i++;
  }
}

TEST(mapTest, insert_or_assign_2) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  s21_map.insert_or_assign(2, 'd');
  std_map.insert_or_assign(2, 'd');
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());

  auto i = 0;
  for (auto it = std_map.begin(); it != std_map.end(); it++) {
    EXPECT_EQ(s21_map.at(i), std_map.at(i));
    i++;
  }
}

TEST(mapTest, erase) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  auto s21_it = s21_map.begin();
  auto std_it = std_map.begin();

  s21_map.erase(s21_it);
  std_map.erase(std_it);

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());

  auto i = 1;
  for (auto it = std_map.begin(); it != std_map.end(); it++) {
    EXPECT_EQ(s21_map.at(i), std_map.at(i));
    i++;
  }
}

TEST(mapTest, erase_21) {
  s21::map<double, int> s21_map = {{1.23, 1}, {2.13, 2}, {3.12, 3}};
  std::map<double, int> std_map = {{1.23, 1}, {2.13, 2}, {3.12, 3}};

  auto s21_it = s21_map.begin();
  auto std_it = std_map.begin();

  s21_map.erase(s21_it);
  std_map.erase(std_it);

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());

  EXPECT_ANY_THROW(s21_map.at(1.23));
  EXPECT_EQ(s21_map.at(2.13), std_map.at(2.13));
  EXPECT_EQ(s21_map.at(3.12), std_map.at(3.12));
}

TEST(mapTest, erase_middle) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  auto s21_it = s21_map.begin();
  s21_it++;
  auto std_it = std_map.begin();
  std_it++;

  s21_map.erase(s21_it);
  std_map.erase(std_it);

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());

  EXPECT_EQ(s21_map.at(0), std_map.at(0));
  EXPECT_EQ(s21_map.at(2), std_map.at(2));
}

TEST(mapTest, erase_end) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  auto s21_it = s21_map.end();
  s21_it--;
  auto std_it = std_map.end();
  std_it--;

  s21_map.erase(s21_it);
  std_map.erase(std_it);

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());

  auto i = 0;
  for (auto it = std_map.begin(); it != std_map.end(); it++) {
    EXPECT_EQ(s21_map.at(i), std_map.at(i));
    i++;
  }
}

TEST(mapTest, swap_empty) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  s21::map<int, char> s21_mapTest;
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_mapTest;

  s21_map.swap(s21_mapTest);
  std_map.swap(std_mapTest);

  EXPECT_TRUE(s21_map.empty());
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_mapTest.size(), std_mapTest.size());

  auto i = 0;
  for (auto std_t_it = std_mapTest.begin(); std_t_it != std_mapTest.end();
       std_t_it++) {
    EXPECT_EQ(s21_mapTest.at(i), std_mapTest.at(i));
    i++;
  }
}

TEST(mapTest, swap_empty_1) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  s21::map<int, char> s21_mapTest;
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_mapTest;

  s21_map.swap(s21_mapTest);
  std_map.swap(std_mapTest);

  EXPECT_TRUE(s21_map.empty());
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_mapTest.size(), std_mapTest.size());

  auto i = 0;
  for (auto std_t_it = std_mapTest.begin(); std_t_it != std_mapTest.end();
       std_t_it++) {
    EXPECT_EQ(s21_mapTest.at(i), std_mapTest.at(i));
    i++;
  }

  s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  EXPECT_EQ(s21_map.size(), s21_mapTest.size());
  EXPECT_EQ(std_map.size(), std_mapTest.size());

  auto j = 0;
  for (auto std_it = std_map.begin(); std_it != std_map.end(); std_it++) {
    EXPECT_EQ(s21_map.at(j), std_map.at(j));
    j++;
  }
}

TEST(mapTest, swap_empty_2) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  s21::map<int, char> s21_mapTest;
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_mapTest;
  s21_map.max_size();
  std_map.max_size();

  s21_map.swap(s21_mapTest);
  std_map.swap(std_mapTest);

  EXPECT_TRUE(s21_map.empty());
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_mapTest.size(), std_mapTest.size());

  auto i = 0;
  for (auto std_t_it = std_mapTest.begin(); std_t_it != std_mapTest.end();
       std_t_it++) {
    EXPECT_EQ(s21_mapTest.at(i), std_mapTest.at(i));
    i++;
  }

  s21_map = s21_mapTest;
  std_map = std_mapTest;

  EXPECT_EQ(s21_map.size(), s21_mapTest.size());
  EXPECT_EQ(std_map.size(), std_mapTest.size());

  auto j = 0;
  for (auto std_it = std_map.begin(); std_it != std_map.end(); std_it++) {
    EXPECT_EQ(s21_map.at(j), std_map.at(j));
    j++;
  }
}

TEST(mapTest, merge) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  s21::map<int, char> s21_mapTest = {{3, 'd'}, {4, 'e'}, {5, 'f'}};
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_mapTest = {{3, 'd'}, {4, 'e'}, {5, 'f'}};

  s21_map.merge(s21_mapTest);
  std_map.merge(std_mapTest);

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_TRUE(s21_mapTest.empty());
  EXPECT_EQ(s21_mapTest.size(), std_mapTest.size());

  auto j = 0;
  for (auto std_it = std_map.begin(); std_it != std_map.end(); std_it++) {
    EXPECT_EQ(s21_map.at(j), std_map.at(j));
    j++;
  }
}

TEST(mapTest, reverse_merge) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  s21::map<int, char> s21_mapTest = {{3, 'd'}, {4, 'e'}, {5, 'f'}};
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_mapTest = {{3, 'd'}, {4, 'e'}, {5, 'f'}};

  s21_mapTest.merge(s21_map);
  std_mapTest.merge(std_map);

  EXPECT_TRUE(s21_map.empty());
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_mapTest.size(), std_mapTest.size());

  auto i = 0;
  for (auto std_t_it = std_mapTest.begin(); std_t_it != std_mapTest.end();
       std_t_it++) {
    EXPECT_EQ(s21_mapTest.at(i), std_mapTest.at(i));
    i++;
  }
}

TEST(mapTest, merge_duplicate) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  s21::map<int, char> s21_mapTest = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_mapTest = {{0, 'a'}, {1, 'b'}, {2, 'c'}};

  s21_mapTest.merge(s21_map);
  std_mapTest.merge(std_map);

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_mapTest.size(), std_mapTest.size());

  auto i = 0;
  for (auto std_t_it = std_mapTest.begin(); std_t_it != std_mapTest.end();
       std_t_it++) {
    EXPECT_EQ(s21_mapTest.at(i), std_mapTest.at(i));
    i++;
  }
}

TEST(mapTest, merge_almost_duplicate) {
  s21::map<int, char> s21_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  s21::map<int, char> s21_mapTest = {
      {0, 'a'}, {1, 'b'}, {2, 'c'}, {3, 'd'}, {4, 'e'}};
  std::map<int, char> std_map = {{0, 'a'}, {1, 'b'}, {2, 'c'}};
  std::map<int, char> std_mapTest = {
      {0, 'a'}, {1, 'b'}, {2, 'c'}, {3, 'd'}, {4, 'e'}};
  s21_mapTest.merge(s21_map);
  std_mapTest.merge(std_map);

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_mapTest.size(), std_mapTest.size());

  auto i = 0;
  for (auto std_t_it = std_mapTest.begin(); std_t_it != std_mapTest.end();
       std_t_it++) {
    EXPECT_EQ(s21_mapTest.at(i), std_mapTest.at(i));
    i++;
  }
}

// map lookup

TEST(mapTest, contains_true_int) {
  s21::map<int, int> s21_map = {{1, 1}, {2, 2}, {3, 3}};

  for (int x : {1, 3}) {
    EXPECT_TRUE(s21_map.contains(x));
  }
}

TEST(mapTest, contains_true_char) {
  s21::map<char, int> s21_map = {{'a', 1}, {'b', 2}, {'c', 3}};

  for (int x : {'a', 'c'}) {
    EXPECT_TRUE(s21_map.contains(x));
  }
}

TEST(mapTest, contains_false_int) {
  s21::map<int, int> s21_map = {{1, 1}, {2, 2}, {3, 3}};

  for (int x : {4, 6}) {
    EXPECT_FALSE(s21_map.contains(x));
  }
}

TEST(mapTest, contains_false_char) {
  s21::map<char, int> s21_map = {{'a', 1}, {'b', 2}, {'c', 3}};

  for (int x : {'d', 'f'}) {
    EXPECT_FALSE(s21_map.contains(x));
  }
}

TEST(mapTest, insert_many) {
  s21::map<int, int> s21_map = {{0, 1}, {1, 2}, {2, 3}};
  s21::map<int, int> s21_exm = {{-1, 0}, {0, 1}, {1, 2}, {2, 3},
                                {3, 4},  {4, 5}, {5, 6}};

  s21_map.insert_many(std::make_pair(3, 4), std::make_pair(4, 5),
                  std::make_pair(5, 6), std::make_pair(-1, 0));

  EXPECT_EQ(s21_map.size(), s21_exm.size());
  auto i = -1;
  for (auto s21_it = s21_map.begin(); s21_it != s21_map.end(); s21_it++) {
    EXPECT_EQ(s21_map.at(i), s21_exm.at(i));
    i++;
  }
}

TEST(mapTest, insert_many_2) {
  s21::map<char, std::string> s21_map = {
      {'c', "Cats"}, {'a', "Are"}, {'d', "The"}};
  s21::map<char, std::string> s21_exm = {
      {'a', "Are"}, {'b', "Best"}, {'c', "Cats"}, {'d', "The"}, {'e', "!"}};

  s21_map.insert_many(std::make_pair('b', "Best"), std::make_pair('e', "!"));

  EXPECT_EQ(s21_map.size(), s21_exm.size());
  auto i = 'a';
  for (auto s21_it = s21_map.begin(); s21_it != s21_map.end(); s21_it++) {
    EXPECT_EQ(s21_map.at(i), s21_exm.at(i));
    i++;
  }
}

TEST(mapTest, insert_many_3) {
  s21::map<std::string, double> s21_map = {
      {"Cats", 3.12}, {"Are", 1.23}, {"The", 4.12}};
  s21::map<std::string, double> s21_exm = {{"Are", 1.23},
                                           {"Best", 2.13},
                                           {"Cats", 3.12},
                                           {"The", 4.12},
                                           {"!", 5.12}};

  s21_map.insert_many(std::make_pair("Best", 2.13), std::make_pair("!", 5.12));

  EXPECT_EQ(s21_map.size(), s21_exm.size());

  EXPECT_EQ(s21_map.at("Are"), s21_exm.at("Are"));
  EXPECT_EQ(s21_map.at("Best"), s21_exm.at("Best"));
  EXPECT_EQ(s21_map.at("Cats"), s21_exm.at("Cats"));
  EXPECT_EQ(s21_map.at("The"), s21_exm.at("The"));
  EXPECT_EQ(s21_map.at("!"), s21_exm.at("!"));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}