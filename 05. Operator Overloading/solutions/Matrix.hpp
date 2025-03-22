#ifndef __MATRIX_HPP
#define __MATRIX_HPP

#include <iostream>
#include <initializer_list>

template<unsigned int const M, unsigned int const N>
class Matrix {
public:
  Matrix operator+(Matrix const& other) const {
    Matrix res(*this);
    res += other;
    return res;
  }

  Matrix& operator+=(Matrix const& other) {
    for (unsigned int i = 0; i < M; ++i) {
      for (unsigned int j = 0; j < N; ++j) {
        m_data[i][j] += other.m_data[i][j];
      }
    }
    return *this;
  }

  Matrix operator*(double scalar) const {
    Matrix res(*this);
    res *= scalar;
    return res;
  }

  friend Matrix operator*(double scalar, Matrix const& matrix) {
    Matrix res(matrix);
    res *= scalar;
    return res;
  }

  Matrix& operator*=(double scalar) {
    for (unsigned int i = 0; i < M; ++i) {
      for (unsigned int j = 0; j < N; ++j) {
        m_data[i][j] *= scalar;
      }
    }
    return *this;
  }

  template<unsigned int const K>
  Matrix<M,K> operator*(Matrix<N,K> const& other) const {
    Matrix<M,K> res;
    for (size_t i = 0; i < M; ++i) {
      for (size_t k = 0; k < K; ++k) {
        for (size_t j = 0; j < N; ++j) {
          res[i][k] += m_data[i][j] * other[j][k];
        }
      }
    }
    return res;
  }

  double* operator[](unsigned int index) {
    return m_data[index];
  }

  double const* operator[](unsigned int index) const {
    return m_data[index];
  }

public:
  Matrix() : m_data() {}

  Matrix(std::initializer_list<double> const& l)
  : Matrix() {
    auto it = l.begin();
    size_t i = 0;
    while (it != l.end() && i < M*N)
      m_data[0][i++] = *it++;
  }

  Matrix(Matrix const& other) {
    copy(other);
  }

  friend std::ostream& operator<<(std::ostream& os, Matrix const& m) {
    for (size_t i = 0; i < M; ++i) {
      for (size_t j = 0; j < N; ++j) {
        os << m.m_data[i][j] << ' ';
      }
      os << std::endl;
    }
    return os;
  }

private:
  void copy(Matrix const& other) {
    for (size_t i = 0; i < M; ++i) {
      for (size_t j = 0; j < N; ++j) {
        m_data[i][j] = other.m_data[i][j];
      }
    }
  }
  
private:
  double m_data[M][N];
};

#endif // __MATRIX_HPP