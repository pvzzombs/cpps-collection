void mergesort_merge(std::vector<int> &arr, std::vector<int> &temp, int start, int mid, int end) {
  int i = start;
  int j = mid + 1;
  int k = 0;
  while (i <= mid && j <= end) {
    if (arr.at(i) < arr.at(j)) {
      temp.at(k) = arr.at(i);
      i++;
    } else {
      temp.at(k) = arr.at(j);
      j++;
    }
    k++;
  }
  
  while (i <= mid) {
    temp.at(k) = arr.at(i);
    k++;
    i++;
  }
  
  while (j <= end) {
    temp.at(k) = arr.at(j);
    k++;
    j++;
  }
  
  int m = 0;
  for (int l = start; l <= end; l++) {
    arr.at(l) = temp.at(m);
    m++;
  }
}

void mergesort(std::vector<int> &arr, std::vector<int> &temp, int start, int end) {
  if (start == end) {
    return;
  }
  int mid = (start + end) / 2;
  mergesort(arr, temp, start, mid);
  mergesort(arr, temp, mid + 1, end);
  mergesort_merge(arr, temp, start, mid, end);
}