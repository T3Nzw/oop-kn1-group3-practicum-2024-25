#include <iostream>

template<typename T>
struct ResizingArray {
  T* data;
  size_t size;
  size_t capacity;
};

template<typename T>
void free(ResizingArray<T>& arr) {
  delete[] arr.data;
}

template<typename T, typename U>
ResizingArray<U> map(U(*f)(T const&), ResizingArray<T> const& arr) {
  ResizingArray<U> res{new U[arr.size],arr.size,arr.size};
  for (size_t i = 0; i < arr.size; ++i) {
    res.data[i] = f(arr.data[i]);
  }
  return res;
}

template<typename T>
ResizingArray<T> filter(bool(*p)(T const&), ResizingArray<T> const& arr) {
  ResizingArray<T> res{new T[arr.size],0,arr.size};
  for (size_t i = 0; i < arr.size; ++i) {
    if (p(arr.data[i])) {
      res.data[res.size++] = arr.data[i];
    }
  }
  return res;
}

int main() {

  ResizingArray<int> arr1{new int[20],20,20};
  for (int i = 0; i < arr1.size; ++i)
    arr1.data[i] = i;

  ResizingArray<double> arr2 = map<int,double>([](int const& x) -> double { return (x+1)*0.1; },arr1);
  for (int i = 0; i < arr2.size; ++i) {
    std::cout << arr2.data[i] << ' ';
  }
  std::cout << '\n';

  ResizingArray<int> arr3 = 
    filter<int>([](int const& x) -> bool { return x%2 == 0; }, arr1);

  for (int i = 0; i < arr3.size; ++i) {
    std::cout << arr3.data[i] << ' ';
  }
  std::cout << '\n';

  free(arr1);
  free(arr2);
  free(arr3);

  return 0;
}