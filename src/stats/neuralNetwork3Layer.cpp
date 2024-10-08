#include <iostream>
#include <cmath>
#include <vector>
#include <Eigen/Dense>

class NeuralNetwork3Layers {
public:
  Eigen::MatrixXd W1, W2, B1, B2;
  NeuralNetwork3Layers(int a, int b, int c): W1(a, b), W2(b, c), B1(1, b), B2(1, c) {
    W1 = Eigen::MatrixXd::Random(a, b);
    W2 = Eigen::MatrixXd::Random(b, c);
    B1 = Eigen::MatrixXd::Random(1, b);
    B2 = Eigen::MatrixXd::Random(1, c);

    std::cout << W1 << ";" << std::endl;
    std::cout << W2 << ";"  << std::endl;
    std::cout << B1 << ";"  << std::endl;
    std::cout << B2 << ";"  << std::endl;

  }
  Eigen::MatrixXd firstPass(Eigen::MatrixXd I) {
    return I * W1 + B1;
  }
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
  Eigen::MatrixXd secondPass(const Eigen::MatrixXd & G1) {
    return G1 * W2 + B2;
  }
};

int main() {
  // std::vector<std::vector<double>> dataSet;
  std::vector<Eigen::MatrixXd> inputDataSet;
  std::vector<Eigen::MatrixXd> outputDataSet;
  // Eigen::MatrixXd input(1, 2);

  // dataSet.resize(4);
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
  // std::cout << input << std::endl;
  NeuralNetwork3Layers nn(2, 4, 1);
  for(size_t i = 0; i < 1000; i++) {
    Eigen::MatrixXd totalDelCostdelW1 = Eigen::MatrixXd::Zero(nn.W1.rows(), nn.W1.cols());
    Eigen::MatrixXd totalDelCostdelB1 = Eigen::MatrixXd::Zero(nn.B1.rows(), nn.B1.cols());
    Eigen::MatrixXd totalDelCostdelW2 = Eigen::MatrixXd::Zero(nn.W2.rows(), nn.W2.cols());
    Eigen::MatrixXd totalDelCostdelB2 = Eigen::MatrixXd::Zero(nn.B2.rows(), nn.B2.cols());
    for (size_t d = 0; d < 4; d++) {
      Eigen::MatrixXd Z_1 = nn.firstPass(inputDataSet.at(d));
      Eigen::MatrixXd G_1 = nn.sigmoid(Z_1);
      Eigen::MatrixXd Z_2 = nn.secondPass(G_1);
      Eigen::MatrixXd Y_hat = nn.sigmoid(Z_2);

      Eigen::MatrixXd delCostdelY_hat = (2 * (Y_hat - outputDataSet.at(d)).array()).matrix();
      Eigen::MatrixXd delCostdelZ2 = (delCostdelY_hat.array() * (Y_hat.array() * (1 - Y_hat.array()))).matrix();
      Eigen::MatrixXd delCostdelW2 = G_1.transpose() * (delCostdelZ2);
      Eigen::MatrixXd delCostdelB2 = delCostdelZ2;
      Eigen::MatrixXd delCostdelW1 = inputDataSet.at(d).transpose() * ((delCostdelZ2 * nn.W2.transpose()).array() * G_1.array() * (1 - G_1.array())).matrix();
      Eigen::MatrixXd delCostdelB1 = ((delCostdelZ2 * nn.W2.transpose()).array() * G_1.array() * (1 - G_1.array())).matrix();

      totalDelCostdelW1 += delCostdelW1;
      totalDelCostdelB1 += delCostdelB1;
      totalDelCostdelW2 += delCostdelW2;
      totalDelCostdelB2 += delCostdelB2;

      // std::cout << delCostdelY_hat << std::endl;
      if (i % 100 == 0) {
        std::cout << "Iteration: " << i << " Loss: " << delCostdelY_hat.squaredNorm() << std::endl;
      }
    }
    if (i % 100 == 0) {
      std::cout << "W1 updates: \n" << totalDelCostdelW1 << "\n";
      std::cout << "B1 updates: \n" << totalDelCostdelB1 << "\n";
      std::cout << "W2 updates: \n" << totalDelCostdelW2 << "\n";
      std::cout << "B2 updates: \n" << totalDelCostdelB2 << "\n";
    }
    nn.W1 -= 1 * totalDelCostdelW1;
    nn.B1 -= 1 * totalDelCostdelB1;
    nn.W2 -= 1 * totalDelCostdelW2;
    nn.B2 -= 1 * totalDelCostdelB2;
  }
  {
    auto Z_1 = nn.firstPass(inputDataSet.at(1));
    auto G_1 = nn.sigmoid(Z_1);
    auto Z_2 = nn.secondPass(G_1);
    auto Y_hat = nn.sigmoid(Z_2);
    std::cout << "Actual: " << outputDataSet.at(1) << std::endl;
    std::cout << "Prediction: " << Y_hat << std::endl;
  }
  return 0;
}