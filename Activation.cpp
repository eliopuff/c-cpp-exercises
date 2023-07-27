#include "Activation.h"

Matrix& activation::relu(Matrix& m)
{
  int rows = m.get_rows();
  int cols = m.get_cols();
  for (int i = 0; i < rows*cols; i++) //loop through all values
  {
    if (m[i] < 0)
    {
      m[i] = 0; //in this case we assign the value 0, as relu should
    }
  }
  return m;
}

Matrix& activation::softmax(Matrix& m)
{
  int rows = m.get_rows();
  int cols = m.get_cols();

  float coeff_denom = 0; // we shall sum up the coefficient denominator
  for (int i = 0; i < cols; i++) // in case we don't get a vector
  {
    for (int j = 0; j < rows; j++)
    {
      float cur = m(j, i);
      float new_cur = exp(cur);
      m(j, i) = new_cur;
      coeff_denom += new_cur;
    }
  }
  float coeff = ((float) 1) / coeff_denom;
  m = m * coeff;
  return m;
}
