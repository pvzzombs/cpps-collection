#include <iostream>
#include <cmath>
#include <vector>
#include <Eigen/Dense>

int main() {
  int fnum = 2;
  int labelCount = 2;
  Eigen::MatrixXi F(fnum, 5);
  Eigen::MatrixXi Label(1, 5);
  F << 1, 1, 0, 0, 1,
  0, 1, 0, 1, 0;
  Label << 1, 1, 0, 0, 1;
  Eigen::MatrixXi LabelTotal = Eigen::MatrixXi::Zero(labelCount, 1);
  Eigen::MatrixXd LabelP(labelCount, 1);

  for (int i = 0; i < 5; i++) {
    int labelC = Label(0, i);
    LabelTotal(labelC, 0) += 1;
  }
  LabelP(0, 0) = (double)LabelTotal(0, 0) / 5.0;
  LabelP(1, 0) = (double)LabelTotal(1, 0) / 5.0;
  // std::cout << LabelTotal << ";" << std::endl;
  std::vector<Eigen::MatrixXi> Lx = {
    Eigen::MatrixXi::Zero(fnum, 2),
    Eigen::MatrixXi::Zero(fnum, 2)
  };

  for (int i = 0; i < 5; i++) {
    int labelC = Label(0, i);
    for (int p = 0; p < fnum; p++) {
      Lx.at(labelC)(p, F(p, i)) += 1;
    }
  }
  // std::cout << Lx.at(0) << ";" << std::endl;
  // std::cout << Lx.at(1) << ";" << std::endl;
  std::vector<Eigen::MatrixXd> LPx = {
    Eigen::MatrixXd::Zero(fnum, 2),
    Eigen::MatrixXd::Zero(fnum, 2)
  };

  for (int p = 0; p < labelCount; p++) {
    for (int i = 0; i < fnum; i++) {
      for (int j = 0; j < 2; j++) {
        LPx.at(p)(i, j) = double(Lx.at(p)(i, j) + 1) / (LabelTotal(p, 0) + 2);
      }
    }
  }
  // std::cout << LPx.at(0) << ";" << std::endl;
  // std::cout << LPx.at(1) << ";" << std::endl;
  
  double highest = -1;
  int currentLabel = 0;
  Eigen::MatrixXi predict(2, 1);
  predict << 1, 1;

  for (int p = 0; p < labelCount; p++) {
    double temp = LabelP(p, 0);
    for (int i = 0; i < fnum; i++) {
      temp *= LPx.at(p)(i, predict(i, 0));
    }
    std::cout << temp << std::endl;
    if (temp > highest) {
      highest = temp;
      currentLabel = p;
    }
  }
  std::cout << "Classification: " << currentLabel << std::endl;
  return 0;
}