#include <iostream>
#include <vector>
#include <forward_list>  // STL имплементация на линеен едносвързан списък
#include "Exception.hpp"
#include "RuntimeError.hpp"
#include "OutOfRange.hpp"
#include "BadCast.hpp"
#include "Optional.hpp"
#include "Comparator.hpp"

double div(double a, double b) {
  if (b==0)
    throw RuntimeError("division by zero");
  return a/b;
}

Optional<double> divM(double a, double b) {
  if (b==0)
    return Optional<double>();
  return Optional<double>(a/b);
}

template<typename T>
T const& at(std::vector<T> const& v, size_t idx) {
  if (idx >= v.size())
    throw OutOfRange("vector index out of range");
  return v.at(idx);
}

template<typename T>
T const& at(std::forward_list<T> const& l, size_t idx) {
  auto it = l.begin();
  for (size_t i = 0; i < idx && it != l.end(); ++i, ++it);

  if (it == l.end())
    throw OutOfRange("forward list position out of range");
  return *it;
}

class Base {
public:
  virtual void print() const=0;
};

class Der1 : public Base {
public:
  virtual void print() const {
    std::cout << "Der1\n";
  }
  void nonBaseMethod() const {
    std::cout << "non-base method for Der1\n";
  }
};

class Der2 : public Base {
public:
  virtual void print() const {
    std::cout << "Der2\n";
  }
  void nonBaseMethod() const {
    std::cout << "non-base method for Der2\n";
  }
};

template<typename B, typename D>
void callNonBaseMethod(void (D::*f)() const, B* base) {
  D* ptr = dynamic_cast<D*>(base);
  if (!ptr)
    throw BadCast();
  (ptr->*f)();
}

int main() {

  double a, b;
  std::cin >> a >> b;
  
  try {
    std::cout << div(a,b) << '\n';
  }
  catch (Exception const& e) {
    std::cout << e.what() << '\n';
  }

  Optional<double> res = divM(a, b);
  if (res.hasValue()) {
    std::cout << "The division of a and b yields " << res.value() << ".\n";
  }
  else {
    std::cout << "The laws of mathematics prohibit us from the blasphemy of dividing by zero!\n";
  }

  std::vector<int> v{1,2,3,4,5};
  std::forward_list<int> l;
  for (int i = 5; i >= 1; --i)
    l.push_front(i);

  try {
    std::cout << at(v, 4) << '\n';
    std::cout << at(v, 5) << '\n';
  }
  catch (Exception const& e) {
    std::cout << e.what() << '\n';
  }

  try {
    std::cout << at(l, 4) << '\n';
    std::cout << at(l, 5) << '\n';
  }
  catch (OutOfRange const& e) {
    std::cout << e.what() << '\n';
  }

  Der1* ptr1 = new Der1();
  Der2* ptr2 = new Der2();

  try {
    callNonBaseMethod<Base, Der1>(&Der1::nonBaseMethod, ptr1);
    callNonBaseMethod(&Der2::nonBaseMethod, ptr2);
    callNonBaseMethod(&Der2::nonBaseMethod, ptr1);  // ptr1 is of type Der1*
  }
  catch (Exception const& e) {
    std::cout << e.what() << '\n';
  }

  Comparator<int> icmp;
  std::cout << icmp(1,2) << '\n';

  Comparator<char const*> scmp;
  std::cout << scmp("hello, world!", "Hello, world!") << '\n';

  return 0;
}
