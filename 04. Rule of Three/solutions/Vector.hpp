#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class Vector {
private:
  /*
   *  една възможна имплементация за итератор,
   *  който може да бъде const или non-const
   *  в зависимост от типовия параметър elRef,
   *  а именно T const& за const и T& - иначе.
   *  доц. д-р Калин Георгиев също има подобна
   *  имплементация в GitHub, която обаче използва
   *  elRef=T за const итератора и е trade-off
   *  на памет и допълнително копиране за ГОЛЕМИ обекти
   *  (реално итераторът би могъл да бъде даже по-бърз
   *  и от elRef=T const& за малки типове като int, char, ...).
   *  в STL се използва друг подход,
   *  който обаче е една идея по-сложен
   *  концептуално :)
   */
  template <typename elRef> 
  class Iterator {
  public:
    Iterator(T *it) : m_it(it) {}

    Iterator &operator++() {
      if (m_it)
        m_it++;
      return *this;
    }

    /*
     *  забележете, че нямаме нужда от два различни
     *  const-overloaded метода (спомнете си, че бяхме
     *  написали два метода - T& operator*()
     *  и T const& operator*() const,
     *  където извикването на правилния метод
     *  се определяше от това, дали контекстът,
     *  в който извиквахме този метод, би довел до
     *  промяна на стойността вътре в итератора, или не).
     *  тук няма нужда да правим това (а и би било семантично
     *  грешно да го правим), тъй като, ако elRef=T&, то методът
     *  има вида: T& operator*() const, но знаем, че ние можем да
     *  променяме стойността в m_it, тъй като const-qualifier-ът
     *  се отнася за самия указател m_it, а не - това, към което сочи.
     *  обратно, ако elRef=T const&, то методът ще има сигнатурата
     *  T const& operator*() const и няма да можем да променяме
     *  стойността на това в указателя, което и искаме
     */
    elRef operator*() const { return *m_it; }

    bool operator==(Iterator const &other) const { return m_it == other.m_it; }

    bool operator!=(Iterator const &other) const { return !(*this == other); }

    T *ptr() const { return m_it; }

  private:
    T *m_it;
  };

  template <typename elRef> 
  class ReverseIterator {
  public:
    ReverseIterator(T *it) : m_it(it) {}

    ReverseIterator &operator++() {
      if (m_it)
        m_it--;
      return *this;
    }

    elRef operator*() const { return *m_it; }

    bool operator==(ReverseIterator const &other) const {
      return m_it == other.m_it;
    }

    bool operator!=(ReverseIterator const &other) const {
      return !(*this == other);
    }

    T *ptr() const { return m_it; }

  private:
    T *m_it;
  };

