#include <iostream>
#include <fstream>

bool halve(char const* filename, char const* result) {
  std::ifstream ifile(filename);
  std::ofstream ofile(result);
  if (!ifile || !ofile) {
    std::cerr << "could not open file";
    return false;
  }
  
  ifile.seekg(0,std::ios::end);
  std::streamsize halfSize = ifile.tellg()/2;
  ifile.seekg(0);
  ofile.seekp(0);

  while (halfSize--) {
    ofile.put(ifile.get());
  }

  ifile.close();
  ofile.close();

  return true;
}

int main() {

  halve("files/hello_world.txt","files/result.txt");

  return 0;
}