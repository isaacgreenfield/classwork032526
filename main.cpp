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
  try {
    Vector<int> v(10, 10);
    return v.getSize() == 10;
  } catch (...) {
    return false;
  }
}
bool testGetCapacityOfEmptyVector() {
  Vector<int> v;
  return v.getCapacity() == 0;
}
bool testGetCapacityOfNonEmptyVector() {
  Vector<int> v(10, 10);
  return v.getCapacity()==2*v.getSize() && v.getCapacity()==20;
}
bool testIfDefaultAndZeroVectorsAreTheSame() {
  Vector<int> f(0);
  Vector<int> g(0, 0);
  Vector<int> h;

  return f.getCapacity() == g.getCapacity() && g.getCapacity() == h.getCapacity();
}
bool testPushBackOnGuaranteedBiggerCapacity() {
  Vector<int> v;
  v.pushBack(5);
  v.pushBack(7);

  return !v.isEmpty() && v.getSize() == 2 && v.getCapacity() >= 2;
}
bool testResizeOnPush() {
  Vector<int> v;
  try {
    auto sz = v.getCapacity();
    for (size_t i = 0; i < sz + 1; ++i) {
      v.pushBack(0);
    }
    return v.getCapacity() > sz && v.getSize() > sz;
  } catch (...) {
    return false;
  }
}
bool testIfPushAndDefaultConsturctedAreSame() {
  Vector<int> v(10, 10);
  try {
    Vector<int> f;
    for (size_t i = 0; i < 10; ++i) {
      f.pushBack(10);
    }
    return f.getSize() == v.getSize();
  } catch (...) {
    return false;
  }
}
bool testPopForOneIn() {
  Vector<int> v(2, 2);
  v.popBack();
  return v.getSize() == 1;
}
bool testPopForZeroVector() {
  Vector<int> v;
  try {
    v.popBack();
    return false;
  } catch (...) {
    return true;
  }
}
bool testIfPopNotDownsizesTheVector() {
  Vector<int> v(1, 1);
  try {
    v.pushBack(1);
    v.pushBack(1);
    return v.getSize() != 2;
  } catch (...) {
    return false;
  }
}
bool testIfDefaultAndDownsizedAreEqualPop() {
  Vector<int> v;
  try {
    Vector<int> f(10, 10);
    for (size_t i = 0; i < 10; ++i) {
      f.popBack();
    }
    return f.isEmpty() && f.getSize() == v.getSize();
  } catch (...) {
    return false;
  }
}
bool testCopyConstructor() {
  Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  Vector<int> yav = v;
  bool ans = yav.getSize() == v.getSize();
  for (size_t i =0; ans && i< v.getSize(); ++i) {
    try {
      ans = v.at(i) == yav.at(i);
    } catch (...) {
      return false;
    }
  }
  return ans;
}
bool testElementAccess() {
  Vector<int> v;
  v.pushBack(10);
  return v.at(0) == 10;
}
bool testFailAtAccess() {
  Vector<int> v;
  v.pushBack(12);
  try {
    return 1 == v.at(1) && 1 == v.at(-1);
  } catch (...) {
    return true;
  }
}

int main() {
  using test_t = bool(*)();
  using case_t = std::pair<test_t, const char *>;
  case_t tests[] = {
    { testConstructAndDistruct, "Vector must be constructable and destructible" },
    { testIsEmpty, "Default constructor constructed vector must be empty" },
    { testGetSize, "Size of default constructed vector should be zero" },
    { testSizeOfNonEmptyVector, "Size of non-empty vector must be greater than zero" },
    { testGetCapacityOfEmptyVector, "Capacity of empty vector should be zero" },
    { testGetCapacityOfNonEmptyVector, "Capacity of non-empty vector should be greater than zero" },
    { testIfDefaultAndZeroVectorsAreTheSame, "All constructors should lead to the same vector being created" },
    { testPushBackOnGuaranteedBiggerCapacity, "Push back should push an element into the vector" },
    { testResizeOnPush, "Vector should resize upon receiving more elements than promised" },
    { testIfPushAndDefaultConsturctedAreSame, "Constructed and pushed into vectors should yield the same vector in everything but capacity" },
    { testPopForOneIn, "Pop function should throw the last element from vector" },
    { testPopForZeroVector, "Pop function should throw error if there are no elements in the vector" },
    { testIfPopNotDownsizesTheVector, "Pop function should not downsize the vector" },
    { testIfDefaultAndDownsizedAreEqualPop, "Popped vector should be same as default vector in all but capacity" },
    { testCopyConstructor, "Copy constructor should copy the vector"},
    { testElementAccess, "Elements should be accessed correctly"},
    { testFailAtAccess, "Access failures should be properly registered"}
  };

  constexpr size_t count = sizeof(tests)/sizeof(case_t);
  size_t failed = 0;
  for (size_t i = 0; i < count; ++i) {
    bool r = tests[i].first();
    if (r) {
      std::cout << "[PASS] TEST " << (i+1) << "\n";
    } else {
      ++failed;
      std::cout << "[FAIL] TEST " << (i+1) << "\n";
      std::cout << "\t" << tests[i].second << "\n";
    }
  }
  std::cout << "\nSUMMARY:\n\tPASSED: " << (count - failed) << "\n\tFAILED: " << (failed) << "\n";
  return 0;
}