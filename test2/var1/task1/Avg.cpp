#include "Avg.hpp"

double Avg::result() const {
  if (seq.empty()) return 0;
  double avg = 0;
  for (double el : seq) avg += el;
  return avg / seq.size();
}
