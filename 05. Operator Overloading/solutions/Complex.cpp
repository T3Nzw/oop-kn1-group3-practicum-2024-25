#include "Complex.hpp"
#include <iostream>
#include <cmath>

Complex Complex::operator-() const {
  return Complex(-real,-imaginary);
}

Complex Complex::operator+(Complex const& other) const {
  return Complex(real+other.real,imaginary+other.imaginary);
}

Complex Complex::operator-(Complex const& other) const {
  return Complex(real-other.real,imaginary-other.imaginary);
}

Complex Complex::operator*(Complex const& other) const {
  return Complex(real*other.real,imaginary*other.imaginary);
}

Complex& Complex::operator+=(Complex const& other) {
  real += other.real;
  imaginary += other.imaginary;
  return *this;
}

Complex& Complex::operator-=(Complex const& other) {
  real -= other.real;
  imaginary -= other.imaginary;
  return *this;
}

Complex& Complex::operator*=(Complex const& other) {
  real *= other.real;
  imaginary *= other.imaginary;
  return *this;
}

Complex Complex::operator*(double scalar) const {
  return Complex(scalar*real,scalar*imaginary);
}

Complex& Complex::operator*=(double scalar) {
  real *= scalar;
  imaginary *= scalar;
  return *this;
}

Complex operator*(double scalar, Complex const& c) {
  return Complex(scalar*c.real,scalar*c.imaginary);
}

Complex& Complex::operator++() {
  ++real;
  return *this;
}

Complex Complex::operator++(int) {
  Complex c = *this;
  ++real;
  return c;
}

std::ostream& operator<<(std::ostream& os, Complex const& c) {
  os << c.real << (c.imaginary>0 ? "+" : "") << c.imaginary << "i";
  return os;
}

std::istream& operator>>(std::istream& is, Complex& c) {
  is >> c.real >> c.imaginary;
  return is;
}

Complex Complex::conjugate() const {
  return Complex(real,-imaginary);
}

double Complex::modulus() const {
  return sqrt(real*real + imaginary*imaginary);
}
