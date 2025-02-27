#include <iostream>

unsigned int fixedPoints(int a, int b, int(*f)(int)) {
  unsigned int cnt = 0;
  for (int x = a; x <= b; ++x) {
    if (f(x)==x) cnt++;
  }
  return cnt;
}

int main() {

  std::cout << fixedPoints(-100,100,[](int x){ return x; }) << '\n';
  std::cout << fixedPoints(0,1000,[](int x){ return x%500; }) << '\n';
  std::cout << fixedPoints(-1000,1000,[](int x){ return x+1; }) << '\n';

  return 0;
}