#include "framework.h"
#include <vector>
#include <cstdlib> 
#include <algorithm>

void generate_random_vectors(int size_a, int size_b, std::vector<int>& a, std::vector<int>& b, std::vector<int>& result){
    a.resize(size_a);
    b.resize(size_b);
    result.resize(size_a + size_b);

    for (int i = 0; i < size_a; ++i) {
        a[i] = rand() % 10000;
    }
    std::sort(a.begin(), a.end());

    for (int i = 0; i < size_b; ++i) {
        b[i] = rand() % 10000;
    }
    std::sort(b.begin(), b.end());

    std::merge(a.begin(), a.end(), b.begin(), b.end(), result.begin());
    std::sort(result.begin(), result.end());
}