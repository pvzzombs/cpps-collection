void insertionsort(std::vector<int> &arr) {
  for (int i = 1; i < arr.size(); i++) {
    int j = i;
    while (j - 1 >= 0 && arr.at(j - 1) > arr.at(j)) {
      std::swap(arr.at(j - 1), arr.at(j));
      j--;
    }
  }
}