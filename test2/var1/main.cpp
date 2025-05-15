#include "task1/Aggregator.hpp"
#include "task1/Sum.hpp"
#include "task1/Avg.hpp"
#include "task1/Foldr.hpp"
#include "task2/VectorStream.hpp"
#include <iostream>

int main() {

  VectorStream<int> vs({1,2,3,4,5});

  int a, b, c, d, e;
  vs >> a >> b >> c >> d >> e;

  std::cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << '\n';

  vs.reset();

  std::cout << vs.peek() << '\n';

  std::vector<double> vec{1,2,3,4,5,6,7,8,9, 10};
  Sum sum;
  Avg avg;
  Foldr foldr([](double lhs, double rhs) { return lhs - rhs; });

  std::cout << '\n';

  std::cout << reduce(vec, sum) << '\n';
  std::cout << reduce(vec, avg) << '\n';
  std::cout << reduce(vec, foldr) << '\n';

  Foldr* maxer = new Foldr([](double lhs, double rhs) -> double { return std::max(lhs, rhs); });
  std::cout << reduce({1,2,3,4, 100, 5}, maxer) << '\n';

  delete maxer;

  return 0;
}
