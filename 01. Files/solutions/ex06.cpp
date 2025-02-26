#include <iostream>
#include <fstream>
#include <cstring>

unsigned int const MAX_SIZE = 1024;

struct ResizingArray {
  char (*data)[MAX_SIZE];
  size_t size;
  size_t capacity;
};

void resize(ResizingArray& arr) {
  char (*newData)[MAX_SIZE] = new char[arr.capacity = arr.capacity ? arr.capacity*2 : 1][MAX_SIZE];
  for (size_t i = 0; i < arr.size; ++i) {
    strcpy(newData[i],arr.data[i]);
  }
  delete[] arr.data;
  arr.data = newData;
}

void sort(ResizingArray& arr) {
  for (size_t i = 0; i < arr.size-1; ++i) {
    for (size_t j = i+1; j < arr.size; ++j) {
      if (strcmp(arr.data[i],arr.data[j]) > 0) {
        std::swap(arr.data[i],arr.data[j]);
      }
    }
  }
}

bool sort(char const* filename, char const* result) {
  std::ifstream ifile(filename);
  std::ofstream ofile(result);
  if (!ifile || !ofile) {
    std::cerr << "could not open file";
    return false;
  }

  ifile.seekg(0);
  ofile.seekp(0);
  ResizingArray arr{nullptr,0,0};
  char buffer[MAX_SIZE];
  size_t i = 0;
  while (ifile.getline(buffer,MAX_SIZE)) {
    if (arr.size>=arr.capacity) resize(arr);
    strcpy(arr.data[arr.size++],buffer);
  }

  sort(arr);

  for (size_t i = 0; i < arr.size-1; ++i) {
    ofile << arr.data[i] << std::endl;
  }
  ofile << arr.data[arr.size-1];

  return true;
}

enum class Error { NONE, FILE_NOT_OPEN };

int main() {

  sort("files/unsorted.txt","files/sorted.txt");

  return 0;
}