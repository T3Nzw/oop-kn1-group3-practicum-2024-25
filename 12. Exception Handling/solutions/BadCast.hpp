#ifndef __BAD_CAST_HPP
#define __BAD_CAST_HPP

#include "Exception.hpp"

class BadCast : public Exception {
public:
  virtual char const* what() const noexcept override final {
    return "bad cast error: could not convert type of derived class to base class";
  }
};

#endif // __BAD_CAST_HPP 
