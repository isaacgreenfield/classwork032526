#ifndef SE_VECTOR_H
#define SE_VECTOR_H
#include <cstddef>
namespace knk {
  template <class T>
  class Vector {
  public:
    ~Vector();
    Vector();
    Vector(size_t size, const T& value);

    Vector(const Vector<T>& rhs) = delete;
    Vector<T>& operator=(const Vector<T> rhs) = delete;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;

    void pushBack(const T&);
    void popBack();
  private:
    T* data_;
    size_t size_, capacity_;

  };
}

template<class T>
knk::Vector<T>::~Vector() {
  delete[] data_;
}

template<class T>
knk::Vector<T>::Vector(): data_(nullptr), size_(0), capacity_(0) {}

template<class T>
knk::Vector<T>::Vector(size_t size, const T &value): data_(size ? new T[2*size] : nullptr), size_(size), capacity_(2*size) {
  for (size_t i = 0; i < size_; ++i) data_[i] = value;
}


template<class T>
bool knk::Vector<T>::isEmpty() const noexcept {
  return !getSize();
}

template<class T>
size_t knk::Vector<T>::getSize() const noexcept {
  return size_;
}


#endif
