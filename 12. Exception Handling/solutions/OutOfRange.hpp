#ifndef __OUT_OF_RANGE_HPP
#define __OUT_OF_RANGE_HPP

#include "Exception.hpp"

class OutOfRange : public Exception {
public:
  OutOfRange(char const* msg) : msg(msg) {}
  virtual char const* what() const noexcept override final {
    return msg;
  }
private:
  char const* msg;
};

#endif // __OUT_OF_RANGE_HPP 
