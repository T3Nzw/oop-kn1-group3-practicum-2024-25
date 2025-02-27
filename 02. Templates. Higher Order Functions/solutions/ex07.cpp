#include <iostream>

template<typename T>
using BinaryOperation = T(*)(T,T);

template<typename T>
BinaryOperation<T> operation(char c) {
  switch (c) {
    case '+':
      return [](T a, T b) { return a+b; };
    case '-':
      return [](T a, T b) { return a-b; };
    case '*':
      return [](T a, T b) { return a*b; };
    case '/':
      return [](T a, T b) { return a/b; };
    default:
      throw std::invalid_argument("invalid operation");
  }
}

template<typename T>
T apply(BinaryOperation<T> op, T const& a, T const& b) {
  return op(a,b);
}

int main() {

  std::cout << apply(operation<int>('+'),5,6) << '\n';
  std::cout << apply<double>(operation<double>('*'),20.3,-1);

  return 0;
}