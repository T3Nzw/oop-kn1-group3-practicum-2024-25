#ifndef __OPTIONAL_HPP
#define __OPTIONAL_HPP

#include <exception>
#include <utility>

// можем да наследяваме и от STL класа!
class BadOptionalAccess : public std::exception {
public:
  // красотата на C++ :)
  // noexcept -> "обещава", че функцията няма да хвърля никакви изключения
  // final -> не позволява предефинирането на метода в класовете, които 
  // наследяват от BadOptionalAccess
  virtual char const* what() const noexcept override final {
    return "object has no value";
  } 
};

template<typename T>
class Optional {
public:
  Optional() : m_hasValue(false) {}
  
  Optional(T const& value) : m_hasValue(true) {
    new (&m_value.value) T(value);
  }

  Optional(Optional const& other) : m_hasValue(other.m_hasValue) {
    if (other.m_hasValue) {
      new (&m_value.value) T(other.m_value);
    }
  } 

  Optional(Optional&& other) : m_hasValue(other.m_hasValue) {
    if (other.m_hasValue) {
      new (&m_value.value) T(std::move(other.m_value));
      other.m_value.value.~T();
      other.m_hasValue = false;
    }
  }

  Optional& operator=(Optional const& other) {
    if (this != &other) {
      if (other.m_hasValue)
        new (&m_value.value) T(other.m_value);
      
      m_hasValue = other.m_hasValue;
    }
    return *this;
  }

  Optional& operator=(Optional&& other) {
    if (this != &other) {
      if (m_hasValue) {
        m_value.value.~T();
      }

      if (other.m_hasValue) {
        new (&m_value.value) T(other.m_value);
      }
      m_hasValue = other.m_hasValue;
    }
    return *this;
  }

  ~Optional() {
    if (m_hasValue) {
      m_value.value.~T();
    }
  }

  bool hasValue() const {
    return m_hasValue;
  }

  T& value() {
    if (!hasValue())
      throw BadOptionalAccess();
    return m_value.value;
  }

  T const& value() const {
    if (!hasValue())
      throw BadOptionalAccess();
    return m_value.value;
  }

  void swap(Optional& other) {
    // това е т.нар. Argument-Dependent Lookup (ADL). 
    // ще говорим за него, когато вземем move семантики :)
    using std::swap;
    
    if (m_hasValue && other.m_hasValue) {
      swap(m_value.value, other.m_value);
    }
    else if (m_hasValue) {
      new (&other.m_value.value) T(m_value);
      m_value.value.~T();
    }
    else if (other.m_hasValue) {
      new (&m_value.value) T(other.m_value);
      other.m_value.value.~T();
    }

    std::swap(m_hasValue, other.m_hasValue);
  }

private:
  union Value { 
    T value; 

    Value() {}
    ~Value() {}
  } m_value;
  bool m_hasValue;
};

#endif // __OPTIONAL_HPP
