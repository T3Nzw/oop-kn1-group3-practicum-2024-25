#ifndef __COMPARATOR_HPP
#define __COMPARATOR_HPP

#include <cstring>

template<typename T>
class Comparator {
public:
  int operator()(T const& lhs, T const& rhs) {
    if      (lhs < rhs)  return -1;
    else if (lhs == rhs) return  0;
                         return  1;
  }
};

template<>
class Comparator<char const*> {
public:
  int operator()(char const* lhs, char const* rhs) {
    // strcmp не връща точно -1 или 1, а някаква отрицателна
    // и някаква положителна стойност, но ще го преживеем :)
    return strcmp(lhs, rhs);
  }
};

#endif // __COMPARATOR_HPP 
