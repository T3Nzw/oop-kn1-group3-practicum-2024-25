#include <iostream>
#include <cfloat>

template<typename T>
T max(T a, T b) {
  return a > b ? a : b;
}

template<>
float max<float>(float a, float b) {
  return a-b > FLT_EPSILON ? a : b;
}

template<>
double max<double>(double a, double b) {
  return a-b > DBL_EPSILON ? a : b;
}

int main() {

  std::cout << max<int>(1,2) << std::endl;
  std::cout << max<double>(0.29999999999,0.3) << std::endl;
  std::cout << max<float>(0.29999999999,0.3) << std::endl;

  return 0;
}