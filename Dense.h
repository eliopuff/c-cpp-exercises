#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

typedef Matrix& (*ActivationFunction)(Matrix& m);

// Insert Dense class here...
class Dense {
 private:
  // private members
  Matrix weights;
  Matrix bias;
  ActivationFunction act_func;

 public:
  Dense(Matrix weights, Matrix bias, ActivationFunction func) : weights
  (weights), bias(bias), act_func(func) {} //constructor

  // a few getters for our use
  Matrix get_weights() const;
  Matrix get_bias() const;
  ActivationFunction get_activation() const;

  // OPERATORS
  Matrix& operator()(Matrix& input) const;


};

#endif //DENSE_H
