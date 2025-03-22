#ifndef __STRING_HPP
#define __STRING_HPP

#include <cstddef>
#include <iosfwd>

class String {
public:
  bool empty() const { return m_size==0; }
  size_t size() const { return m_size; }
  size_t capacity() const { return m_capacity; }

  void push_back(char c);
  bool pop_back();

  long long find(char c) const;
  long long find(String const& substr) const;

  String slice(size_t left, size_t right) const;

  void clear() { String().swap(*this); }
  void reverse();
  
  void copy(String const& other);
  void reserve(size_t capacity);

  void erase(size_t index, size_t length=1);

  void swap(String& other);

  char const* c_str() const { return m_data; }
  char* data() { return m_data; }

  String& replace(char const* oldS, char const* newS);
  String& replace(String const& oldS, String const& newS);

  String operator+(char const* s);
  String operator+(String const& other);

  friend String operator+(char const* s, String const& other);

  String& operator+=(char const* s);
  String& operator+=(String const& other);

  char& operator[](size_t index);
  char operator[](size_t index) const;

  bool operator==(String const& other) const;
  bool operator<(String const& other) const;
  bool operator>(String const& other) const;
  bool operator<=(String const& other) const;
  bool operator>=(String const& other) const;

  friend std::ostream& operator<<(std::ostream& os, String const& s);
  friend std::istream& operator>>(std::istream& is, String& s);

public: 
  String();
  String(char const*);
  String(String const&);
  String& operator=(String const&);
  ~String();

private:
  void free() { delete[] m_data; }

private:
  char* m_data;
  size_t m_size;
  size_t m_capacity;
};

#endif // __STRING_HPP