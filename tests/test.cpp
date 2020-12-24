// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include "iostream"
#include "CacheTest.hpp"
TEST(Example, EmptyTest) {
  test test;
  test.set_bufs();
  test.straight_test();
  std::cout << test;
  test.revert_test();
  std::cout << test;
  test.random_test();
  std::cout << test;
}