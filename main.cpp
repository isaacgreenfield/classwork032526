#include "se-vector.h"
#include <iostream>
using knk::Vector;

bool testConstructAndDistruct(const char ** p_name) {
  *p_name = __func__;
  Vector<int> v;
  return true;
}
bool testIsEmpty(const char ** p_name) {
  *p_name == __func__;
  Vector<int> v;
  return v.isEmpty();
}

int main() {
  using test_t = bool(*)(const char **);
  using case_t = std::pair<test_t, const char *>;
  case_t tests[] = {
    { testConstructAndDistruct, "Vector must be constructable and destructable" },
    {testIsEmpty, "Default constructor constructed vector must be empty"}
  };

  constexpr size_t count = sizeof(tests)/sizeof(case_t);
  size_t failed = 0;
  for (size_t i = 0; i < count; ++i) {
    const char * testName = nullptr;
    bool r = tests[i].first(&testName);
    if (!r) {
      ++failed;
      std::cout << "failed " << testName << "\n";
      std::cout << "\t" << tests[i].second << "\n";
    }
  }
  std::cout << "SUMMARY:\nPASSED: " << (count - failed) << " FAILED: " << (failed) << "\n";
  return 0;
}