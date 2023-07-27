//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4
#define MAX_NUMS 10

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};

class MlpNetwork {
 private:
  // our private class members are arrays of weights and biases for each layer
  Matrix weights[MLP_SIZE];
  Matrix biases[MLP_SIZE];
  Matrix m;
  Dense layer1 = Dense(m, m, activation::relu);
  Dense layer2 = Dense(m, m, activation::relu);
  Dense layer3 = Dense(m, m, activation::relu);
  Dense layer4 = Dense(m, m, activation::softmax);

 public:
  // we have a constructor, and a () operator
  MlpNetwork(const Matrix weights[MLP_SIZE], const Matrix biases[MLP_SIZE]);

  digit operator()(Matrix& img);
};

#endif // MLPNETWORK_H