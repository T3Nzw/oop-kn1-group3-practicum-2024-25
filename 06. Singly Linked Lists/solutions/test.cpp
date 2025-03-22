#include "LinkedList.hpp"
#include "LinkedListUtils.hpp"
#include <iostream>

int main() {

  LinkedList<int> l1;
  LinkedList<int> l2;

  l1.push_back(-1);
  l1.push_back(4);
  l1.push_back(4);
  l1.push_back(4);
  l1.push_back(5);
  l1.push_back(6);
  l1.push_back(10);

  l1.print();
  l1.reverse();
  l1.print();

  for (int i = 0; i < 10; ++i)
    l2.push_back(i);

  for (int i = 0; i < 10; ++i)
    std::cout << l2.at(i) << ' ';

  std::cout << '\n';

  l2.pop_at(2);
  l2.pop_at(8);

  l2.print();

  l2.push_at(l2.size(),9);
  l2.push_at(2,2);
  l2.push_at(0,-1);

  l2.print();

  std::cout << l2.pop_front() << ' ';
  std::cout << l2.pop_back() << '\n';

  l2.reverse();
  l2.print();

  l1.reverse();
  l2.reverse();

  LinkedList<int> l3 = LinkedListUtils::merge(l1,l2);
  l3.print();

  LinkedListUtils::removeDuplicates(l3);
  l3.print();

  LinkedList<int> l4;
  for (int i = 0; i <= 10; ++i)
    l4.push_front(i);

  l4.print();
  LinkedListUtils::sort(l4);
  l4.print();

  std::cout << std::boolalpha;
  std::cout << LinkedListUtils::isPalindrome(l4) << '\n';

  LinkedList<int> l5;
  l5.push_back(1);
  l5.push_back(2);
  l5.push_back(3);
  l5.push_back(2);
  l5.push_back(1);

  std::cout << LinkedListUtils::isPalindrome(l5) << '\n';
  l5.pop_at(2);
  std::cout << LinkedListUtils::isPalindrome(l5);

  return 0;
}