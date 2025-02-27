# Шаблони (Templates)

```
template<{<шаблонен_параметър>}+>
```

където шаблонните параметри могат да бъдат имена на типове:

```
template<typename T, typename U>
```

или стойности от някакъв тип:

```
template<bool B, int N, double M>
```

или и двете заедно:

```
template<typename T, T a>
```

---

- шаблони на променливи

```c++
template<typename T>
constexpr T PI{3.14159265358979323846};

std::cout << PI<char>  << ' '
          << PI<int>   << ' ' 
          << PI<float> << ' '
          << PI<double>;
```

- шаблони на функции

```c++
template<typename T>
void print(T const& a) {
  std::cout << a;
}

print('a');         //print<char>('a');
print(5.2);         //print<double>(5.2);
print("a string");  //print<char const*>("a string");
//+ всякакви други обекти, 
//за които е дефиниран оператор<<
```

```c++
template<typename T>
int compare(T const& left, T const& right) {
  if (left==right)     return  0;
  else if (left<right) return -1;
  else                 return  1;
}

compare(1,2);
compare('t','s');
compare("a","a");  //грешка, операторите ==,<,>
                   //не са дефинирани за низове
```

```c++
template<typename T, size_t const SIZE>
//подаване на масив по референция
void print(T (&arr)[SIZE]) {
  for (size_t i = 0; i < SIZE; ++i)
    std::cout << arr[i] << ' ';
}

int arr[]{1,2,3,4,5,6,7,8,9,10};
print(arr);  //print<int,10>(arr);
```

- шаблони на структури/класове

```c++
template<typename T>
struct ResizingArray {
  T* data;
  size_t size;
  size_t capacity;
};

struct Point { double x, y; }

ResizingArray<int> arr{new int[10],0,10};
ResizingArray<Point> arr{new Point[4],0,4};
```

- (пълна) специализация на функции

```c++
template<typename T>
bool isIntType(T const& el) {
  std::cout << "not an int type";
}

template<>
bool isIntType<int> (int const& el) {
  std::cout << "int type";
}
```