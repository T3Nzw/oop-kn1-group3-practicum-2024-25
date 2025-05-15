#ifndef __AGGREGATOR_HPP
#define __AGGREGATOR_HPP

#include <vector>
#include <stdexcept>

class Aggregator {
public:
  void add(double x) {
    seq.push_back(x);
  }

  virtual double result() const=0;

protected:
  std::vector<double> seq;
};

inline double reduce(std::vector<double> const& vec, Aggregator& aggregator) {
  for (double el : vec) aggregator.add(el);
  return aggregator.result();
}

inline double reduce(std::vector<double> const& vec, Aggregator* aggregator) {
  if (!aggregator)
    throw std::runtime_error("attempted to dereference nullptr");
  for (double el : vec) aggregator->add(el);
  return aggregator->result();
}

#endif // __AGGREGATOR_HPP
