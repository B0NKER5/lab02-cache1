// Copyright 2020 Your Name <your_email>

#include "CacheTest.hpp"
#include "chrono"
#include "algorithm"
#include "random"
#include "sstream"


const int kylo1024 = 1024;
const int kylo1000 = 1000;
const double four = 4.;
const int sixteen = 16;

void test::straight_test() {
  var_of_test = "direction";
  durations_of_test.clear();
  [[maybe_unused]] int vault;
  for (const double &size : sizes_of_bufs) {
    int *arr1 = new int[static_cast<int>(size / four)];
    for (int i = 0; i < size / four; i += sixteen) {
      vault = arr1[i];
    }
    auto startTime = std::chrono::steady_clock::now();
    for (int item = 0; item < kylo1000; ++item) {
      for (int i = 0; i < size / four; i += sixteen) {
        vault = arr1[i];
      }
    }
    auto endTime = std::chrono::steady_clock::now();
    durations_of_test.push_back(
        std::chrono::duration_cast<std::chrono::microseconds>
            (endTime - startTime).count()/kylo1000);
    delete[] arr1;
  }
}

void test::revert_test() {
  var_of_test = "reverse";
  durations_of_test.clear();

  [[maybe_unused]] int vault;

  for (const double &size : sizes_of_bufs) {
    int *arr1 = new int[static_cast<int>(size / four)];
    for (int i = size / four-1; i > 0; i -= sixteen) {
      vault = arr1[i];
    }
    auto startTime = std::chrono::steady_clock::now();
    for (int i = 0; i < kylo1000; ++i) {
      for (int j = size / four-1; j > 0; j -= sixteen) {
        vault = arr1[j];
      }
    }
    auto endTime = std::chrono::steady_clock::now();

    durations_of_test.push_back(
        std::chrono::duration_cast<std::chrono::microseconds>
            (endTime - startTime).count()/kylo1000);
    delete[] arr1;
  }
}

void test::random_test() {
  var_of_test = "random";
  durations_of_test.clear();
  [[maybe_unused]]int vault;

  for (const double &size : sizes_of_bufs) {
    int *arr1 = new int[static_cast<int>(size / four)];
    std::vector<int> indexesOfBlocks;
    for (int j = 0; j < size / four; j += sixteen) {
      indexesOfBlocks.push_back(j);
      vault = arr1[j];
    }
    auto rng = std::default_random_engine{};
    std::shuffle(indexesOfBlocks.begin(), indexesOfBlocks.end(), rng);

    auto startTime = std::chrono::steady_clock::now();
    for (int i = 0; i < kylo1000; ++i) {
      for (auto index : indexesOfBlocks) {
        vault = arr1[index];
      }
    }
    auto endTime = std::chrono::steady_clock::now();
    durations_of_test.push_back(
        std::chrono::duration_cast<std::chrono::microseconds>
            (endTime - startTime).count()/kylo1000);
    delete[] arr1;
  }
}

std::stringstream test::get_exp(int indexOfBuf) {
  std::stringstream ss;
  ss << "\t- experiment:\n"
     << "\t\tnumber: " << indexOfBuf + 1 << "\n"
     << "\t\tinput_data:\n"
     << "\t\t\tbuffer_size: " << sizes_of_bufs[indexOfBuf] / kylo1024 << "Kb"
     << "\n"
     << "\t\tresults:\n"
     << "\t\t\tduration: " << durations_of_test[indexOfBuf] << "mcs" << '\n';
  return ss;
}

std::string test::get_investigation() {
  std::stringstream ss;
  ss << "investigation:\n"
     << "\ttravel_variant:" << var_of_test << "\n";
  for (size_t duration = 0; duration < durations_of_test.size(); ++duration) {
    ss << get_exp(duration).str();
  }
  ss << "\n";
  return ss.str();
}

std::string test::get_var_of_test() {
  return var_of_test;
}

size_t test::get_size_of_buf_arr() {return sizes_of_bufs.size();}

std::ostream & operator << (std::ostream & out, test & invest){
  out << "investigation:\n" << "\ttravel_variant: "
      << invest.get_var_of_test() << "\n";
  for (size_t i = 0; i < invest.get_size_of_buf_arr(); ++i)
    out << invest.get_exp(i).str();
  out << "\n";
  return out;
}

void test::set_bufs() {
  sizes_of_bufs.push_back(sizes_of_cashes[0] / 2.0 * kylo1024 * kylo1024);
  for (int i = 1; i <= 1.5 * sizes_of_cashes[2]; i *= 2) {
    sizes_of_bufs.push_back(i * kylo1024 * kylo1024);
  }
  sizes_of_bufs.push_back(sizes_of_cashes[2] * 1.5 * kylo1024 * kylo1024);
}