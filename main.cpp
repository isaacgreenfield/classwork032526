#include "se-vector.h"
#include <iostream>
#include <utility>   // для std::pair

using knk::Vector;

// ======================= существующие тесты =======================

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
    return v.getCapacity() == 2 * v.getSize() && v.getCapacity() == 20;
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
    for (size_t i = 0; ans && i < v.getSize(); ++i) {
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
bool testSubscriptOperator() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v[0] = 10;
    return v[0] == 10 && v[1] == 2;
}

bool testConstSubscriptOperator() {
    Vector<int> v;
    v.pushBack(5);
    const Vector<int>& cv = v;
    return cv[0] == 5;
}
bool testIterators() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    auto it = v.begin();
    if (it == v.end()) return false;
    if (*it != 1) return false;
    ++it;
    if (*it != 2) return false;
    ++it;
    if (*it != 3) return false;
    ++it;
    return it == v.end();
}

bool testConstIterators() {
    Vector<int> v;
    v.pushBack(10);
    v.pushBack(20);
    const Vector<int>& cv = v;
    auto it = cv.begin();
    if (*it != 10) return false;
    return true;
}

bool testIteratorRangeFor() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    int sum = 0;
    for (const auto& val : v) {
        sum += val;
    }
    return sum == 3;
}

// --- insert ---
bool testInsertMiddle() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(3);
    auto it = v.begin() + 1;
    v.insert(it, 2);
    return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testInsertAtBegin() {
    Vector<int> v;
    v.pushBack(2);
    v.pushBack(3);
    v.insert(v.begin(), 1);
    return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testInsertAtEnd() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.insert(v.end(), 3);
    return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testInsertResult() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(3);
    auto res = v.insert(v.begin() + 1, 2);
    return *res == 2 && res == v.begin() + 1;
}

bool testInsertCapacityIncrease() {
    Vector<int> v;
    size_t initCap = v.getCapacity();
    v.insert(v.begin(), 1);
    return v.getCapacity() > initCap && v.getSize() == 1 && v[0] == 1;
}

bool testInsertOutOfRange() {
    Vector<int> v;
    v.pushBack(1);
    try {
        v.insert(v.begin() + 2, 5);
        return false;
    } catch (...) {
        return true;
    }
}
bool testEraseMiddle() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    auto it = v.erase(v.begin() + 1);
    return v.getSize() == 2 && v[0] == 1 && v[1] == 3 && *it == 3;
}

bool testEraseAtBegin() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.erase(v.begin());
    return v.getSize() == 1 && v[0] == 2;
}

bool testEraseAtEnd() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.erase(v.end() - 1);
    return v.getSize() == 1 && v[0] == 1;
}

bool testEraseResult() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    auto it = v.erase(v.begin() + 1);
    return *it == 3 && it == v.begin() + 1;
}

bool testEraseFromEmpty() {
    Vector<int> v;
    try {
        v.erase(v.begin());
        return false;
    } catch (...) {
        return true;
    }
}

int main() {
    using test_t = bool(*)();
    using case_t = std::pair<test_t, const char*>;

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
        { testCopyConstructor, "Copy constructor should copy the vector" },
        { testElementAccess, "Elements should be accessed correctly" },
        { testFailAtAccess, "Access failures should be properly registered" },
        { testSubscriptOperator, "Subscript operator should allow read/write access" },
        { testConstSubscriptOperator, "Const subscript operator should allow read access" },
        { testIterators, "Non-const iterators should traverse elements correctly" },
        { testConstIterators, "Const iterators should provide read-only access" },
        { testIteratorRangeFor, "Range-based for loop should work" },
        { testInsertMiddle, "Insert in the middle should work correctly" },
        { testInsertAtBegin, "Insert at begin should work" },
        { testInsertAtEnd, "Insert at end should work like pushBack" },
        { testInsertResult, "Insert should return iterator to inserted element" },
        { testInsertCapacityIncrease, "Insert should increase capacity if needed" },
        { testInsertOutOfRange, "Insert out of range should throw" },
        { testEraseMiddle, "Erase should remove element and shift" },
        { testEraseAtBegin, "Erase at begin" },
        { testEraseAtEnd, "Erase at end" },
        { testEraseResult, "Erase should return iterator to next element" },
        { testEraseFromEmpty, "Erase from empty vector should throw" }
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