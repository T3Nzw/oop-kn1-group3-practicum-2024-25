#  Move семантики

## Задача 00

Въвеждаме следните два класа:

```c++
struct A {
  A() { std::cout << "A()\n"; }
  A(int) { std::cout << "A(int)\n"; }
  A(A const&) { std::cout << "A(A const&)\n"; }
  A(A&&) { std::cout << "A(A&&)\n"; }
  A& operator=(A const&) { std::cout << "A& operator=(A const&)\n"; return *this; }
  A& operator=(A&&) { std::cout << "A& operator=(A&& a)\n"; return *this; }
  ~A() { std::cout << "~A()\n"; }
  int x;
};

struct B {
  B() { std::cout << "B()\n"; }
  B(int) { std::cout << "B(int)\n"; }
  B(B const&) { std::cout << "B(B const&)\n"; }
  B& operator=(B const&) { std::cout << "B& operator=(B const&)\n"; }
  ~B() { std::cout << "~B()\n"; }
};
```

Какво ще бъде поведението на следните кодови фрагменти:

0.

```c++
A a;
A a2();
A a3 = A();
A a4 = A(4);
int ax1 = A().x;
int ax2 = a4.x;
A a5 = std::move(A());
A a6 = std::move(a5);
```

1.

```c++
void foo(A a) {}
void bar(A& a) {}
void baz(A const& a) {}
void qux(A&& a) {}
void quux(A const a) {}

foo(A());
bar(A());
baz(A(4));
qux(A());
quux(A());

A a;
foo(a);
bar(a);
baz(a);
qux(a);
quux(a);
```

2.

```c++
class MoveWrapper {
public:
  // останалите методи от голямата шестица, които работят коректно...
  MoveWrapper(MoveWrapper&& other) { move(other); }
  MoveWrapper& operator=(MoveWrapper&& other) {
    if (this != &other) { 
      free();
      move(other); 
    }
  }
private:
  A a;
  A* aptr;

  void free() { delete aptr; }

  void move(MoveWrapper&& other) {
    a = other.a;
    aptr = other.aptr; 
  }
};
```

3.

```c++
A&& foo(A&& a) { return a; }
A&& a2 = foo(A());

B&& bar(B&& b) { return b; }
B&& b2 = bar(B());
```

4.

```c++
A foo(A&& a) { return a; }
A&& a1 = foo(A());

A bar(A a) { return a; }
A a2 = bar(A());

B baz(B&& b) { return b; }
B&& b1 = baz(B());

B qux(B b) { return b; }
B b2 = qux(B());
```

5. 

```c++
A foo(A&& a) { return std::move(a); }
A&& a2 = foo(A());

B bar(B&& b) { return std::move(b); }
B&& b2 = bar(B());
```

6.

```c++
A foo(A a) { return a; }
A bar() { return A(); }
A baz() { A a; return a; }
A qux() { 
  if (1 == 0)
    return A(0);
  else 
    return A(1);
}
A quux(int x, A a1) {
  A a2 = A(2);
  if (x == 1)
    return a1;
  else if (x == 2)
    return a2;
  else 
    return A(3);
}

A a1 = foo(A());
A a2 = bar();
A a3 = baz();
A a4 = qux();
A a5 = quux(1, A(1));
A a6 = quux(2, A(1));
A a7 = quux(3, A(1));
```

## Задача 01

За класовете `Vector` и `unique_ptr` да се напишат подходящи move конструктор и move оператор за присвояване.

*Бонус*: Да се използва `copy-and-swap` идиома за реализацитя на move семантиките.

## Задача 02

Да се напише шаблон на клас `Either`, който позволява даден обект да съдържа точно един от два възможни типа във всеки един момент. Двете възможни стойности ще наричаме лява и дясна стойност (съответно ляв и десен тип). Да се гарантира, че лява стойност **няма** да се инициализира със стойност от десен тип, и обратно. Класът да поддържа следния интерфейс:

- `bool isLeft() const` - връща дали стойността в обекта е от ляв тип;

- `bool isRight() const` - връща дали стойността в обекта е от десен тип;

- `<подходящ_тип> type() const` - връща дали типът на стойността в обекта е ляв или десен;

- `L const& fromLeft() const` - връща лявата стойност, ако именно такава се съдържа в обекта;

- `R const& fromRight() const` - връща дясната стойност, ако именно такава се съдържа в обекта;

- `Either& operator=(<лява_стойност>)` - присвоява някаква лява стойност на обекта;

- `Either& operator=(<дясна_стойност>)` - присвоява някаква дясна стойност на обекта;

- `void either(std::function<L(L)> const& lfunc, std::function<R(R)> const& rfunc)` - прилага правилната функция в зависимост от стойността, която се съдържа в обекта;

- `void swap(Either& other)` - разменя два обекта;

- `friend void swap(Either& lhs, Either& rhs)` - разменя два обекта;

- подходящи методи от **голямата шестица**.
