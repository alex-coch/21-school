#include <gtest/gtest.h>

#include <set>

#include "s21_set.h"
using namespace s21;

template <class T>
void is_equal(set<T> &x, std::set<T> &x_orig) {
  ASSERT_EQ(x.size(), x_orig.size());
  for (std::pair<typename std::set<T>::iterator, typename s21::set<T>::iterator>
           i(x_orig.begin(), x.begin());
       (i.first != x_orig.end() && i.second != x.end());
       ++i.first, ++i.second) {
    ASSERT_EQ((*i.first), (*i.second));
  }
}

TEST(s21_set, create) {
  set<double> x;
  std::set<double> x_orig;
  x.insert(-2.3);
  x.insert(4);
  x.insert(6.987654);
  x.insert(0);
  x.insert(-0.000001);
  x_orig.insert(-2.3);
  x_orig.insert(4);
  x_orig.insert(6.987654);
  x_orig.insert(0);
  x_orig.insert(-0.000001);
  is_equal(x, x_orig);
}

TEST(s21_set, copy) {
  set<double> x;
  x.insert(1.234567);
  x.insert(2.34567);
  x.insert(-0);
  x.insert(-4.567890);
  x.insert(-0.987654);
  x.insert(901.1);
  x.insert(88382221);
  x.insert(0.0000002);
  x.insert(8881234.009);
  x.insert(-100000.01);
  x.insert(123456789);
  x.insert(-98765432);
  x.insert(-0.000000001);
  std::set<double> x_orig;
  x_orig.insert(1.234567);
  x_orig.insert(2.34567);
  x_orig.insert(-0);
  x_orig.insert(-4.567890);
  x_orig.insert(-0.987654);
  x_orig.insert(901.1);
  x_orig.insert(88382221);
  x_orig.insert(0.0000002);
  x_orig.insert(8881234.009);
  x_orig.insert(-100000.01);
  x_orig.insert(123456789);
  x_orig.insert(-98765432);
  x_orig.insert(-0.000000001);
  set<double> y(x);
  std::set<double> y_orig(x_orig);
  is_equal(y, y_orig);
}

TEST(s21_set, move) {
  set<double> x;
  x.insert(1.234567);
  x.insert(2.34567);
  x.insert(-0);
  x.insert(-4.567890);
  x.insert(-0.987654);
  x.insert(901.1);
  x.insert(88382221);
  x.insert(0.0000002);
  x.insert(8881234.009);
  x.insert(-100000.01);
  x.insert(123456789);
  x.insert(-98765432);
  x.insert(-0.000000001);
  std::set<double> x_orig;
  x_orig.insert(1.234567);
  x_orig.insert(2.34567);
  x_orig.insert(-0);
  x_orig.insert(-4.567890);
  x_orig.insert(-0.987654);
  x_orig.insert(901.1);
  x_orig.insert(88382221);
  x_orig.insert(0.0000002);
  x_orig.insert(8881234.009);
  x_orig.insert(-100000.01);
  x_orig.insert(123456789);
  x_orig.insert(-98765432);
  x_orig.insert(-0.000000001);
  set<double> y(std::move(x));
  std::set<double> y_orig(std::move(x_orig));
  is_equal(y, y_orig);
  is_equal(x, x_orig);
}

TEST(s21_set, list) {
  set<double> x{11, 2.3, 6.1, 0.1, 3, 1.09, 4.2, 0.1, 7.7, -0.1, -10};
  std::set<double> x_orig{11, 2.3, 6.1, 0.1, 3, 1.09, 4.2, 0.1, 7.7, -0.1, -10};
  is_equal(x, x_orig);
}

TEST(s21_set, insert) {
  set<int> x;
  std::set<int> x_orig;
  for (int i = -10; i <= 10; i++) {
    x.insert(i);
    x_orig.insert(i);
  }
  is_equal(x, x_orig);
}

TEST(s21_set, iterator) {
  set<int> x{6, 2, 1,    0,  78, 0,  7,  -1,  90,
             3, 8, -234, 98, 33, -0, 11, -99, 1234};
  std::set<int> x_orig{6, 2, 1,    0,  78, 0,  7,  -1,  90,
                       3, 8, -234, 98, 33, -0, 11, -99, 1234};
  auto it = x.begin();
  auto std_it = x_orig.begin();
  ASSERT_EQ(*it, *std_it);

  x.clear();
  it = x.begin();
  ASSERT_EQ(it, x.end());
  EXPECT_ANY_THROW(*it);

  x = {6, 2, 1, 0, 78, 0, 7, -1, 90, 3, 8, -234, 98, 33, -0, 11, -99, 1234};
  x_orig = {6, 2, 1,    0,  78, 0,  7,  -1,  90,
            3, 8, -234, 98, 33, -0, 11, -99, 1234};
  it = x.begin();
  std_it = x_orig.begin();
  for (unsigned int i = 0; i < x.size(); ++i, ++it, ++std_it)
    ASSERT_EQ(*it, *std_it);

  x = {6, 2, 1, 0, 78, 0, 7, -1, 90, 3, 8, -234, 98, 33, -0, 11, -99, 1234};
  it = x.begin();
  for (unsigned int i = 0; i < x.size() - 1; ++i, ++it)
    ;
  ASSERT_EQ(1234, *it);
}

