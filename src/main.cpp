#include <iostream>
#include <vector>
#include "framework/framework.h"
#include "algorithms/algorithms.hpp"

int main() {
    int size_a = 100; // Size of first sorted vector
    int size_b = 100; // Size of second sorted vector

    std::vector<int> a;
    std::vector<int> b;
    std::vector<int> result;

    generate_sorted_vectors(size_a, size_b, a, b, result);

    // Optionally print some elements of the merged result for verification
    std::cout << "First 10 elements of merged vector: ";
    for (int i = 0; i < 10 && i < result.size(); ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    // Two way merge
    std::vector<int> result_two_way_merge = two_way_merge(a, b);
    
    if (result == result_two_way_merge) {
        std::cout << "Two way merge result is correct" << std::endl;
    } else {
        std::cout << "Two way merge result is incorrect" << std::endl;
    }

    // Hwang-Lin Merging Algorithm
    // std::vector<int> result_hla = hla(a, b);

    // if (result == result_hla) {
    //     std::cout << "Hwang-Lin result is correct" << std::endl;
    // } else {
    //     std::cout << "Hwang-Lin result is incorrect" << std::endl;
    // }

    return 0;
}