#include "Foldr.hpp"

double Foldr::result() const {
  if (seq.empty()) return 0;
  double nv = seq[seq.size()-1]; 
  for (long long i = seq.size()-2; i >= 0; --i) {
    nv = op(seq[i], nv);
  }
  return nv;
}
