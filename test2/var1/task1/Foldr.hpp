#ifndef __FOLDR_HPP 
#define __FOLDR_HPP

#include "Aggregator.hpp"
#include <functional>

class Foldr: public Aggregator {
public:
  Foldr(std::function<double(double, double)> const& op) : op(op) {}
  virtual double result() const override;
private:
  std::function<double(double, double)> op; 
};

#endif // __FOLDR_HPP 
