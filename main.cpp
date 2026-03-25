#include "se-vector.h"
#include <iostream>
using knk::Vector;

bool testConstructAndDistruct() {
  Vector<int> v;
  return true;
}
bool testIsEmpty() {
  Vector<int> v;
  return v.isEmpty();
}
bool testGetSize() {
  Vector<int> v;
  return !v.getSize();
}
bool testSizeOfNonEmptyVector() {
  return false;
}

int main() {
  using test_t = bool(*)();
  using case_t = std::pair<test_t, const char *>;
  case_t tests[] = {
    { testConstructAndDistruct, "Vector must be constructable and destructable" },
    { testIsEmpty, "Default constructor constructed vector must be empty" },
    { testGetSize, "Size of default constructed vector should be zero" },
    { testSizeOfNonEmptyVector, "Size of non-empty vector must be greated than zero"}
  };

  constexpr size_t count = sizeof(tests)/sizeof(case_t);
  size_t failed = 0;
  for (size_t i = 0; i < count; ++i) {
    bool r = tests[i].first();
    if (!r) {
      ++failed;
      std::cout << "failed test " << (i + 1) << "\n";
      std::cout << "\t" << tests[i].second << "\n";
    }
  }
  std::cout << "SUMMARY:\n\tPASSED: " << (count - failed) << " FAILED: " << (failed) << "\n";
  return 0;
}