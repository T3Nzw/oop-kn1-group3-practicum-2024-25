#ifndef __EXCEPTION_HPP
#define __EXCEPTION_HPP

class Exception {
public:
  virtual char const* what() const noexcept=0;
};

#endif // __EXCEPTION_HPP 