public:
  using iterator = Iterator<T&>;
  using const_iterator = Iterator<T const&>;
  using reverse_iterator = ReverseIterator<T&>;
  using const_reverse_iterator = ReverseIterator<T const&>;

  iterator begin() { return iterator(m_data); }
  iterator end() { return iterator(m_data ? m_data + m_size : nullptr); }

  const_iterator cbegin() const { return const_iterator(m_data); }
  const_iterator cend() const {
    return const_iterator(m_data ? m_data + m_size : nullptr);
  }

  reverse_iterator rbegin() {
    return reverse_iterator(m_data ? m_data + m_size - 1 : nullptr);
  }
  reverse_iterator rend() {
    return reverse_iterator(m_data ? m_data - 1 : nullptr);
  }

  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(m_size ? m_data + m_size - 1 : nullptr);
  }
  const_reverse_iterator crend() const {
    return const_reverse_iterator(m_size ? m_data - 1 : nullptr);
  }

  bool empty() const { return m_size == 0; }

  size_t size() const { return m_size; }
  size_t capacity() const { return m_capacity; }

  void reserve(size_t capacity) {
    if (capacity <= m_capacity)
      return;

    T *newData = new T[capacity];
    for (size_t i = 0; i < m_size; ++i) {
      newData[i] = m_data[i];
    }
    delete[] m_data;
    m_data = newData;
    m_capacity = capacity;
  }

  void push_back(T const &el) {
    if (m_size >= m_capacity) {
      reserve(m_capacity > 0 ? m_capacity * 2 : 1);
    }

    m_data[m_size++] = el;
  }

  T pop_back() {
    if (empty())
      throw std::runtime_error("vector is empty");

    return m_data[--m_size];
  }

  void insert(size_t index, T const &el) {
    if (index > m_size)
      throw std::out_of_range("invalid index");

    if (m_size >= m_capacity) {
      reserve(m_capacity > 0 ? m_capacity * 2 : 1);
    }

    shiftRight(index);
    m_size++;
    m_data[index] = el;
  }

  void remove(size_t index) {
    if (index >= m_size)
      throw std::out_of_range("invalid index");

    shiftLeft(index);
    m_size--;
  }

  template <typename elRef> 
  void remove(Iterator<elRef> it) {
    remove(it.ptr() - m_data);
  }

  template <typename elRef> 
  void remove(ReverseIterator<elRef> it) {
    remove(it.ptr() - m_data);
  }

  T &at(size_t index) {
    if (index >= m_size)
      throw std::out_of_range("invalid index");

    return m_data[index];
  }

  T const &at(size_t index) const {
    if (index >= m_size)
      throw std::out_of_range("invalid index");

    return m_data[index];
  }

  T &operator[](size_t index) { return at(index); }

  T const &operator[](size_t index) const { return at(index); }

  void clear() { m_size = 0; }

  void swap(Vector &other) {
    std::swap(m_data, other.m_data);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
  }

  bool contains(T const &el) const {
    for (size_t i = 0; i < m_size; ++i)
      if (m_data[i] == el)
        return true;
    return false;
  }

public:
  Vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

  Vector(size_t capacity, T const &initEl = T())
      : m_data(new T[capacity]), m_size(capacity), m_capacity(capacity) {
    for (size_t i = 0; i < m_size; ++i)
      m_data[i] = initEl;
  }

  Vector(std::initializer_list<T> const &l)
      : m_data(new T[l.size()]), m_size(l.size()), m_capacity(l.size()) {
    size_t i = 0;
    auto it = l.begin();
    for (; it != l.end(); ++i, ++it)
      m_data[i] = *it;
  }

  Vector(Vector const &other)
      : m_data(new T[other.m_size]), m_size(other.m_size),
        m_capacity(other.m_size) {
    for (size_t i = 0; i < m_size; ++i)
      m_data[i] = other.m_data[i];
  }

  Vector(Vector&& other) {
    move(std::move(other));
  }

  /*
  Vector& operator=(Vector const &other) {
    if (this != &other) {
      free();
      copy(other);
    }
    return *this;
  }

  Vector& operator=(Vector&& other) {
    if (this != &other) {
      free();
      move(std::move(other));
    }
    return *this;
  }
  */

  // copy-and-swap idiom
  Vector& operator=(Vector other) {
    other.swap(*this);
    return *this;
  }

  ~Vector() { free(); }

private:
  void copy(Vector const &other) {
    m_data = new T[other.m_size];
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    for (size_t i = 0; i < m_size; ++i)
      m_data[i] = other.m_data[i];
  }

  void move(Vector&& other) {
    m_data = other.m_data;
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    other.m_data = nullptr;
    other.m_size = other.m_capacity = 0;
  }

  void free() { delete[] m_data; }

  void shiftLeft(size_t index) {
    for (size_t i = index; i < m_size - 1; ++i)
      m_data[i] = m_data[i + 1];
  }

  // тук предполагаме, че ще има достатъчно място в масива!
  void shiftRight(size_t index) {
    for (size_t i = m_size; i >= index + 1; --i) {
      m_data[i] = m_data[i - 1];
    }
  }

private:
  T *m_data;
  size_t m_size;
  size_t m_capacity;
};

#endif // __VECTOR_HPP
