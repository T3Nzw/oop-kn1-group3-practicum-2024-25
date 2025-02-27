# Функции от по-висок ред (Higher Order Functions)

- функционални указатели

```
<тип_на_връщан_резултат>(*<идентификатор>)({<формални_параметри>})
```

*Забележка*: Подаването на `void` като функционален параметър е същото като да не подадем никакви параметри.

```c++
void print() { std::cout << "This is a void function that takes no arguments!"; }
double mult(double x, double y) { return x*y; }
template<typename T>
void push_back(ResizingArray<T>& arr, T const& el) { /*code goes here*/ }

void(*f1)() = &print;
double(*f2)(double,double) = &mult;
template<typename T> void(*f3)(ResizingArray<T>&,T const&) = &push_back;

f1(); // print();
f2(4.5,2);  // mult(4.5,2);
ResizingArray<int> arr{new int[2]{1,2},2,2};
f3(arr,3);  // push_back(arr,3);
```

- (имплицитно) преобразуване на функции до функционални указатели и обратно

```c++
void print() { std::cout << "Hello, world!"; }
int main() {
  print();  //функция
  (&print)();  //функционален указател към print,
               //дереференцира се на ниско ниво от компилатора

  void(*f1)() = &print;  //копиране на функционален указател
  void(*f2)() = print;  //имплицитно преобразуване до функционален указател

  f1();  //имплицитно преобразуване до функция
  (*f1)();  //дереференциране на функционалния указател
  f2();
  (*f2)();
}
```

- предефиниране на типове

```c++
typedef int(*BinaryIntOp)(int,int);
using BinaryIntOperation = int(*)(int,int);
//typedef не може да се използва с шаблони
template<typename T> using BinaryOperation = T(*)(T,T);

BinaryIntOp op1 = &add;
BinaryIntOperation op2 = &add;
BinaryOperation op3 = &add;
BinaryOperation<int> op4 = &add;
```

- подаване на функция като параметър

```c++
template<typename T>
using BinaryFunction = T(*)(T,T);

template<typename T>
T apply1(BinaryFunction f, T x, T y) {
  return f(x,y);
}

template<typename T>
T apply2(T(*f)(T,T), T x, T y) {
  return f(x,y);
}
```

- връщане на функция като резултат от изпълнението на функция

```c++
using UnaryFunction = int(*)(int);
int addOne(int x) { return x+1; }

UnaryFunction faddOne1() {
  return &addOne;
//return [](int) -> int { return x+1; };
}
int (*faddOne2(void))(int) {
  return &addOne;
//return [](int) -> int { return x+1; };
}

//НЕ можем да напишем директно
int(*)(int) faddOne3() { return &addOne; }
```

- ламбда изрази (анонимни функции)

```
[{<capture_клаузи>}]({<формални_параметри>}) -> {<тип_на_резултат>} {<тяло>}
```

```c++
//преобразуване до функционален указател
int(*addOne)(int) = [](int x) -> int { return x+1; }
int y = addOne(4);  //5

void(*print)(char const*) = [](char const* s) { std::cout << s; }
print("Hello, world!");
```

*Забележка*: При наличие на capture клаузи е невъзможно преобразуването до функционален указател. За целта се използва класът `std::function`.

- `std::function` (дефиниран във `<functional>`)

```
std::function< <тип_на _функция> >
```

```c++
std::function<void(void)> print
  = []() { std::cout << "Hello, world!"; };
print();

int x = 10, y = 12;

std::function<int()> add
//capture-ва всички променливи в текущата област по стойност
  = [=]() { return x+y; };
add();

std::function<void()> modify
//capture-ва всички променливи по референция
  = [&]() { x = 20; };
modify();

std::function<int(int)> addParam
//capture-ва x по стойност, а y е параметър
  = [x](int y) { return x+y; };
addParam(3);

std::function<void()> condModify
//capture-ва x по референция и y по стойност
  = [&x,y]() {
    if (x==20) {
      x = 10;  //променя x
      y = 15;  //не променя y
    }
  };
condModify();
```

- *(допълнително)* функционални указатели към член-функции на структури/класове. Нека като пример използваме следния клас:

```c++
class Foo {
public:
  void bar() { std::cout << "Foo::bar() called\n"; }
private:
  void qux() { std::cout << "Foo::qux() called\n"; }
};
```

```c++
void(Foo::*f)() = &Foo::bar;
void(Foo::*g)() = &Foo::qux;  //грешка - qux e private

Foo foo;
//първо се дереференцира функционалният указател f,
//тъй като унарният оператор* е с по-висок приоритет 
(foo.*f)();  //Foo::bar() called
Foo* foo2 = &foo;
(foo->*f)();  //Foo::bar() called
```