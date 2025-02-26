#include <iostream>
#include <fstream>
#include <cstring>

unsigned int const MAX_SIZE = 1024;

size_t resize(char*& buffer, size_t size) {
  char* newBuffer = new char[size*2];
  for (size_t i = 0; i < size; ++i) {
    newBuffer[i] = buffer[i];
  }
  delete[] buffer;
  buffer = newBuffer;
  return size*2;
}

void replace(char*& s, size_t& capacity, char const* oldS, char const* newS) {
  char* cpy = new char[capacity];  //read-only copy of the string
  strcpy(cpy,s);

  size_t read = 0, write = 0;
  size_t oldSize = strlen(oldS);
  while (cpy[read]) {
    if (!strncmp(cpy+read,oldS,oldSize)) {
      read+=oldSize;

      for (size_t i = 0; newS[i] != '\0'; ++i) {
        if (write>=capacity) capacity = resize(s,capacity);
        s[write++] = newS[i];
      }
    }
    else {
      s[write++] = cpy[read++];
    }
  }

  if (write>=capacity) capacity = resize(s,capacity);
  s[write] = '\0';
}

bool replaceInFile(char const* filename, char const* oldS, char const* newS) {
  std::ifstream ifile(filename);
  //std::ios::trunc ensures that a new file is created
  //if one with the name "helper.txt" doesn't exist,
  //otherwise it erases the file's contents
  std::fstream iofile("files/helper.txt",std::ios::in|std::ios::out|std::ios::trunc);
  if (!ifile || !iofile) {
    std::cerr << "could not open file";
    return false;
  }

  ifile.seekg(0);
  iofile.seekp(0);
  
  size_t capacity = 1024;
  char* buffer = new char[capacity];
  while (ifile.getline(buffer,capacity)) {
    replace(buffer,capacity,oldS,newS);
    iofile << buffer << std::endl;
  }

  ifile.close();

  std::ofstream ofile(filename);
  if (!ofile) {
    std::cout << "could not open file";
    return false;
  }

  ofile.seekp(0);
  iofile.seekg(0);

  while (iofile.getline(buffer,capacity)) {
    ofile << buffer << std::endl;
  }

  ofile.close();
  iofile.close();
  delete[] buffer;

  return true;
}

int main() {

  replaceInFile("files/replaced.txt","file","FILES!");

  return 0;
}