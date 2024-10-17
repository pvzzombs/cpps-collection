#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
  std::string mainString = "abcabcdabcdxabcdabcd";
  std::string patternString = "abcdabcd";
  std::vector<int> LPS(patternString.size());
  std::fill(LPS.begin(), LPS.end(), 0);
  int i, j;
  i = 0;
  j = 1;
  while (j < patternString.size()) {
    if (patternString.at(i) != patternString.at(j)) {
      if (i != 0) {
        i = LPS.at(i - 1);
      } else {
        LPS[j] = 0;
        j++;
      }
    } else {
      LPS[j] = i + 1;
      i++;
      j++;
    }
  }
  for (auto &e : LPS) {
    std::cout << e << " ";
  }
  std::cout << std::endl;

  // KMP main algo
  i = 0;
  j = 0;
  while (i < mainString.size()) {
    if (mainString.at(i) != patternString.at(j)) {
      if (j == 0) {
        i++;
      } else {
        j = LPS.at(j - 1);
      }
    } else {
      i++;
      j++;
      if (j == patternString.size()) {
        std::cout << (i - j) << std::endl;
        j = LPS.at(j - 1);
      }
    }
  }
  return 0;
}