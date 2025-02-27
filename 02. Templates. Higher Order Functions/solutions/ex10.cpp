#include <iostream>
#include <functional>

//the reason for using std::function
//is because we use a capture clause inside
//partialFunctionApplication
template<typename Ret, typename T>
using UnaryFunction = std::function<Ret(T)>;

template<typename Ret, typename T, typename U>
using BinaryFunction = std::function<Ret(T,U)>;

template<typename Ret, typename T, typename U>
UnaryFunction<Ret,U> partialFunctionApplication(BinaryFunction<Ret,T,U> op, T const& lArg) {
  //capture by value since lArg might be an rvalue
  //at the call site
  return [=](U rArg) -> Ret { return op(lArg,rArg); };
}

int main() {

  BinaryFunction<int,int,int> add = [](int x, int y){ return x+y; };
  std::cout << partialFunctionApplication(add,3)(2);

  return 0;
}