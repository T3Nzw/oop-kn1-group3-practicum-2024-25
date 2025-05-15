#ifndef __VECTOR_STREAM_HPP
#define __VECTOR_STREAM_HPP

#include <stdexcept>
#include <vector>

template<typename T>
class VectorStream {
public:
  VectorStream(std::vector<T> const& vec) : vec(vec), pos(0) {}

  VectorStream& operator>>(T& elem) {
    if (vec.empty()) {
      elem = T();
    }
    else {
      elem = vec[pos];
      pos = std::min(pos+1, vec.size()-1);
    }
    return *this;
  }

  void reset() { pos = 0; }

  T const& peek() const { 
    if (vec.empty()) throw std::runtime_error("invalid position");
    return vec[pos]; 
  }

private:
  std::vector<T> vec;
  size_t pos;
};

#endif // __VECTOR_STREAM_HPP 
