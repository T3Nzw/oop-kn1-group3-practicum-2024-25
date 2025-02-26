#include <iostream>
#include <fstream>

double sumNumbersInFile(char const* filename) {
  std::ifstream ifile(filename);
  if (!ifile) {
    std::cerr << "could not open file \"" << filename << "\"";
    return 0;
  }

  ifile.seekg(0);
  double sum  = 0, cur = 0;
  char sign = 1;
  char buf;
  while (ifile.get(buf)) {
    if (buf=='-' && std::isdigit(ifile.peek())) {
      sign = -1;
      ifile.get(buf);
    }
    
    if (std::isdigit(buf)) {
      cur = buf-'0';
      while (std::isdigit(buf = ifile.get())) {
        cur = cur*10 + buf-'0';
      }
      if (buf=='.') {
        double prec = 0.1;
        while (std::isdigit(buf = ifile.get())) {
          cur += (buf-'0')*prec;
          prec*=0.1;
        }
      }
      sum+=sign*cur;
      sign = 1;
    }

    cur = 0;
  }

  return sum;
}

int main() {

  //3.2 .7.1 8 .-22.2 - 5 2.04 -abcd 1 -1  ~>
  //3.2 + 7.1 + 8 + (-22.2) + 5 + 2.04 + 1 + (-1) = 3.14
  std::cout << sumNumbersInFile("files/numbers.txt");

  return 0;
}