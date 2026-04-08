#ifndef SE_VECTOR_H
#define SE_VECTOR_H
#include <cstddef>
#include <stdexcept>

namespace knk {
  template <class T>
  class Vector {
  public:
    ~Vector();
    Vector();
    Vector(size_t size, const T& value);
    explicit Vector(size_t size);

    Vector(const Vector<T>& rhs);
    Vector<T>& operator=(const Vector<T> rhs) = delete;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    //realize + test thoroughly these 3 things
    size_t getCapacity() const noexcept;

    void pushBack(const T& elem);
    void popBack();
    void resize();

    T& get(size_t id) noexcept;
    const T& get(size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;
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
knk::Vector<T>::Vector(): Vector(0) {}

template<class T>
knk::Vector<T>::Vector(size_t size, const T &value): Vector(size)
{
  try {
    for (size_t i = 0; i < size; ++i) data_[i] = value;
  } catch (...) {
    delete[] data_;
    throw;
  }
}

template<class T>
knk::Vector<T>::Vector(size_t size): data_(size ? new T[2*size] : nullptr), size_(size), capacity_(2*size) {}

template<class T>
knk::Vector<T>::Vector(const Vector<T> &rhs): Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i) {
    data_[i] = rhs.data_[i];
  }
}


template<class T>
bool knk::Vector<T>::isEmpty() const noexcept {
  return !getSize();
}

template<class T>
size_t knk::Vector<T>::getSize() const noexcept {
  return size_;
}

template<class T>
size_t knk::Vector<T>::getCapacity() const noexcept {
  return capacity_;
}

template<class T>
void knk::Vector<T>::pushBack(const T & elem) {
  if (data_ == nullptr) {
    data_ = new T[5];
    capacity_ = 5;
  }
  else {
    if (size_ == capacity_) {
      resize();
    }
  }
  data_[size_++] = elem;
}

template<class T>
void knk::Vector<T>::popBack() {
  if (!isEmpty()) size_--;
  else throw std::logic_error("Cannot pop from empty vector");
}

template<class T>
void knk::Vector<T>::resize() {
  T* newarr = new T[size_];
  try {
    for (size_t i = 0; i < size_; ++i) {
      newarr[i] = data_[i];
    }
    delete[] data_;
    data_ = new T[2*size_];
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = newarr[i];
    }
    capacity_*=2;
    delete[] newarr;
  } catch (...) {
    delete[] newarr;
    throw;
  }
}

template<class T>
T & knk::Vector<T>::get(size_t id) noexcept {
  return const_cast<T&>(static_cast<const Vector<T>*>(this)->get(id));
}

template<class T>
const T & knk::Vector<T>::get(size_t id) const noexcept {
  return data_[id];
}

template<class T>
T & knk::Vector<T>::at(size_t id) {
  const Vector<T>* cthis = this;
  const T& cr = cthis->at(id);
  T& r = const_cast<T&>(cr);
  return r;
}

template<class T>
const T & knk::Vector<T>::at(size_t id) const {
  if (id < getSize()) return get(id);
  throw std::logic_error("there is no such element");
}


#endif
