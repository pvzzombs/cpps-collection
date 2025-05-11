void selectionsort(std::vector<int> &arr) {
  for (int i = 0; i < arr.size() - 1; i++) {
    int minIndex = i;
    int minNum = arr.at(i);
    for (int j = minIndex + 1; j < arr.size(); j++) {
      if (arr.at(j) < minNum) {
        minIndex = j;
        minNum = arr.at(j);
      }
    }
    std::swap(arr.at(i), arr.at(minIndex));
  }
}