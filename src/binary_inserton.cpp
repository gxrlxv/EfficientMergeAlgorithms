#include "binary_insertion.h"
#include <vector>
#include <iostream>
#include <algorithm>

std::vector<int> binary_insertion(const std::vector<int>& array, int value) {
    std::vector<int> result;
    int l = 0;
    int u = array.size() - 1;

    while (l <= u) {
        int j = (l + u) / 2; 
        if (array[j] < value) {
            l = j + 1;
        } else {
            u = j - 1;
        }
    }

    for (auto i = 0; i < array.size() - 1;){
        if (i == l) {
            result.push_back(value);
            continue;
        }
        i++;
        result.push_back(array[i]);
    }

    return result; 
}


int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    std::cout << "zhopa";
    std::vector<int> res = binary_insertion(numbers, 1);
    std::cout << "Vector after adding an element: ";
    // for (int num : res) {
        // std::cout << num << " ";
    // }

    return 0;
}