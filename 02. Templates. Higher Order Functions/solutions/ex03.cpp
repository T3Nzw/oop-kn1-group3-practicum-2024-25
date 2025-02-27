#include <iostream>

template<typename T>
void bubbleSort(T arr[], size_t size) {
  for (size_t i = 0; i < size-1; ++i) {
    bool swapped = false;
    for (size_t j = 0; j < size-i-1; ++j) {
      if (arr[j] > arr[j+1]) {
        std::swap(arr[j],arr[j+1]);
        swapped = true;
      }
    }
    if (!swapped) return;
  }
}
int main() {

  int arri[]{3,7,1,9};
  bubbleSort<int>(arri,sizeof(arri)/sizeof(int)); 
  for (unsigned int i = 0; i < 4; ++i)
    std::cout << arri[i] << ' ';

  std::cout << std::endl;
  char arrc[] = "a string is also an array!";
  //minus 1 because of terminating zero
  bubbleSort<char>(arrc,sizeof(arrc)-1);
  std::cout << arrc;

  return 0;
}