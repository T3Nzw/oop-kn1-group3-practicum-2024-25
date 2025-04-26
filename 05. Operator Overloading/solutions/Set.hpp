#ifndef __SET_HPP
#define __SET_HPP

#include <iostream>
#include "../../04. Rule of Three/solutions/Vector.hpp"

template<typename T>
class Set {
public:
  bool empty() const { return m_set.empty(); }

  size_t size() const { return m_set.size(); }

  //ще използваме оператора за достъпване по индекс,
  //тъй като все още не знаем как се пишат итератори
  T& operator[](size_t index) {
    return m_set[index];
  }

  T const& operator[](size_t index) const {
    return m_set[index];
  }

  bool contains(T const& el) const {
    return m_set.contains(el);
  }

  bool isSubsetOf(Set const& other) const {
    for (size_t i = 0; i < this->size(); ++i)
      if (!other.contains(m_set[i]))
        return false;
    
    return true;
  }

  bool isEqualTo(Set const& other) const {
    return this->isSubsetOf(other)
        && other.isSubsetOf(*this);
  }

  Set& unifyMutable(Set const& other) {
    for (size_t i = 0; i < other.size(); ++i) {
      if (!contains(other.m_set[i]))
        m_set.push_back(other.m_set[i]);
    }
    return *this;
  }

  Set unify(Set const& other) const {
    Set res(*this);
    res.unifyMutable(other);
    return res;
  }

  Set& intersectMutable(Set const& other) {
    Set temp;
    for (size_t i = 0; i < other.size(); ++i) {
      if (contains(other.m_set[i]))
        temp.m_set.push_back(other.m_set[i]);
    }
    *this = temp;
    return *this;
  }

  Set intersect(Set const& other) const {
    Set res(*this);
    res.intersectMutable(other);
    return res;
  }

  Set& differenceMutable(Set const& other) {
    Set temp;
    for (size_t i = 0; i < size(); ++i) {
      if (!other.contains(m_set[i]))
        temp.m_set.push_back(m_set[i]);
    }
    *this = temp;
    return *this;
  }

  Set difference(Set const& other) const {
    Set res(*this);
    res.differenceMutable(other);
    return res;
  }

  Set& symmetricDifferenceMutable(Set const& other) {
    Set res(this->unify(other));
    return *this = res.difference(this->intersect(other));
  }

  Set symmetricDifference(Set const& other) const {
    Set res(*this);
    res.symmetricDifferenceMutable(other);
    return res;
  }

  Set operator+(Set const& other) const {
    return unify(other);
  }

  Set& operator+=(Set const& other) {
    return unifyMutable(other);
  }

  Set operator*(Set const& other) const {
    return intersect(other);
  }

  Set& operator*=(Set const& other) {
    return intersectMutable(other);
  }

  Set operator-(Set const& other) const {
    return difference(other);
  }

  Set& operator-=(Set const& other) {
    return differenceMutable(other);
  }

  Set operator^(Set const& other) const {
    return symmetricDifference(other);
  }

  Set& operator^=(Set const& other) {
    return symmetricDifferenceMutable(other);
  }

  bool operator<=(Set const& other) const {
    return isSubsetOf(other);
  }

  bool operator==(Set const& other) const {
    return isEqualTo(other);
  }

  void print(std::ostream& os=std::cout) const {
    os << '{';
    if (empty()) {
      os << '}';
      return;
    }
    for (size_t i = 0; i < m_set.size()-1; ++i)
      os << m_set[i] << ',';
    os << m_set[m_set.size()-1] << '}';
  }

  friend std::ostream& operator<<(std::ostream& os, Set const& set) {
    set.print(os);
    return os;
  }

public:
  Set()=default;

  Set(std::initializer_list<T> const& l) {
    for (auto it1 = l.begin(); it1 != l.end(); ++it1) {
      bool isContained = false;
      for (auto it2 = it1+1; it2 != l.end(); ++it2) {
        if (*it1 == *it2) {
          isContained = true;
          break;
        }
      }
      if (!isContained)
        m_set.push_back(*it1);
    }
  }

  Set(Set const& other) : m_set(other.m_set) {}

  Set& operator=(Set const& other) {
    m_set = other.m_set;
    return *this;
  }

  ~Set()=default;

private:
  Vector<T> m_set;
};

#endif // __SET_HPP
