#include "MlpNetwork.h"

MlpNetwork::MlpNetwork(const Matrix weights[MLP_SIZE], const Matrix
biases[MLP_SIZE])
{
  for (int i = 0; i < MLP_SIZE; ++i)
  {
    this->weights[i] = weights[i];
    this->biases[i] = biases[i];
  }
  layer1 = Dense(weights[0], biases[0], activation::relu);
  layer2 = Dense(weights[1], biases[1], activation::relu);
  layer3 = Dense(weights[2], biases[2], activation::relu);
  layer4 = Dense(weights[3], biases[3], activation::softmax);
}

digit MlpNetwork::operator()(Matrix& img)
{
  img = img.vectorize();
  img = layer1(img);
  img = layer2(img);
  img = layer3(img);
  img = layer4(img);

  float max_res = img[0];
  unsigned int max_ind = 0;
  for (int j = 0; j < MAX_NUMS; j++)
  {
    if (img[j] > max_res)
    {
      max_res = img[j];
      max_ind = j;
    }
  }

  digit result = {max_ind, max_res};
  return result;
}