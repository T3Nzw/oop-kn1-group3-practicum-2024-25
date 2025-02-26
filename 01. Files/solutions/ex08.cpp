#include <iostream>
#include <fstream>

bool isEndOfSentence(char c) {
  return c=='.' || c=='?' || c=='!';
}

bool isInterval(char c) {
  return c==' ' || c=='\t';
}

bool isPunctuationMark(char c) {
  return c=='.' || c=='?' || c=='!' ||
         c==',' ||  c==';' || c==':';
}

bool invalid(char c) {
  return isInterval(c) || isPunctuationMark(c);
}

void edit(std::ifstream& ifile, std::ofstream& ofile) {
  ifile.seekg(0);
  ofile.seekp(0);

  char prev = ifile.get(), next;
  
//trim whitespaces to the left
  while (isInterval(prev))
   ifile.get(prev);
  
  if (ifile.eof()) return;
  else if (isalpha(prev)) prev = toupper(prev);

  bool endOfSentence = false;
  while (ifile.get(next)) {

  //skip all >=2 intervals
    if (isInterval(prev) && isInterval(next)) {
      while (ifile.get(next) && isInterval(next)) {}
    }

    //if the next character is a punctuation mark,
    //skip the only left interval
    if (isInterval(prev) && isPunctuationMark(next)) {}
    else {
      if (endOfSentence && isalpha(prev)) {
        endOfSentence = false;
        prev = toupper(prev);
      }
      ofile.put(prev);
    }
    
    if (isPunctuationMark(prev) && !isInterval(next)) {
      ofile.put(' ');
    }

    if (isEndOfSentence(prev))
      endOfSentence = true;

    prev = next;
  }

  if (!isInterval(next)) ofile.put(next);
}


void align(std::ifstream& ifile, std::ofstream& ofile, size_t alignment) {
  char* buffer = new char[alignment+1];

  ifile.seekg(0);
  ofile.seekp(0);

  while(ifile.get(buffer,alignment+1,'\n')) {
    ofile << buffer << std::endl;
    if (ifile.peek()=='\n') ifile.get();
  }

  ofile << buffer;

  delete[] buffer;
}

void format(char const* file, char const* target, size_t alignment) {
  std::ifstream ifile(file);
  std::ofstream ofile(target);

  if (!ifile || !ofile) {
    std::cerr << "could not open file";
    return;
  }

  edit(ifile,ofile);
  ifile.close(); ofile.close();

  std::ifstream ifile2(target);
  std::ofstream ofile2(file);

  if (!ifile2 || !ofile2) {
    std::cerr << "could not open file";
    return;
  }

  align(ifile2,ofile2,alignment);
  ifile2.close(); ofile2.close();
}

int main() {

//original string in file:
/*
                this was an unformatted version of the file in exercise 08.it was used in order to illustrate the formatting and        alignment of a file              .
*/
  format("files/formatted.txt","files/format-helper.txt",20);

  return 0;
}