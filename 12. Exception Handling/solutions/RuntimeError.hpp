#ifndef __RUNTIME_ERROR_HPP
#define __RUNTIME_ERROR_HPP

#include "Exception.hpp"

class RuntimeError : public Exception {
public:
  RuntimeError(char const* msg) : msg(msg) {}
  virtual char const* what() const noexcept override final {
    return msg;
  }
private:
  char const* msg;
};

#endif // __RUNTIME_ERROR_HPP 
