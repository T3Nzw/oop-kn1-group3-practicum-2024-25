#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include <stdexcept>
#include <initializer_list>

template<typename T>
class Vector {
public:
  bool empty() const { return m_size==0; }
  
  size_t size() const { return m_size; }
  size_t capacity() const { return m_capacity; }

  void reserve(size_t capacity) {
    if (capacity<=m_capacity) return;

    T* newData = new T[capacity];
    for (size_t i = 0; i < m_size; ++i) {
      newData[i] = m_data[i];
    }
    delete[] m_data;
    m_data = newData;
    m_capacity = capacity;
  }

  void push_back(T const& el) {
    if (m_size>=m_capacity) {
      reserve(m_capacity>0 ? m_capacity*2 : 1);
    }

    m_data[m_size++] = el;
  }

  T pop_back() {
    if (empty())
      throw std::runtime_error("vector is empty");

    return m_data[--m_size];
  }

  void insert(size_t index, T const& el) {
    if (index>m_size)
      throw std::out_of_range("invalid index");

    if (m_size>=m_capacity) {
      reserve(m_capacity>0 ? m_capacity*2 : 1);
    }

    shiftRight(index);
    m_size++;
    m_data[index] = el;
  }

  void remove(size_t index) {
    if (index>=m_size)
      throw std::out_of_range("invalid index");

    shiftLeft(index);
    m_size--;
  }

  T& at(size_t index) {
    if (index>=m_size)
      throw std::out_of_range("invalid index");

    return m_data[index];
  } 

  T const& at(size_t index) const {
    if (index>=m_size)
      throw std::out_of_range("invalid index");

    return m_data[index];
  }

  T& operator[](size_t index) {
    return at(index);
  }

  T const& operator[](size_t index) const {
    return at(index);
  }

  void clear() {
    m_size = 0;
  }

  void swap(Vector& other) {
    std::swap(m_data,other.m_data);
    std::swap(m_size,other.m_size);
    std::swap(m_capacity,other.m_capacity);
  }

  bool contains(T const& el) const {
    for (size_t i = 0; i < m_size; ++i)
      if (m_data[i]==el) return true;
    return false;
  }

public:
  Vector() 
  : m_data(nullptr), m_size(0), m_capacity(0) {}

  Vector(size_t capacity, T const& initEl=T())
  : m_data(new T[capacity]), m_size(capacity), m_capacity(capacity) {
    for (size_t i = 0; i < m_size; ++i)
      m_data[i] = initEl;
  }

  Vector(std::initializer_list<T> const& l)
  : m_data(new T[l.size()]), m_size(l.size()), m_capacity(l.size()) {
    size_t i = 0;
    auto it = l.begin();
    for (; it != l.end(); ++i, ++it)
      m_data[i] = *it;
  }

  Vector(Vector const& other)
  : m_data(new T[other.m_size]), m_size(other.m_size), m_capacity(other.m_size) {
    for (size_t i = 0; i < m_size; ++i)
      m_data[i] = other.m_data[i];
  }

  Vector& operator=(Vector const& other) {
    if (this != &other) {
      free();
      copy(other);
    }
    return *this;
  }

  ~Vector() { free(); }

private:
  void copy(Vector const& other) {
    m_data = new T[other.m_size];
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    for (size_t i = 0; i < m_size; ++i)
      m_data[i] = other.m_data[i]; 
  }

  void free() { delete[] m_data; }

  void shiftLeft(size_t index) {
    for (size_t i = index; i < m_size-1; ++i)
      m_data[i] = m_data[i+1];
  } 

  //тук предполагаме, че ще има достатъчно място в масива!
  void shiftRight(size_t index) {
    for (size_t i = m_size; i >= index+1; --i) {
      m_data[i] = m_data[i-1];
    }
  }

private:
  T* m_data;
  size_t m_size;
  size_t m_capacity;
};

#endif // __VECTOR_HPP