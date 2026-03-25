#ifndef SE_VECTOR_H
#define SE_VECTOR_H
#include <cstddef>
namespace knk {
  template <class T>
  struct Vector {
    T* data;
    size_t size, capacity;


  };
}
#endif
