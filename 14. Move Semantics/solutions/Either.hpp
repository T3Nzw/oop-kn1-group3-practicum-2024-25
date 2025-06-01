#ifndef __EITHER_HPP
#define __EITHER_HPP

#include <stdexcept>
#include <utility>
#include <functional>

class bad_either_access : public std::exception {
public:
  bad_either_access(char const* type)
  : msg("error: either has no active type ") {
    msg += type;
  }
  virtual char const* what() const noexcept override final {
    return msg.c_str(); 
  }
private:
  std::string msg;
};

/*
най-интуитивният и лесен начин да си подсигурим, че ще имаме два различими
конструктора в Either, дори и двата типа L и R да съвпадат, е да имаме две отделни
структури, съответно за ляв и десен тип, и да конструкторите да приемат като параметри
именно такива обекти. за целта можем да използваме ключовата дума explicit в сигнатурите
на конструкторите, за да задължим потребителя експлицитно да напише конструктора на съответната
структура (Left или Right) и да забраним неявното преобразуване на типове, тъй като то отново
би могло да се окаже проблем, ако L==R. това е една примерна имплементация на по-горното:
*/

/*
template<typename T>
class Left {
public:
  explicit Left(T const& value) : value(value) {}
private:
  T value;
};

template<typename T>
class Right {
public:
  explicit Right(T const& value) : value(value) {}
private:
  T value;
};

template<typename L, typename R>
class Either {
  Either(Left<L> const& left) { ... }
  Either(Right<R> const& right) { ... }

private:
  <лява_стойност> lvalue;
  <дясна_стойност> rvalue;
};
*/

/*
въпросът е как ще представяме лявата и дясната стойност - все пак като параметри на
конструкторите подаваме обекти на класове, а не - самите стойности. имаме два варианта:
- вътрешно пазим самите обекти и в съотвените им класове добавяме селектори и мутатори
(или можем да използваме и структура);
- пазим самите стойности, т.е. L lvalue; и R rvalue;, като, отново, можем да направим
класовете структури, а можем и да си дефинираме селектори и да извличаме стойностите
в конструкторите на Either. друг вариант е да предефинираме оператора за преобразуване
на типове в двата класа: operator T() const { ... }, който ще ни позволи да третираме
обектите Left и Right като обекти от съотвения тип, който съдържат
*/

/*
приемаме, че класовете Left и Right имат предефинирани оператора за преобразуване:
operator T() const { return value; }

template<typename L, typename R>
class Either {
public:
  Either(Left<L> const& left) : lvalue(left) {}
  Either(Right<R> const& right) : rvalue(right) {}
private:
  L lvalue;
  R rvalue;
};
*/

/*
тук обаче отново може да достигнем проблем. първо, заделяме памет за два обекта от типове L и R,
което е ненужно, имайки предвид, че във всеки момент от програмата очакваме обект на този клас да
съдържа точно една стойност - съответно лява или дясна. още повече, дори и да извикаме конструктора
на левия тип, трябва да създадем и обект от десния тип. това може да е проблемно, ако за десния тип
няма конструктор по подразбиране, тъй като няма да знаем как да създадем обекта.
единият вариант е да работим с динамично заделяне на памет - т.е. ще имаме два указателя към ляв и
към десен тип и по този начин ще симулираме "лениво" създаване на обектите само при нужда:
*/

/*
template<typename L, typename R>
class Either {
public:
  Either(Left<L> const& left) : lvalue(new L(left)), rvalue(nullptr) {}
  Either(Right<R> const& right) : lvalue(nullptr), rvalue(new R(right)) {}
  // останалите методи от Г6...
private:
  L* lvalue;
  R* rvalue;
};
*/

/*
другият вариант е да използваме обединение (union), за да спестим памет и
за да конструираме обектите от типове L и R лениво. имплементацията може
да видите по-надолу :)
*/


// алтернативна имплементация на описаното по-горе, използваща
// частична специализация на структури/класове и фантомови типове
// (прави абсолютно същото)


// дефинираме две празни структури, понеже искаме само и единствено да използваме типовете им
struct Left {};
struct Right {};

template<typename T, typename Tag>
struct TaggedValue {
  explicit TaggedValue(T const& value)
  : value(value) {}
  
  T value;
  operator T() const { return value; }
};

template<typename T>
using LeftType = TaggedValue<T, Left>;

template<typename T>
using RightType = TaggedValue<T, Right>;

// функции, които играят ролята на конструктори, може и без тях
template<typename T>
inline LeftType<T> Left(T const& value) {
  return LeftType<T>(value);
}

template<typename T>
inline RightType<T> Right(T const& value) {
  return RightType<T>(value);
}

