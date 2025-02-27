#include <iostream>

template<typename T, typename U>
U accumulate(T* begin, T* end, U const& nv, U(*op)(U const&, T const&)) {
  U res = nv;
  while (begin <= end) {
    res = op(res,*begin);
    ++begin;
  }
  return res;
}

int main() {

  int arr[5]{1,2,3,4,5};
  std::cout << accumulate<int,int>(arr,arr+4,0,[](int const& x, int const& y) -> int { return x+y; }) << std::endl;
  std::cout << accumulate<int,char>(arr,arr+4,'a',[](char const& x, int const& y) -> char { return (x+y)%256; });

  return 0;
}