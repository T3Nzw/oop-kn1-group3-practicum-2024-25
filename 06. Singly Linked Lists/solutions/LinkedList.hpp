#ifndef __LINKED_LIST_HPP
#define __LINKED_LIST_HPP

#include <stdexcept>
#include <initializer_list>
#include <iostream>

template<typename T>
class LinkedList {
public:
  bool empty() const { return !m_begin; }

  size_t size() const {
    Node* tmp = m_begin;
    size_t cnt = 0;
    while (tmp) {
      cnt++;
      tmp = tmp->next;
    }
    return cnt;
  }

  void push_front(T const& el) {
    Node* node = new Node(el);
    if (!m_begin) {
      m_begin = m_end = node;
      return;
    }

    node->next = m_begin;
    m_begin = node;
  }

  void push_back(T const& el) {
    Node* node = new Node(el);
    if (!m_end) {  // !m_begin
      m_begin = m_end = node;
      return;
    }

    m_end->next = node;
    m_end = node;
  }

  T pop_front() {
    if (!m_begin)
      throw std::runtime_error("empty list");

    T el = m_begin->data;

    Node* save = m_begin->next;
    delete m_begin;
    m_begin = save;

    return el;
  }

  T pop_back() {
    if (!m_end)
      throw std::runtime_error("empty list");

    Node* save = m_begin;
    while (save && save->next && save->next->next) {
      save = save->next;
    }

    T el = m_end->data;

    delete m_end;
    m_end = save;
    m_end->next = nullptr;

    return el;
  }

  void push_at(size_t index, T const& el) {
    if (empty() || index==0) return push_front(el);

    Node* tmp = m_begin;
    while (tmp && --index) {
      tmp = tmp->next;
    }

    if (!tmp)
      throw std::runtime_error("invalid index");

    tmp->next = new Node(el,tmp->next);

    if (tmp==m_end)
      m_end = m_end->next;
  }

  T pop_at(size_t index) {
    if (index==0) return pop_front();

    Node* tmp = m_begin;
    while (tmp && --index) {
      tmp = tmp->next;
    }

    if (!tmp || !tmp->next)
      throw std::runtime_error("invalid index");

    if (tmp->next==m_end)
      m_end = tmp;

    T el = tmp->next->data;

    Node* save = tmp->next->next;
    delete tmp->next;
    tmp->next = save;

    return el;
  }

  T& at(size_t index) {
    Node* tmp = m_begin;
    while (tmp && index--) {
      tmp = tmp->next;
    }

    if (!tmp)
      throw std::runtime_error("invalid index");

    return tmp->data;
  }

  T const& at(size_t index) const {
    Node* tmp = m_begin;
    while (tmp && index--) {
      tmp = tmp->next;
    }

    if (!tmp)
      throw std::runtime_error("invalid index");

    return tmp->data; 
  }

  void reverse() {
    if (empty()) return;

    Node *prev = nullptr, *cur = m_begin, *next;
    while (cur) {
      next = cur->next;
      cur->next = prev;
      prev = cur;
      cur = next;
    }

    m_begin = prev;
  }

  void print() const {
    Node* tmp = m_begin;
    while (tmp) {
      std::cout << tmp->data << ' ';
      tmp = tmp->next;
    }
    std::cout << '\n';
  }

public:
  LinkedList() : m_begin(nullptr), m_end(nullptr) {}

  LinkedList(LinkedList const& other) {
    copy(other);
  }

  LinkedList& operator=(LinkedList const& other) {
    if (this != &other) {
      free();
      copy(other);
    }
    return *this;
  }

  ~LinkedList() { free(); }

private:
  void copy(LinkedList const& other) {
    Node dummy;
    Node* dptr = &dummy;
    Node* tmp = other.m_begin;

    while (tmp) {
      dptr->next = new Node(tmp->data);
      dptr = dptr->next;
      tmp = tmp->next;
    }
    
    m_begin = dummy.next;
  }

  void free() {
    Node* tmp = m_begin;
    while (m_begin) {
      m_begin = m_begin->next;
      delete tmp;
      tmp = m_begin;
    }
  }

private:
  struct Node {
    T data;
    Node* next;
    Node(T const& data=T(), Node* next=nullptr)
    : data(data), next(next) {}
  };

private:
  Node* m_begin;
  Node* m_end;
};

#endif // __LINKED_LIST_HPP