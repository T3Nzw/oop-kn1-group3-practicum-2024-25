#ifndef __AVG_HPP
#define __AVG_HPP

#include "Aggregator.hpp"

// класът би могъл да наследява пряко и Sum
class Avg : public Aggregator {
public:
  virtual double result() const override;
};

#endif // __AVG_HPP
