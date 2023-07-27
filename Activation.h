

#ifndef ACTIVATION_H
#define ACTIVATION_H
#include "Matrix.h"
using std::exp;

//our namespace for the activation functions
namespace activation {
    Matrix& relu(Matrix& m); //relu func
    Matrix& softmax(Matrix& m); //softmax func
}

#endif //ACTIVATION_H

