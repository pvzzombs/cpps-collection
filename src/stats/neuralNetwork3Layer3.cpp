#include <iostream>
#include <cmath>
#include <vector>
#include <Eigen/Dense>

Eigen::MatrixXd sigmoid(const Eigen::MatrixXd & m) {
  Eigen::MatrixXd output(m.rows(), m.cols());
  const double E = std::exp(1);
  // std::cout << E << std::endl;
  for (size_t i = 0; i < m.rows(); i++) {
    for (size_t j = 0; j < m.cols(); j++) {
      output(i, j) = 1 / (1 + std::pow(E, -1 * m(i, j)));
    }
  }
  return output;
}

int main() {
  double learningRate = 0.01;
  std::vector<Eigen::MatrixXd> inputDataSet;
  std::vector<Eigen::MatrixXd> outputDataSet;
  Eigen::MatrixXd W1, W2, B1, B2;
  W1 = Eigen::MatrixXd::Random(2, 3);
  W2 = Eigen::MatrixXd::Random(3, 1);
  B1 = Eigen::MatrixXd::Random(1, 3);
  B2 = Eigen::MatrixXd::Random(1, 1);

  inputDataSet.resize(4);
  outputDataSet.resize(4);
  for (size_t i = 0; i < 4; i++) {
    inputDataSet.at(i).resize(1, 2);
    outputDataSet.at(i).resize(1, 1);
  }
  inputDataSet.at(0) << 0, 0;
  outputDataSet.at(0) << 0;
  inputDataSet.at(1) << 0, 1;
  outputDataSet.at(1) << 1;
  inputDataSet.at(2) << 1, 0;
  outputDataSet.at(2) << 1;
  inputDataSet.at(3) << 1, 1;
  outputDataSet.at(3) << 0;

  for (size_t i = 0; i < 30; i++) {
    double err = 0;
    for(size_t epoch = 0; epoch < 1000; epoch++) {
      double errEpoch = 0;
      for (size_t d = 0; d < 4; d++) {
        Eigen::MatrixXd Z_1 = inputDataSet.at(d) * W1 + B1;
        Eigen::MatrixXd G_1 = sigmoid(Z_1);
        Eigen::MatrixXd Z_2 = G_1 * W2 + B2;
        Eigen::MatrixXd Y_hat = sigmoid(Z_2);

        Eigen::MatrixXd delCostdelY_hat = (2 * (Y_hat - outputDataSet.at(d)).array()).matrix();
        Eigen::MatrixXd delCostdelZ2 = (delCostdelY_hat.array() * (Y_hat.array() * (1 - Y_hat.array()))).matrix();
        Eigen::MatrixXd delCostdelB2 = delCostdelZ2;
        Eigen::MatrixXd delCostdelW2 = G_1.transpose() * delCostdelZ2;
        Eigen::MatrixXd delCostdelB1 = ((delCostdelZ2 * W2.transpose()).array() * G_1.array() * (1 - G_1.array())).matrix();
        Eigen::MatrixXd delCostdelW1 = inputDataSet.at(d).transpose() * delCostdelB1;

        W1 -= learningRate * delCostdelW1;
        B1 -= learningRate * delCostdelB1;
        W2 -= learningRate * delCostdelW2;
        B2 -= learningRate * delCostdelB2;

        Eigen::MatrixXd cost = Y_hat - outputDataSet.at(d);
        errEpoch += (cost(0, 0) * cost(0, 0));
      }
      errEpoch /= 4;
      err = errEpoch;
    }
    std::cout << i + 1 << "th 1000 epoch, error: " << err << std::endl;
  }
  {
    for (size_t i = 0; i < 4; i++) {
      Eigen::MatrixXd Z_1 = inputDataSet.at(i) * W1 + B1;
      Eigen::MatrixXd G_1 = sigmoid(Z_1);
      Eigen::MatrixXd Z_2 = G_1 * W2 + B2;
      Eigen::MatrixXd Y_hat = sigmoid(Z_2);
      std::cout << "Training data: " << inputDataSet.at(i) << std::endl;
      std::cout << "Actual: " << outputDataSet.at(i) << std::endl;
      std::cout << "Prediction: " << Y_hat << std::endl;
    }
  }
  return 0;
}