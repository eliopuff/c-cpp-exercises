// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <fstream>
#define MIN_VAL 0.1

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
	int rows, cols;
} matrix_dims;


// matrix class up ahead!

class Matrix {
 private:
  int rows;
  int cols;
  float *nums;

 public:
  //basic constructor with variables
  Matrix(int rows, int cols);

  //default constructor
  Matrix();

  //copy constructor
  Matrix(const Matrix& matrix);

  //basic destructor
  ~Matrix();

  //GETTERS
  int get_rows() const;
  int get_cols() const;

  //MATRIX ACTIONS
  Matrix& transpose();
  Matrix& vectorize();
  void plain_print() const;
  Matrix dot(Matrix matrix) const;
  float norm() const;
  Matrix rref() const; // BONUS- return later
  int argmax() const;
  float sum() const;


  //OPERATORS
  Matrix& operator+=(const Matrix& rhs);
  Matrix operator+(const Matrix& rhs) const;
  Matrix& operator=(const Matrix& equ);
  Matrix operator*(const Matrix& rhs) const;
  Matrix operator*(float rscalar) const;
  friend Matrix operator*(float lscalar, const Matrix& m);
  float& operator()(int i, int j);
  float& operator[](int i);

  float operator()(int i, int j) const;
  float operator[](int i) const;

  //STREAM FRIENDS
  friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
  friend std::istream& operator>>(std::istream& os, const Matrix& m);



};

#endif //MATRIX_H