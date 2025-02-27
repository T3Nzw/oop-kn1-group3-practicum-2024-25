#include <iostream>

template<typename T>
using UnaryFunction = T(*)(T);

template<typename T>
T apply(UnaryFunction<T> f, T x, unsigned int n) {
  for (unsigned int i = 0; i < n; ++i) {
    x = f(x);
  }
  return x;
}

int main() {

  std::cout << apply<int>([](int x) { return x+1; },4,0) << '\n';
  std::cout << apply<int>([](int x) { return x+1; },4,3);

  return 0;
}