#include <iostream>
#include <fstream>

int main() {

  char const* file = "ex02.cpp";
  std::ifstream ifile(file, std::ios::in);
  ifile.seekg(0, std::ios::beg);

  if (!ifile) {
    std::cout << "Could not open file $" << file << "$";
    return -1;
  }

  char buffer[1024];
  while (!ifile.eof()) {
    ifile.getline(buffer,1024);
    std::cout << buffer << std::endl;
  }

  ifile.close();

  return 0;
}