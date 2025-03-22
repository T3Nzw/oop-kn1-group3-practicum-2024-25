#include "String.hpp"
#include <cstring>
#include <iostream> //!!!
#include <stdexcept>

void String::push_back(char c) {
  if (m_size+1>=m_capacity)
    reserve(m_capacity*2);

  m_data[m_size++] = c;
  m_data[m_size] = '\0';
}

bool String::pop_back() {
  if (empty())
    return false;

  m_data[--m_size] = '\0';
  return true;
}

long long String::find(char c) const {
  for (size_t i = 0; i < m_size; ++i)
    if (m_data[i]==c)
      return i;

  return -1;
}

long long String::find(String const& substr) const {
  char* s = strstr(m_data,substr.m_data);
  if (!s)
    return -1;

  return s-m_data;
}

String String::slice(size_t left, size_t right) const {
  String s;
  if (left>=m_size)
    return s;

  for (size_t i = left; i<m_size && i<right; ++i) {
    s.push_back(m_data[i]);
  }
  m_data[m_size] = '\0';

  return s;
}

void String::reverse() {
  size_t mid = m_size/2;
  for (size_t i = 0; i < mid; ++i)
    std::swap(m_data[i],m_data[m_size-1-i]);
}

void String::copy(String const& other) {
  m_data = new char[other.m_size+1];
  m_size = other.m_size;
  m_capacity = other.m_size+1;
  strcpy(m_data,other.m_data);
}

void String::reserve(size_t capacity) {
  if (capacity<=m_capacity) return;

  char* newData = new char[capacity];
  strcpy(newData,m_data);
  delete[] m_data;
  m_data = newData;
  m_capacity = capacity;
}

void String::erase(size_t index, size_t length) {
  if (index>=m_size) return;

  String s;
  s.reserve(m_size-length+1);
  for (size_t i = 0; i < index; ++i) {
    s.push_back(m_data[i]);
  }
  for (size_t i = index+length; i < m_size; ++i) {
    s.push_back(m_data[i]);
  }
  *this = s;
}

void String::swap(String& other) {
  std::swap(m_data,other.m_data);
  std::swap(m_size,other.m_size);
  std::swap(m_capacity,other.m_capacity);
}

String& String::replace(char const* oldS, char const* newS) {
  String s;
  size_t read = 0;
  size_t oldLength = strlen(oldS);
  while (read<m_size) {
    if (!strncmp(m_data+read,oldS,oldLength)) {
      read+=oldLength;
      s+=newS;
    }
    else {
      s.push_back(m_data[read++]);
    }
  }
  *this = s;
  return *this;
}

String& String::replace(String const& oldS, String const& newS) {
  replace(oldS.m_data,newS.m_data);
  return *this;
}

String String::operator+(char const* s) {
  String res(*this);
  while (*s)
    res.push_back(*s);
  return res;
}

String String::operator+(String const& other) {
  return *this + other.m_data;
}

String operator+(char const* s, String const& other) {
  String res(s);
  res += other;
  return res;
}

String& String::operator+=(char const* s) {
  while (*s) 
    push_back(*s++);
  return *this;
}

String& String::operator+=(String const& other) {
  // operator+=(other.m_data);
  *this += other.m_data;
  return *this;
}

char& String::operator[](size_t index) {
  if (index>=m_size)
    throw std::out_of_range("invalid index");

  return m_data[index];
}

char String::operator[](size_t index) const {
  if (index>=m_size)
    throw std::out_of_range("invalid index");

  return m_data[index];
}

bool String::operator==(String const& other) const {
  return strcmp(m_data,other.m_data) == 0;
}

bool String::operator<(String const& other) const {
  return strcmp(m_data,other.m_data) < 0;
}

bool String::operator>(String const& other) const {
  return strcmp(m_data,other.m_data) > 0;
}

bool String::operator<=(String const& other) const {
  return *this == other || *this < other;
}

bool String::operator>=(String const& other) const {
  return *this == other || *this > other;
} 

std::ostream& operator<<(std::ostream& os, String const& s) {
  os << s.m_data;
  return os;
}

std::istream& operator>>(std::istream& is, String& s) {
  is >> s;
  return is;
}

String::String()
: m_data(new char[1]{""}), m_size(0), m_capacity(1) {}

String::String(char const* s) {
  m_size = strlen(s);
  m_capacity = m_size+1;
  m_data = new char[m_capacity];
  strcpy(m_data,s);
}

String::String(String const& other)
: m_data(new char[other.m_size+1]), 
m_size(other.m_size), m_capacity(other.m_size+1) {
  strcpy(m_data,other.m_data);
}

String& String::operator=(String const& other) {
  if (this != &other) {
    free();
    copy(other);
  }
  return *this;
}

String::~String() { free(); }