TEST(s21_set, erase) {
  set<int> x{6, 2, 1,    0,  78, 0,  7,  -1,  90,
             3, 8, -234, 98, 33, -0, 11, -99, 1234};
  std::set<int> x_orig{6, 2, 1,    0,  78, 0,  7,  -1,  90,
                       3, 8, -234, 98, 33, -0, 11, -99, 1234};
  auto it = x.begin();
  auto std_it = x_orig.begin();
  for (long unsigned int i = 0; i < x.size() / 2; ++i, ++it, ++std_it)
    ;
  x.erase(it);
  x_orig.erase(std_it);
  is_equal(x, x_orig);

  x = {9, 1, 4};
  x_orig = {9, 1, 4};
  it = x.begin();
  std_it = x_orig.begin();
  x.erase(it);
  x_orig.erase(std_it);
  is_equal(x, x_orig);

  x = {1234};
  x_orig = {1234};
  std_it = x_orig.begin();
  it = x.begin();
  x.erase(it);
  x_orig.erase(std_it);
  is_equal(x, x_orig);

  x.clear();
  it = x.begin();
  EXPECT_ANY_THROW(x.erase(it));

  x = {9, 1, 4};
  int initail_size = x.size();
  it = x.begin();
  x.erase(it);
  ASSERT_EQ(x.size(), initail_size - 1);

  x = {-2, -3, -4, -5, -6, -7};
  initail_size = x.size();
  it = x.begin();
  for (unsigned int i = 0; i < x.size() - 1; ++i, ++it)
    ;
  x.erase(it);
  ASSERT_EQ(x.size(), initail_size - 1);

  x = {6, 2, 1, 0, 78, 0, 7, -1, 90, 3, 8, -234, 98, 33, -0, 11, -99, 1234};
  x_orig = {6, 2, 1,    0,  78, 0,  7,  -1,  90,
            3, 8, -234, 98, 33, -0, 11, -99, 1234};
  it = x.begin();
  std_it = x_orig.begin();
  x.erase(it);
  x_orig.erase(std_it);
  is_equal(x, x_orig);

  x = {6, 2, 1, 0, 78, 0, 7, -1, 90};
  x_orig = {6, 2, 1, 0, 78, 0, 7, -1, 90};

  it = x.begin();
  std_it = x_orig.begin();
  ++it;
  ++std_it;
  x.erase(it);
  x_orig.erase(std_it);
  is_equal(x, x_orig);

  x = {9, 1, 4};
  it = x.begin();
  x.clear();
  ASSERT_EQ(x.size(), 0);
  EXPECT_ANY_THROW(x.erase(it));
}

TEST(s21_set, equal) {
  set<int> x{6, 2, 1,    0,  78, 0,  7,  -1,  90,
             3, 8, -234, 98, 33, -0, 11, -99, 1234};
  std::set<int> x_orig{6, 2, 1,    0,  78, 0,  7,  -1,  90,
                       3, 8, -234, 98, 33, -0, 11, -99, 1234};
  set<int> y = x;
  std::set<int> y_orig = x_orig;
  is_equal(y, y_orig);

  x.clear();
  x_orig.clear();
  y = x;
  y_orig = x_orig;
  is_equal(y, y_orig);
}

TEST(s21_set, empty) {
  set<int> x;
  std::set<int> x_orig;
  ASSERT_EQ(x.empty(), x_orig.empty());

  x = {9};
  x_orig = {9};
  ASSERT_EQ(x.empty(), x_orig.empty());
}

TEST(s21_set, size) {
  set<int> x{1, 2, 3};
  std::set<int> x_orig{1, 2, 3};
  ASSERT_EQ(x.size(), x_orig.size());
}

TEST(s21_set, clear) {
  set<int> x{1, 2, 3};
  std::set<int> x_orig{1, 2, 3};
  x.clear();
  x_orig.clear();
  is_equal(x, x_orig);
}

TEST(s21_set, swap) {
  set<int> x{1, 2, 3};
  set<int> y;
  std::set<int> x_orig{1, 2, 3};
  std::set<int> y_orig;
  y.swap(x);
  y_orig.swap(x_orig);
  is_equal(y, y_orig);
  is_equal(x, x_orig);

  x.swap(x);
  x_orig.swap(x_orig);
  is_equal(x, x_orig);
}

TEST(s21_set, merge) {
  set<int> x{1, 2, 3};
  set<int> y{6, 5, 4, 3};
  std::set<int> x_orig{1, 2, 3};
  std::set<int> y_orig{6, 5, 4, 3};

  y.merge(x);
  y_orig.merge(x_orig);
  is_equal(y, y_orig);
  is_equal(x, x_orig);

  x.merge(x);
  x_orig.merge(x_orig);
  is_equal(x, x_orig);
}

TEST(s21_set, find) {
  set<int> x{1, 2, 3};
  std::set<int> x_orig{1, 2, 3};
  auto it = x.find(2);
  auto std_it = x_orig.find(2);
  ASSERT_EQ(*it, *std_it);

  it = x.find(4);
  std_it = x_orig.find(4);
  ASSERT_EQ(it, x.end());
  ASSERT_EQ(std_it, x_orig.end());
}

TEST(s21_set, contains) {
  set<int> x;
  ASSERT_EQ(x.contains(4), false);

  x = {1, 2, 3};
  ASSERT_EQ(x.contains(4), false);

  set<double> y{-0.8563859, 1.9473646};
  ASSERT_EQ(y.contains(-0.8563855), false);
  ASSERT_EQ(y.contains(1.9473646), true);
}

TEST(s21_set, max_size) {
  set<double> x;
  std::set<double> x_orig;
  EXPECT_GE(x.max_size(), 0);
  EXPECT_GE(x_orig.max_size(), 0);
}

// TEST(s21_set, emplace_bonus) {
//   set<double> x{2.34534534};
//   x.emplace(2.34, 1.43, 1.0, 14.54, 75.34);
//   std::set<double> x_orig{2.34534534};
//   x_orig.emplace(2.34);
//   x_orig.emplace(1.43);
//   x_orig.emplace(1.0);
//   x_orig.emplace(14.54);
//   x_orig.emplace(75.34);
//   is_equal(x, x_orig);
// }