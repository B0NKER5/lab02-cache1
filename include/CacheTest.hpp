// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_CACHETEST_HPP_
#define INCLUDE_CACHETEST_HPP_
#include "string"
#include "vector"
class test {
 private:
  std::string var_of_test;

  std::vector<double> sizes_of_cashes = {0.25, 1, 6 };
  std::vector<double> sizes_of_bufs;
  std::vector<double> durations_of_test;

 public:
  void straight_test();
  void random_test();
  void revert_test();
  void set_bufs();
  friend std::ostream & operator << (std::ostream & out, test & a);
  std::string get_var_of_test();
  size_t get_size_of_buf_arr();

  std::stringstream get_exp(int index_of_buf);
  std::string get_investigation();
};
#endif  // INCLUDE_CACHETEST_HPP_
