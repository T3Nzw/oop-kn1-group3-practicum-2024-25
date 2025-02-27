#include <iostream>

template<typename T, typename U>
struct Pair {
  T a;
  U b;
};

template<typename T, typename U>
void print(Pair<T,U> const& p) {
  std::cout << '(' << p.a << ',' << p.b << ')';
}

template<typename T, typename U>
Pair<T,U> add(Pair<T,U> const& p1, Pair<T,U> const& p2) {
  return {p1.a+p2.a, p1.b+p2.b};
}

template<typename T, typename U>
Pair<U,T> reverse(Pair<T,U> const& p) {
  return {p.b,p.a};
}

template<typename T, typename U>
int compare(Pair<T,U> const& p1, Pair<T,U> const& p2) {
  if (p1.a==p2.a && p1.b==p2.b) return 0;
  else if (p1.a<p2.a || (p1.a==p2.a && p1.b<p2.b)) return -1;
  return 1;
}

template<typename T, typename U>
void sort(Pair<T,U> arr[], size_t size) {
  for (size_t i = 0; i < size-1; ++i) {
    size_t minIdx = i;
    for (size_t j = i+1; j < size; ++j) {
      if (compare(arr[i],arr[j]) == 1) {
        minIdx = j;
      }
    }
    std::swap(arr[i],arr[minIdx]);
  }
}

int main() {

  Pair<int,double> pair {42,1.618};
  Pair<int,double> pair2{22,3.14};

  print(pair);
  std::cout << ' ';
  print(pair2);
  std::cout << '\n';

  print(add(pair,pair2));
  std::cout << '\n';
  print(reverse(pair));
  std::cout << '\n';

  Pair<int,int> arr[]{ {2,5},{7,3},{2,4},{10,2},{2,5} };
  sort(arr,5);
  for (unsigned int i = 0; i < 5; ++i) {
    print(arr[i]);
    std::cout << '\n';
  }

  return 0;
}