#ifndef __UNIQUE_PTR_HPP
#define __UNIQUE_PTR_HPP

#include <stdexcept>

template<typename T> class unique_ptr;

template<typename T>
unique_ptr<T> make_unique(T const& data) {
  return unique_ptr<T>(new T(data));
}

template<typename T>
class unique_ptr {
public:
  T& operator*() {
    if (!m_ptr)
      throw std::runtime_error("attempted to dereference nullptr");
    
    return *m_ptr;
  }

  T const& operator*() const {
    if (!m_ptr)
      throw std::runtime_error("attempted to derefence nullptr");

    return *m_ptr;
  }

  T* operator->() { return m_ptr; }
  T const* operator->() const { return m_ptr; }

  T* release() {
    T* copy = m_ptr;
    m_ptr = nullptr;
    return copy;
  }

  void swap(unique_ptr& other) {
    std::swap(m_ptr,other.m_ptr);
  }

  bool valid() const { return m_ptr; }
  operator bool() const { return valid(); }

public:
  unique_ptr() : m_ptr(nullptr) {} 
  unique_ptr(T* ptr) : m_ptr(ptr) {}

  unique_ptr(unique_ptr const&)=delete;
  
  unique_ptr& operator=(unique_ptr const&)=delete;

  ~unique_ptr() { delete m_ptr; }

private:
  T* m_ptr;
};

#endif // __UNIQUE_PTR_HPP