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
  test_t tests[] = {
    testConstructAndDistruct,
    testIsEmpty
  };

  constexpr size_t count = sizeof(tests)/sizeof(test_t);
  for (size_t i = 0; i < count; ++i) {
    const char * testName = nullptr;
    bool r = tests[i](&testName);
    if (!r) {
      std::cout << "failed " << testName << "\n";
    }
  }
  return 0;
}