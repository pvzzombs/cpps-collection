#include <iostream>
#include <vector>
#include "quicksort.hpp"
#include "mergesort.hpp"


void print(std::vector<int> & arr) {
    for (auto &e: arr) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {3, 5, 8, 1, 2, 9, 4, 7, 6};
    // std::vector<int> arr = {3, 2, 2, 1, 1, 2, 1, 2, 1};
    std::vector<int> temp;
    temp.resize(arr.size());
    std::vector<int> arr2;
    
    arr2 = arr;
    std::cout << "Quick Sort:" << std::endl;
    quicksort(arr2, 0, arr2.size() - 1);
    print(arr2);

    arr2 = arr;
    std::cout << "Merge Sort:" << std::endl;
    mergesort(arr2, temp, 0, arr2.size() - 1);
    print(arr2);

    return 0;
}