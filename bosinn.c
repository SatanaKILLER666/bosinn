#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
private:
  double real;
  double imaginary;

public:
  Complex();
  Complex(double real, double imaginary);
  Complex(const Complex& other);

  double getReal() const;
  double getImaginary() const;

  Complex operator+(const Complex& other) const;
  Complex operator-(const Complex& other) const;
  Complex operator*(const Complex& other) const;

  Complex& operator+=(const Complex& other);
  Complex& operator-=(const Complex& other);
  Complex& operator*=(const Complex& other);

  friend std::ostream& operator<<(std::ostream& os, const Complex& complex);
};

#endif
#include "complex.h"

Complex::Complex() : real(0.0), imaginary(0.0) {}

Complex::Complex(double real, double imaginary) : real(real), imaginary(imaginary) {}

Complex::Complex(const Complex& other) : real(other.real), imaginary(other.imaginary) {}

double Complex::getReal() const { return real; }

double Complex::getImaginary() const { return imaginary; }


Complex Complex::operator+(const Complex& other) const {
  return Complex(real + other.real, imaginary + other.imaginary);
}

Complex Complex::operator-(const Complex& other) const {
  return Complex(real - other.real, imaginary - other.imaginary);
}

Complex Complex::operator*(const Complex& other) const {
  double newReal = real * other.real - imaginary * other.imaginary;
  double newImaginary = real * other.imaginary + imaginary * other.real;
  return Complex(newReal, newImaginary);
}

Complex& Complex::operator+=(const Complex& other) {
  real += other.real;
  imaginary += other.imaginary;
  return *this;
}

Complex& Complex::operator-=(const Complex& other) {
  real -= other.real;
  imaginary -= other.imaginary;
  return *this;
}

Complex& Complex::operator*=(const Complex& other) {
  double tempReal = real * other.real - imaginary * other.imaginary;
  imaginary = real * other.imaginary + imaginary * other.real;
  real = tempReal;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Complex& complex) {
  os << complex.real;
  if (complex.imaginary >= 0) {
    os << "+";
  }
  os << complex.imaginary << "i";
  return os;
}
#include <iostream>
#include "complex.h"

int main() {
  Complex c1;
  Complex c2(2.0, 3.0);
  Complex c3 = c2;

  std::cout << "c1: " << c1 << std::endl;
  std::cout << "c2: " << c2 << std::endl;
  std::cout << "c3: " << c3 << std::endl;

  Complex c4 = c1 + c2;
  std::cout << "c1 + c2: " << c4 << std::endl;

  Complex c5 = c2 - c3;
  std::cout << "c2 - c3: " << c5 << std::endl;

  Complex c6 = c2 * c3;
  std::cout << "c2 * c3: " << c6 << std::endl;

  c1 += c2;
  std::cout << "c1 += c2: " << c1 << std::endl;

  c1 -= c2;
  std::cout << "c1 -= c2: " << c1 << std::endl;

  c1 *= c2;
  std::cout << "c1 *= c2: " << c1 << std::endl;

  return 0;
}