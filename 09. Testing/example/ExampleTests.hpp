#ifndef __EXAMPLE_TESTS_HPP
#define __EXAMPLE_TESTS_HPP

#include "../../libs/doctest.h"
//тъй като дефинициите на методите на String са в
//String.cpp файла (в същата директория като String.hpp),
//трябва да компилираме и него.
#include "../../04. Rule of Three/solutions/String.hpp"

TEST_CASE("Тест, който минава успешно") {
  CHECK(2*4+3-2==9);
}

TEST_CASE("Тест, който се проваля") {
  CHECK(1==0);
}

TEST_CASE("Тест с няколко различни подтеста") {
  SUBCASE("Подтест 1, който сравнява два низа") {
    String s("Hello, ");
    s += "world";
    CHECK_EQ(s,"Hello, world");
  }

  String s;
  s += "this is a string";

  SUBCASE("Подтест 2, който мутира външен низ ЛОКАЛНО") {
    s.clear();
    CHECK(s.empty());
  }

  SUBCASE("Подтест 3, който проверява дали низът s e празен") {
    CHECK(!s.empty());
  }

  SUBCASE("Подтест 4, който достъпва елемент от низ на невалиден индекс") {
    String s("abc");
    CHECK_THROWS(s[4]);
  }
}

#endif // __EXAMPLE_TESTS_HPP