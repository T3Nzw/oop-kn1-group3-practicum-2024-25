#include "Sum.hpp"

double Sum::result() const {
  double sum = 0;
  for (double el : seq) sum += el;
  return sum;
}
