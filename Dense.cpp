#include "Dense.h"

Matrix Dense::get_weights() const
{
  return weights;
}
Matrix Dense::get_bias() const
{
  return bias;
}
ActivationFunction Dense::get_activation() const
{
  return act_func;
}

// OPERATORS

Matrix& Dense::operator()(Matrix& input) const
{
  input = input*weights;
  return act_func(input+=bias);
}