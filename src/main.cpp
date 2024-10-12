#include <iostream>
#include <vector>
#include "framework/framework.h"

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

    return 0;
}