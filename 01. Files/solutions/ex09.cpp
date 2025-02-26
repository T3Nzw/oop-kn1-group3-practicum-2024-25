#include <iostream>
#include <fstream>

struct ResizingArray {
  int* data;
  size_t size;
  size_t capacity;
};

void resize(ResizingArray& arr) {
  int* newData = new int[arr.capacity = arr.capacity ? arr.capacity*2 : 1];
  for (size_t i = 0; i < arr.size; ++i) {
    newData[i] = arr.data[i];
  }
  delete[] arr.data;
  arr.data = newData;
}

bool numbersInFile(char const* filename, ResizingArray& arr) {
  std::ifstream ifile(filename,std::ios::in|std::ios::binary);
  if (!ifile) {
    std::cerr << "could not open file";
    return false;
  }

  ifile.seekg(0);
  int num;
  while (ifile.read((char*)&num,sizeof(int))) {
    if (arr.size>=arr.capacity) resize(arr);
    arr.data[arr.size++] = num;
  }

  return true;
}

int main() {

  std::ofstream ofile("files/numbers.bin",std::ios::out|std::ios::binary);
  for (int i = 0; i <= 100; ++i) {
    ofile.write((char const*)&i,sizeof(int));
  }
  ofile.close();  //!!!

  ResizingArray arr{nullptr,0,0};
  numbersInFile("files/numbers.bin",arr);

  for (size_t i = 0; i < arr.size; ++i) {
    std::cout << arr.data[i] << ' ';
  }

  return 0;
}