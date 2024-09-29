// Standard merging of 2 sorted arrays with n and m lenghts
#include <array>
#include <algorithm>
#include <iostream>
#include <vector>

template <typename IterContainer>
IterContainer two_way_merge(const IterContainer& a, const IterContainer& b) {
    auto [a_left, a_right, b_left, b_right] = std::array<typename IterContainer::const_iterator, 4>{{a.begin(), a.end(), b.begin(), b.end()}};
    IterContainer r(a.size() + b.size()); // Resulting vector

    typename IterContainer::iterator k_iter = r.begin(); // Pointer for insertion

    while (a_left != a_right && b_left != b_right) {
        if (*a_left <= *b_left) {
            *k_iter = *a_left;
            a_left++;
        } else {
            *k_iter = *b_left;
            b_left++;
        }
        k_iter++;
    }

    if (a_left == a_right) {
        std::copy(b_left, b_right, k_iter);
    } else {
        std::copy(a_left, a_right, k_iter);
    }

    return r;
}

int main() {
    std::vector<int> x = {1, 6, 9, 11};
    std::vector<int> y = {2, 5, 7, 10};

    std::cout << "Vector x: \n";
    for (auto & e : x)
        std::cout << e << " ";
    std::cout << std::endl;

    std::cout << "Vector y: \n";
    for (auto & e : y)
        std::cout << e << " ";
    std::cout << std::endl;

    std::vector<int> z = two_way_merge(x, y);

    std::cout << "Resulting vector z: \n";
    for (auto & e : z)
        std::cout << e << " ";
    std::cout << std::endl;

    return 0;
}