template<typename L, typename R>
class Either {
public:
  // ръчно заделяне на памет, използвайки placement new
  // (НЕ заделя ДИНАМИЧНА памет, но въпреки това след това ние
  // сме длъжни да освободим заделената памет!!!)
  Either(LeftType<L> const& left) : activeType(ValueType::LEFT) {
    new (&m_value) L(left);
  }

  Either(RightType<R> const& right) : activeType(ValueType::RIGHT) {
    new (&m_value) R(right);
  }

  Either(Either const& other) : activeType(other.activeType) {
    switch (activeType) {
      case ValueType::LEFT:
        new (&m_value) L(other.m_value.left);
        break;
      case ValueType::RIGHT:
        new (&m_value) R(other.m_value.right);
        break;
    }
  }

  Either(Either&& other) noexcept : activeType(other.activeType) {
    switch (activeType) {
      case ValueType::LEFT:
        new (&m_value) L(std::move(other.m_value.left));
        break;
      case ValueType::RIGHT:
        new (&m_value) R(std::move(other.m_value.right));
        break;
    }
  }

  // оператори за присвояване, изпозвайки copy-and-swap идиома
  Either& operator=(LeftType<L> const& left) {
    Either(left).swap(*this);
    return *this;
  }

  Either& operator=(RightType<R> const& right) {
    Either(right).swap(*this);
    return *this;
  }

  Either& operator=(Either other) {
    other.swap(*this);
    return *this;
  }

  ~Either() {
    switch (activeType) {
      case ValueType::LEFT:
        m_value.left.~L();
        break;
      case ValueType::RIGHT:
        m_value.right.~R();
        break;
    }
  }

  bool isLeft() const {
    return activeType == ValueType::LEFT;
  }

  bool isRight() const {
    return activeType == ValueType::RIGHT;
  }

  void either(std::function<L(L)> const& leftFunc, std::function<R(R)> const& rightFunc) {
    switch (activeType) {
      case ValueType::LEFT:
        m_value.left = leftFunc(m_value.left);
        break;
      case ValueType::RIGHT:
        m_value.right = rightFunc(m_value.right);
        break;
      default:
        throw std::runtime_error("this should never happen");
    }
  } 

  void swap(Either& other) {
    // Argument-Dependent Lookup (ADL). в случая има смисъл, понеже работим с типове, за които не знаем нищо,
    // т.е. могат да не са примитивни типове, така че искаме да проверим дали съществува
    // user-defined swap метод за тези типове
    using std::swap;

    if (activeType == ValueType::LEFT && other.activeType == ValueType::LEFT) {
      swap(m_value.left, other.m_value.left);  
    }
    else if (activeType == ValueType::LEFT && other.activeType == ValueType::RIGHT) {
      new (&m_value) R(std::move(other.m_value.right));
      new (&other.m_value) L(std::move(m_value.left));

      m_value.left.~L();
      other.m_value.right.~R();
    }
    else if (activeType == ValueType::RIGHT && other.activeType == ValueType::LEFT) {
      new (&m_value) L(std::move(other.m_value.left));
      new (&other.m_value) R(std::move(m_value.right));

      m_value.right.~R();
      other.m_value.left.~L();
    }
    else {
      swap(m_value.right, other.m_value.right);
    }

    swap(activeType, other.activeType);
  }  

  // съответният swap метод, който компилаторът би използвал при размяна на
  // обекти от тип Either посредством ADL
  friend void swap(Either& lhs, Either& rhs) {
    lhs.swap(rhs);
  }

  L const& fromLeft() const {
    if (activeType != ValueType::LEFT) 
      throw bad_either_access("left");
    return m_value.left;
  }

  R const& fromRight() const {
    if (activeType != ValueType::RIGHT)
      throw bad_either_access("right");
    return m_value.right;
  }

private:
  // обединението, коеот съдържа и двата възможни типа.
  // забележете, че тъй като не знаем нищо за L и R,
  // те могат да се окажат нетривиални типове (има дефиницията в cppreference),
  // което би означавало, че трябва експлицитно да "създадем" тези обекти
  // в конструктора на обединението и да освободим паметта за тях в деструктора.
  // тъй като в съответните конструктор и деструктор няма да знаем как да създадем
  // обекти от тези типове в общия случай (може да нямат конструктор по подразбиране),
  // оставяме телата им празни и "външно" (т.е. в конструкторите, операторите за присвояване
  // и деструктора на Either) се грижим за паметта и жизнения цикъл на тези обекти
  union Value {
    L left;
    R right;
    
    Value() {}
    ~Value() {}
  } m_value;


  enum class ValueType {
    LEFT,
    RIGHT,
  } activeType;
};

#endif // __EITHER_HPP 
