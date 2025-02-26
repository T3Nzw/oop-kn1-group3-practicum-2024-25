#include <iostream>
#include <fstream>

bool isInterval(char c) {
  return c==' ' || c=='\t';
}

bool isPunctuationMark(char c) {
  return c=='.' || c=='?' || c=='!'  ||
         c==',' || c=='/' || c=='\\' ||
         c=='(' || c==')' || c=='\'' ||
         c==';' || c==':' || c=='\"';
}

bool invalid(char c) {
  return isInterval(c) || isPunctuationMark(c);
}

size_t countWordsInFile(char const* filename) {
  std::ifstream ifile(filename);
  if (!ifile.is_open()) {
    std::cerr << "could not open file";
    return 0;
  }

  size_t words = 0;

  ifile.seekg(0);
  char prev = ifile.get(), next;
  if (ifile.eof()) return 0;

  while (ifile.get(next)) {
    if (!invalid(prev) && invalid(next)) words++;
    prev = next;
  }

  if (!invalid(next)) words++;

  ifile.close();
  return words;
}

int main() {

  std::cout << countWordsInFile("files/hello_world.txt");

  return 0;
}