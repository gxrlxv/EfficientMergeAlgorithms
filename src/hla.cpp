// Hwang-Lin Merging Algorithm (Art of Computer Programming Volume 3 Sorting & Searching)
#include <array>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

template <typename IterContainer>
IterContainer hla(const IterContainer& a, const IterContainer& b) {
    auto [a_left, a_right, b_left, b_right] = std::array<typename IterContainer::const_iterator, 4>{{a.begin(), a.end(), b.begin(), b.end()}};
    IterContainer r(a.size() + b.size()); // Resulting vector

    typename IterContainer::iterator k_iter = r.end(); // Pointer for insertion
    
    while (a_left != a_right && b_left != b_right) {
        // H1
        int t;
        auto [m, n] = std::array<int, 2>{{static_cast<int>(std::distance(a_left, a_right)), static_cast<int>(std::distance(b_left, b_right))}};
        if (m > n)
            t = std::floor(std::log2(m / n));
        else
            t = std::floor(std::log2(n / m));
        
        // H2
        if (*(a_right - 1) < *(b_right - std::pow(2, t))) {
            k_iter -= std::pow(2, t);
            std::copy(b_right - std::pow(2, t), b_right, k_iter); // copy elements from (b_right - std::pow(2, t) + 1) to b_right
            b_right -= std::pow(2, t);
            continue;
        }

        // H3
        if (*(b_right - 1) < *(a_right - 1)) {
            *(--k_iter) = *(a_right - 1);
            a_right--;
            continue;
        }

        // H4
        if (*(b_right - 1) < *(a_right - std::pow(2, t))) {
            k_iter -= std::pow(2, t);
            std::copy(a_right - std::pow(2, t), a_right, k_iter); // copy elements from (a_right - std::pow(2, t) + 1) to a_right
            a_right -= std::pow(2, t);
            continue;
        }

        // H5
        if (*(a_right - 1) < *(b_right - 1)) {
            *(--k_iter) = *(b_right - 1);
            b_right--;
            continue;
        }
    }
    
    if (a_left == a_right) {
        std::copy(b_left, b_right, r.begin());
    } else {
        std::copy(a_left, a_right, r.begin());
    }
    
    return r;
}

int main() {
    std::vector<int> x = {1, 2, 3};
    std::vector<int> y = {4, 5, 6, 7};

    std::cout << "Vector x: \n";
    for (auto & e : x)
        std::cout << e << " ";
    std::cout << std::endl;

    std::cout << "Vector y: \n";
    for (auto & e : y)
        std::cout << e << " ";
    std::cout << std::endl;

    std::vector<int> z = hla(x, y);

    std::cout << "Resulting vector z: \n";
    for (auto & e : z)
        std::cout << e << " ";
    std::cout << std::endl;

    return 0;
}