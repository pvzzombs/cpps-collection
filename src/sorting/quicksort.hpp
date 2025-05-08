int quicksort_partition(std::vector<int> &arr, int start, int end) {
    int l = start;
    int r = end - 1;
    int pivot = arr.at(end);
    while(l < r) {
        while(arr.at(l) <= pivot && l < end) {
            l++;
        }
        while(arr.at(r) >= pivot && l < r) {
            r--;
        }
        if (l < r) {
            std::swap(arr.at(l), arr.at(r));
        }
    }
    if (arr.at(l) > arr.at(end)) {
        std::swap(arr.at(l), arr.at(end));
    }
    return l;
}

void quicksort(std::vector<int> &arr, int start, int end) {
    if (start >= end) { return; }
    int partition = quicksort_partition(arr, start, end);
    quicksort(arr, start, partition - 1);
    quicksort(arr, partition + 1, end);
}