#include <iostream>
#include <fstream>
#include <cstring>

unsigned short const MAX_SIZE = 32;
unsigned short const FN_MAX_SIZE = 11;

struct Student {
  char firstName[MAX_SIZE];
  char lastName[MAX_SIZE];
  char major[MAX_SIZE];
  char fn[FN_MAX_SIZE];
  unsigned short year;
  unsigned short group;
};

enum class Error {
  NONE,
  FILE_NOT_OPEN,
  STUDENT_ALREADY_EXISTS,
  STUDENT_DOES_NOT_EXIST
};

bool areTheSameStudent(Student const& s1, Student const& s2) {
  return !strcmp(s1.fn,s2.fn);
}

Error addStudent(char const* filename, Student const& student) {
  std::ifstream ifile(filename,std::ios::in|std::ios::binary);
  Student s;
  while (ifile.read((char*)&s,sizeof(Student))) {
    if (areTheSameStudent(student,s)) {
      return Error::STUDENT_ALREADY_EXISTS;
    }
  }
  ifile.close();  //!!!

  std::ofstream ofile(filename,std::ios::out|std::ios::binary|std::ios::app);
  if (!ofile) {
    return Error::FILE_NOT_OPEN;
  }

  ofile.write((char const*)&student,sizeof(Student));

  ofile.close();
  return Error::NONE;
}

Error incrementYear(char const* filename, char const* fn) {
  std::ifstream ifile(filename,std::ios::in|std::ios::binary);
  if (!ifile) return Error::FILE_NOT_OPEN;

  Student s;
  size_t sIdx = 0;
  while (ifile.read((char*)&s,sizeof(Student)) && strcmp(fn,s.fn)) {
    sIdx++;
  }
  if (ifile.eof()) return Error::STUDENT_DOES_NOT_EXIST;
  ifile.close();

  std::ofstream ofile(filename,std::ios::out|std::ios::in|std::ios::binary);
  if (!ofile) return Error::FILE_NOT_OPEN;

  ofile.seekp(sizeof(Student)*sIdx + offsetof(Student,year));
  s.year = s.year >= 4 ? 4 : s.year+1;
  ofile.write((char const*)&s.year,sizeof(s.year));

  ofile.close();
  return Error::NONE;
}

bool areColleagues(Student const& s1, Student const& s2) {
  return !strcmp(s1.major,s2.major) &&
         s1.year  == s2.year        &&
         s1.group == s2.group;
}

char const* const* colleaguesOf(char const* filename, char const* fn, Error& err, size_t& totalStudents) {
  std::ifstream ifile(filename,std::ios::in|std::ios::binary);
  if (!ifile) {
    std::cerr << "could not open file";
    return nullptr;
  }

  ifile.seekg(0,std::ios::end);
  totalStudents = ifile.tellg()/sizeof(Student);
  char** fns = new char*[totalStudents]{};
  
  Student s{};
  bool found = false;
  
  ifile.seekg(0);
  while (ifile.read((char*)&s,sizeof(Student))) {
    if (!strcmp(s.fn,fn)) {
      found = true;
      break;
    }
  }

  if (!found) {
    err = Error::STUDENT_DOES_NOT_EXIST;
    return nullptr;
  }
  
  ifile.seekg(0);
  
  Student buf;
  size_t index = 0;
  while (ifile.read((char*)&buf,sizeof(Student))) {
    if (!strcmp(s.fn,buf.fn)) continue;

    if (areColleagues(s,buf)) {
      fns[index] = new char[FN_MAX_SIZE];
      strcpy(fns[index],buf.fn);
      index++;
    }
  }

  return fns;
}

void print(Student const& s) {
  std::cout << "First name: "     << s.firstName << std::endl;
  std::cout << "Last name: "      << s.lastName  << std::endl;
  std::cout << "Major: "          << s.major     << std::endl;
  std::cout << "Year: "           << s.year      << std::endl;
  std::cout << "Group: "          << s.group     << std::endl;
  std::cout << "Faculty number: " << s.fn        << std::endl;
}

Error printContents(char const* filename) {
  std::ifstream ifile(filename,std::ios::in|std::ios::binary);
  if (!ifile) return Error::FILE_NOT_OPEN;

  Student s;
  while (ifile.read((char*)&s,sizeof(Student))) {
    print(s);
    std::cout << std::endl;
  }

  ifile.close();
  return Error::NONE;
}

int main() {

  char const* filename = "files/students.bin";
  addStudent(filename, {"firstname","lastname","cs","12345",1,3});
  addStudent(filename, {"firstname2","lastname2","cs","12346",1,3});
  addStudent(filename, {"firstname3","lastname3","cs","12347",1,3});
  
  incrementYear(filename,"12345");
  incrementYear(filename,"12346");
  incrementYear(filename,"12347");

  printContents(filename);

  Error err;
  size_t totalStudents = 0;
  char const* const* colleagues = colleaguesOf(filename,"12345",err,totalStudents);
  if (!colleagues) {
    std::cout << "no colleagues\n";
  }
  else {
    for (size_t i = 0; i < totalStudents && colleagues[i]; ++i) {
      std::cout << "Colleague " << i+1 << ": ";
      std::cout << colleagues[i] << '\n';
    }
  }
  
  for (size_t i = 0; i < totalStudents; i++) {
    delete[] colleagues[i];
  }
  delete[] colleagues;

  return 0;
}