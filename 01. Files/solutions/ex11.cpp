#include <iostream>
#include <fstream>

struct DynamicArray {
  int* data;
  size_t size;
};

void writeToFile(char const* filename, DynamicArray const* arrs, size_t size) {
  std::ofstream ofile(filename, std::ios::out|std::ios::binary);
  ofile.seekp(0, std::ios::beg); //redundant

  for (size_t i = 0; i < size; ++i) {
    ofile.write((char*)&arrs[i].size,sizeof(arrs[i].size));
    for (size_t j = 0; j < arrs[i].size; ++j) {
      ofile.write((char*)&arrs[i].data[j],sizeof(arrs[i].data[j]));
    }
  }

  ofile.close();
}

void printContents(char const* filename) {
  std::ifstream ifile(filename, std::ios::in|std::ios::binary);
  ifile.seekg(0, std::ios::beg);

  size_t currSize;
  while (ifile.read((char*)&currSize,sizeof(size_t))) {
    for (size_t i = 0; i < currSize; ++i) {
      int elem;
      ifile.read((char*)&elem,sizeof(int));
      std::cout << elem << ' ';
    }
    std::cout << '\n';
  }

  ifile.close();
}

int main() {

  DynamicArray arrs[10]{};
  for (size_t i = 0; i < 10; ++i) {
    arrs[i].size = i+10;
    arrs[i].data = new int[arrs[i].size];
    for (size_t j = 0; j < arrs[i].size; ++j) {
      arrs[i].data[j] = j+1;
    }
  }

  char const* filename = "files/dyn_arrs.bin";
  writeToFile(filename,arrs,10);
  printContents(filename);

  for (size_t i = 0; i < 10; ++i) {
    delete[] arrs[i].data;
  }

  return 0;
}