#ifndef __RELATION_HPP
#define __RELATION_HPP

#include "Set.hpp"

template<typename T>
struct Pair {
  T first;
  T second;

  bool operator==(Pair const& other) {
    return first == other.first
        && second == other.second;
  }

  friend std::ostream& operator<<(std::ostream& os, Pair const& pair) {
    os << '(' << pair.first << ',' << pair.second << ')';
    return os;
  }
};

template<typename T>
class Relation {
public:
  bool empty() const { return m_relation.empty(); }

  bool contains(Pair<T> const& pair) const {
    return m_relation.contains(pair);
  }

  void insert(Pair<T> const& pair) {
    if (!m_set.contains(pair.first) || !m_set.contains(pair.second)) return;
    if (contains(pair)) return;
    m_relation.push_back(pair);
  }

  void reflexiveClosure() {
    for (size_t i = 0; i < m_set.size(); ++i) {
      Pair<T> pair{m_set[i],m_set[i]};
      if (!contains(pair)) {
        m_relation.push_back(pair);
      }
    }
  }

  void symmetricClosure() {
    size_t initialSize = m_relation.size();
    for (size_t i = 0; i < m_relation.size(); ++i) {
      Pair<T> pair{m_relation[i].second,m_relation[i].first};
      if (!contains(pair)) 
        m_relation.push_back(pair);
    }
  }

  bool isReflexive() const {
    for (size_t i = 0; i < m_set.size(); ++i) {
      Pair<T> pair{m_set[i],m_set[i]};
      if (!contains(pair))
        return false;
    }
    return true;
  }

  bool isSymmetric() const {
    for (size_t i = 0; i < m_relation.size(); ++i) {
      Pair<T> pair{m_relation[i].second,m_relation[i].first};
      if (!contains(pair))
        return false;
      }
    return true;
  }

  bool isTransitive() const {
    for (size_t i = 0; i < m_relation.size(); ++i) {
      Pair<T> pair1 = m_relation[i];
      for (size_t j = 0; j < m_relation.size(); ++j) {
      //не е нужно, но е по-четимо
        Pair<T> pair2 = m_relation[j];
        if (pair1.second != pair2.first)
          continue;
          
        Pair<T> pair3{pair1.first,pair2.second};
        if (!contains(pair3))
          return false;
      }
    }
    return true;
  }

  bool isEquivalenceRelation() const {
    return isReflexive()
        && isSymmetric()
        && isTransitive();
  }

  friend std::ostream& operator<<(std::ostream& os, Relation const& relation) {
    os << '{';
    if (relation.empty()) {
      os << '}';
      return os;
    }
    for (size_t i = 0; i < relation.m_relation.size()-1; ++i) {
      os << relation.m_relation[i] << ", ";
    }
    os << relation.m_relation[relation.m_relation.size()-1] << '}';
    return os;
  }

public:
  Relation(Set<T> const& set)
  : m_set(set) {}

  Relation(Set<T> const& set, Vector<Pair<T> > relation)
  : m_set(set), m_relation(relation) {}

  Relation(Relation const&)=default;
  
private:
  Set<T> m_set;
  Vector<Pair<T> > m_relation;
};

#endif // __RELATION_HPP