#include "Matrix.h"


Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols)
{
  if (rows < 1 || cols < 1)
  {
    throw std::length_error("Error: illegal lengths.");
  }
  nums = new float[rows*cols];
  for (int i = 0; i < rows*cols; i++)
  {
    nums[i] = 0;
  }
}

Matrix::Matrix() : rows(1), cols(1)
{
  nums = new float[1];
  nums[0] = 0;
}

Matrix::Matrix(const Matrix& matrix): rows(matrix.rows), cols(matrix.cols)
{
  nums = new float[rows*cols];
  for (int i = 0; i < rows*cols; i++)
  {
    nums[i] = matrix.nums[i];
  }
}

Matrix::~Matrix()
{
  delete[] nums;
}

int Matrix::get_rows() const
{
  return rows;
}

int Matrix::get_cols() const
{
  return cols;
}

Matrix& Matrix::transpose()
{
  Matrix tposed(rows, cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      tposed.nums[j*cols + i] = nums[i*cols + j];
    }
  }
  rows = tposed.cols;
  cols = tposed.rows;
  delete[] nums;
  nums = new float[rows*cols];
  for (int k = 0; k < rows*cols; k++)
  {
    nums[k] = tposed.nums[k];
  }
  return *this;
}


Matrix& Matrix::vectorize()
{
  rows *= cols;
  cols = 1;
  return *this;
}

void Matrix::plain_print() const
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      std::cout << nums[i*cols + j] << " ";
    }
    std::cout << "\n";
  }
}

Matrix Matrix::dot(Matrix matrix) const
{
  Matrix dotprod(rows, cols);
  for (int i = 0; i < rows*cols; i++)
  {
    dotprod.nums[i] = nums[i]*(matrix.nums[i]);
  }
  return dotprod;
}

float Matrix::norm() const
{
  int sum = 0;
  for (int i = 0; i < cols*rows; i++)
  {
    sum += (int)std::pow(nums[i], 2);
  }
  float norm = std::sqrt((float)sum);
  return norm;
}

Matrix Matrix::rref() const {
  Matrix result(*this);
  return result;
}




int Matrix::argmax () const
{
  float maxnum = nums[0];
  int maxind = 0;
  for (int i = 0; i < rows*cols; i++)
  {
    if (nums[i] > maxnum)
    {
      maxnum = nums[i];
      maxind = i;
    }
  }
  return maxind;
}

float Matrix::sum () const
{
  float cursum = 0;
  for (int i = 0; i < rows*cols; i++)
  {
    cursum += nums[i];
  }
  return cursum;
}

Matrix& Matrix::operator+=(const Matrix& rhs)
{
  for (int i = 0; i < rows*cols; i++)
  {
    nums[i] += rhs.nums[i];
  }
  return *this;
}

Matrix Matrix::operator+(const Matrix& rhs) const
{
  Matrix newm(rows, cols);
  for (int i = 0; i < rows*cols; i++)
  {
    newm.nums[i] = rhs.nums[i] + nums[i];
  }
  return newm;
}

Matrix& Matrix::operator=(const Matrix& equ)
{
  if (this == &equ)
  {
    return *this;
  }

  if (rows*cols != equ.rows*equ.cols)
  {
    delete[] nums;
    rows = equ.rows;
    cols = equ.cols;
    nums = new float[rows*cols];
  }

  for (int i = 0; i < rows*cols; i++)
  {
    nums[i] = equ.nums[i];
  }
  return *this;
}

Matrix Matrix::operator*(const Matrix& rhs) const
{
  Matrix mult(rows, rhs.cols);
  for (int i = 0; i < mult.rows; i++)
  {
    for (int j = 0; j < mult.cols; j++)
    {
      mult.nums[i*mult.cols + j] = 0;
      for (int k = 0; k < rhs.rows; k++)
      {
        mult.nums[i*mult.cols + j] += nums[i*rows+k]*rhs.nums[k*rhs.cols+j];
      }
    }
  }
  return mult;
}

Matrix Matrix::operator*(const float rscalar) const
{
  Matrix scalarmult(rows, cols);
  for (int i = 0; i < rows*cols; i++)
  {
    scalarmult.nums[i] = nums[i]*rscalar;
  }
  return scalarmult;
}



Matrix operator*(float lscalar, const Matrix& m)
{
  Matrix mult(m);
  for (int i = 0; i < m.rows*m.cols; i++)
  {
    mult.nums[i] *= lscalar;
  }
  return mult;
}

float& Matrix::operator()(int i, int j)
{
 return nums[i*cols + j];
}

float& Matrix::operator[](int i)
{
  return nums[i];
}

float Matrix::operator()(int i, int j) const
{
  return nums[i*cols + j];
}
float Matrix::operator[](int i) const
{
  return nums[i];
}



std::istream& operator>>(std::istream& is, const Matrix& m)
{
  if (!is)
  {
    throw std::runtime_error("Input stream invalid");
  }
  is.seekg(0, std::ios::end);
  int length = (int) is.tellg();
  is.seekg(0, std::ios::beg);

  if ((int) length/(int)sizeof(float) < (int)m.rows*m.cols)
  {
    throw std::runtime_error("Input stream too short");
  }
  //float a[128*784] = {0};
  for (int i = 0; i < m.rows*m.cols; i++)
  {
    //is.read((char*) &a[i], sizeof(float));
    //float b = a[i];
    is.read((char*) &m.nums[i], sizeof(float));
  }

  return is;
}


std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
  for (int i = 0; i < m.rows; i++)
  {
    for (int j = 0; j < m.cols; j++)
    {
      if (m.nums[i*m.cols + j] > MIN_VAL)
      {
        os << "**";
      }
      else
      {
        os << "  ";
      }
    }
    os << "\n";
  }
  return os;
}