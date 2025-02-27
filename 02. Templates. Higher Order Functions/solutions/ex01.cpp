#include <iostream>

template<typename T>
void swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}

int main() {

  int a = 10, b = 12;
  swap<int>(a,b); 
  std::cout << a << ' ' << b << std::endl;

  struct Point{ double x,y; } p1{4.5,3}, p2{12,7};
  swap<Point>(p1,p2); 
  std::cout << '(' << p1.x << ',' << p1.y << ") "
            << '(' << p2.x << ',' << p2.y << ')';

  return 0;
}