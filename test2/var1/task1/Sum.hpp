#ifndef __SUM_HPP 
#define __SUM_HPP

#include "Aggregator.hpp"

class Sum : public Aggregator {
public:
  virtual double result() const override;
};

#endif // __SUM_HPP
