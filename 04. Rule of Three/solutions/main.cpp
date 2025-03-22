#include <iostream>
#include "Vector.hpp"
#include "String.hpp"

template<typename T>
void print(Vector<T> const& vec) {
  for (size_t i = 0; i < vec.size(); ++i)
    std::cout << vec[i] << ' ';
  std::cout << '\n';
}

int main() {

  String s1;
  String s2("Hello, world");
  std::cout << s2.find(',') << '\n';
  s2.push_back('!');
  s2.push_back('!');
  std::cout << s2.c_str() << '\n'; 

  s2.pop_back();
  std::cout << s2.c_str() << '\n'; 

  s1 = s2;
  std::cout << s1.data() << '\n';

  s1.clear();
  std::cout << s1.data() << '\n';

  std::cout << s2.slice(0,5).c_str() << '\n';

  s2.erase(0,7);
  std::cout << s2.c_str() << '\n'; 

  String s3 = "the " + s2.slice(0,s2.size()-1);
  std::cout << s3.c_str() << '\n';
  std::cout << s3 << '\n';
  std::cout << s3.size() << '\n';

  s3.reverse();
  std::cout << s3 << '\n';
  s3.reverse();
  std::cout << s3 << '\n';

  s3 += " is going crazy";

  s3 = s3.slice(s3.find("crazy"),s3.size());
  std::cout << s3 << '\n';

  std::cout << s3.size() << ' ' << s3.capacity() << '\n';

  s3 += "? i was crazy once";
  std::cout << s3 << '\n';

  s3.replace("crazy","definitely not crazy");
  std::cout << s3 << '\n';

  s3[s3.find('?')] = '!';
  std::cout << s3 << '\n';

  std::cout << s3.find("craazy") << '\n';

  Vector<int> v1;
  Vector<int> v2{1,2,3,4,5};

  print(v1);
  print(v2);

  try {
    std::cout << v1.pop_back() << '\n';
  }
  catch (std::exception const& e) {
    std::cout << e.what() << '\n';
  }

  std::cout << v2.size() << '\n';
  v2.reserve(4);
  std::cout << v2.size() << '\n';

  for (int i = 6; i <= 10; ++i)
    v2.push_back(i);

  print(v2);

  v1 = v2;
  std::cout << v1.pop_back() << '\n';
  print(v1);

  v1.insert(v1.size(),10);
  print(v1);
  std::cout << v1[v1.size()-1] << '\n';

  v1.insert(0,0);
  v1.insert(4,4);
  print(v1);

  v1.remove(4);
  print(v1);

  v2 = v1;

  v1.clear();
  std::cout << v1.empty() << '\n';

  v1.push_back(1);
  v1.push_back(3);
  v1.push_back(5);
  print(v1);

  std::cout << v1.contains(3) << '\n';
  std::cout << v1.contains(4) << '\n';

  v2.remove(0);
  print(v2);

  v1.swap(v2);

  print(v1);
  print(v2);

  Vector<int> v3(v2);
  print(v3);

  Vector<int> v4(10);
  print(v4);

  v4 = Vector(5,3);
  print(v4);

  return 0;
}