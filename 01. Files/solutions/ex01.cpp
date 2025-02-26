#include <iostream>
#include <fstream>

unsigned int const MAX_MSG_SIZE = 1024;
unsigned int const ASCII_SIZE = 256;

char encrypt(char c) {
  return (c+1)%ASCII_SIZE;
}

char decrypt(char c) {
  //c+256-1
  return (c+255)%ASCII_SIZE;
}

void write(char const* filename, char const* msg) {
  std::ofstream ofile(filename, std::ios::out);
  ofile.seekp(0, std::ios::beg);

  while (*msg) {
    ofile << encrypt(*msg);
    msg++;
  }

  ofile.close();
}

void print(char const* filename) {
  std::ifstream ifile(filename, std::ios::in);
  ifile.seekg(0, std::ios::beg);

  char buf;
  while (ifile.get(buf)) {
    std::cout << decrypt(buf);
  }

  ifile.close();
}

int main() {

  char msg[MAX_MSG_SIZE];
  std::cin.getline(msg,MAX_MSG_SIZE);

  char const* filename = "files/encrypted.txt";
  write(filename,msg);
  print(filename);

  return 0;
}