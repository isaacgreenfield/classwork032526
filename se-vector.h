#ifndef SE_VECTOR_H
#define SE_VECTOR_H
#include <cstddef>
namespace knk {
  template <class T>
  class Vector {
  public:
    ~Vector();
    Vector();
  private:
    T* data_;
    size_t size_, capacity_;

  };
}
#endif
