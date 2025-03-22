#ifndef __COMPLEX_HPP
#define __COMPLEX_HPP

#include <iosfwd>

class Complex {
public:
  Complex operator-() const;

  Complex operator+(Complex const&) const;
  Complex operator-(Complex const&) const;
  Complex operator*(Complex const&) const;

  Complex& operator+=(Complex const&);
  Complex& operator-=(Complex const&);
  Complex& operator*=(Complex const&);

  Complex operator*(double) const;
  Complex& operator*=(double);

  friend Complex operator*(double, Complex const&);
  
  Complex& operator++();
  Complex operator++(int);

  friend std::ostream& operator<<(std::ostream&, Complex const&);
  friend std::istream& operator>>(std::istream&, Complex&);

  Complex conjugate() const;
  double modulus() const;

public:
  Complex() : real(0), imaginary(0) {}
  Complex(double real, double imaginary)
  : real(real), imaginary(imaginary) {}
private:
  double real;
  double imaginary;
};

#endif // __COMPLEX_HPP