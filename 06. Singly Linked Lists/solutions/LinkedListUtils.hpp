#ifndef __LINKED_LIST_UTILS_HPP
#define __LINKED_LIST_UTILS_HPP

#include "LinkedList.hpp"

/*
!!!
следните имплементации са сравнително неефикасни и бавни.
ще пренапишем логиката за тези алгоритми, след като
имаме необходимите абстракции за позиция в списък,
а именно итератори
*/

class LinkedListUtils {
public:
  template<typename T>
  static LinkedList<T> merge(LinkedList<T> const& l1, LinkedList<T> const& l2);
  
  template<typename T>
  static void sort(LinkedList<T>& l);

  template<typename T>
  static void removeDuplicates(LinkedList<T>& l);

  template<typename T>
  static bool isPalindrome(LinkedList<T> const& l);
};

template<typename T>
LinkedList<T> LinkedListUtils::merge(LinkedList<T> const& l1, LinkedList<T> const& l2) {
  size_t size1 = l1.size(), size2 = l2.size();
  size_t index1 = 0, index2 = 0;
  LinkedList<T> res;

  while (index1<size1 && index2<size2) {
    T const& el1 = l1.at(index1), & el2 = l2.at(index2);
    if (el1 <= el2) {
      res.push_back(el1);
      index1++;
    }
    else {
      res.push_back(el2);
      index2++;
    }
  }

  while (index1<size1) {
    res.push_back(l1.at(index1));
    index1++;
  }

  while (index2<size2) {
    res.push_back(l2.at(index2));
    index2++;
  }

  return res;
}

template<typename T>
void LinkedListUtils::sort(LinkedList<T>& l) {
  size_t size = l.size();
  for (size_t i = 0; i < size-1; ++i) {
    bool swapped = false;
    for (size_t j = 0; j < size-1-i; ++j) {
      if (l.at(j+1) < l.at(j)) {
        std::swap(l.at(j+1),l.at(j));
        swapped = true;
      }
    }
    if (!swapped) return;
  }
}

template<typename T>
void LinkedListUtils::removeDuplicates(LinkedList<T>& l) {
  size_t size = l.size();
  for (size_t i = 1; i < size;) {
    if (l.at(i-1) == l.at(i)) {
      l.pop_at(i);
      size--;
    }
    else i++;
  }
}

//има и по-елегантен начин за проверка дали списък е палиндром
//чрез обръщане на едната половина на списъка и проверка дали стойностите
//в двете половини съвпадат
template<typename T>
bool LinkedListUtils::isPalindrome(LinkedList<T> const& l) {
  LinkedList<T> l2(l);
  l2.reverse();

  size_t size = l.size();

  for (size_t i = 0; i < size; ++i) {  //понеже знаем, че и двата списъка са с еднаква дължина
    if (l.at(i) != l2.at(i))
      return false;
  }

  return true;
}

#endif // __LINKED_LIST_UTILS_HPP