#include <iostream>
#include <cmath>
#include <vector>
#include <Eigen/Dense>

int main() {
  const int fnum = 2;
  const int labelCount = 2;
  const int dataSetSize = 5;

  Eigen::MatrixXi features(fnum, dataSetSize);
  Eigen::MatrixXi label(1, dataSetSize);
  features << 1, 1, 0, 0, 1,
  0, 1, 0, 1, 0;
  label << 1, 1, 0, 0, 1;
  Eigen::MatrixXi labelTotal = Eigen::MatrixXi::Zero(labelCount, 1);
  Eigen::MatrixXd labelPriorProbability(labelCount, 1);

  for (int i = 0; i < dataSetSize; i++) {
    int labelC = label(0, i);
    labelTotal(labelC, 0) += 1;
  }

  for (int i = 0; i < labelCount; i++) {
    labelPriorProbability(i, 0) = (double)labelTotal(i, 0) / double(dataSetSize);
  }
  // std::cout << labelTotal << ";" << std::endl;
  std::vector<Eigen::MatrixXi> labelList = {
    Eigen::MatrixXi::Zero(fnum, 2),
    Eigen::MatrixXi::Zero(fnum, 2)
  };

  /* 
    labelC is the label
    p is the feature index (currently 0 or 1)
    features(p, i) is the feature value (currently 0 or 1)
    Example content of labelList.at(0):
    {0, 1  <--- 1st feature (1 means there is 1 occurence of the feature value 1)
     2, 0} <--- 2nd feature (2 means there is 2 occurence of the feature value 0)
    Example access:
    labelList.at(1)(0, 1) means the number of occurence of feature value 1 at feature index 0 of label 1
  */
  for (int i = 0; i < dataSetSize; i++) {
    int labelC = label(0, i);
    for (int p = 0; p < fnum; p++) {
      labelList.at(labelC)(p, features(p, i)) += 1;
    }
  }
  // std::cout << labelList.at(0) << ";" << std::endl;
  // std::cout << labelList.at(1) << ";" << std::endl;
  std::vector<Eigen::MatrixXd> likelihoodProbabilityList = {
    Eigen::MatrixXd::Zero(fnum, 2),
    Eigen::MatrixXd::Zero(fnum, 2)
  };

  for (int p = 0; p < labelCount; p++) {
    for (int i = 0; i < fnum; i++) {
      for (int j = 0; j < likelihoodProbabilityList.at(p).cols(); j++) {
        likelihoodProbabilityList.at(p)(i, j) = double(labelList.at(p)(i, j) + 1) / double(labelTotal(p, 0) + likelihoodProbabilityList.at(p).cols());
      }
    }
  }
  // std::cout << likelihoodProbabilityList.at(0) << ";" << std::endl;
  // std::cout << likelihoodProbabilityList.at(1) << ";" << std::endl;
  
  double highest = -1;
  int currentLabel = 0;
  Eigen::MatrixXi predict(2, 1);
  predict << 1, 1;

  for (int p = 0; p < labelCount; p++) {
    double temp = labelPriorProbability(p, 0);
    for (int i = 0; i < fnum; i++) {
      temp *= likelihoodProbabilityList.at(p)(i, predict(i, 0));
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