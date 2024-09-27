// Hwang-Lin Merging Algorithm (Art of Computer Programming Volume 3 Sorting & Searching)
#include <array>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

template <typename IterContainer, typename T>
typename IterContainer::iterator lower_bound(IterContainer& arr, T val) {
    auto [left, right] = std::array<typename IterContainer::iterator, 2>{{arr.begin(), arr.end()}};

    while (left < right) {
        typename IterContainer::iterator mid = left + std::distance(left, right) / 2;
        
        if (*mid < val) {
            left = std::next(mid);
        } else {
            right = mid;
        }
    }

    if (left != arr.begin()) {
        return --left;
    }

    return arr.begin();
}

template <typename IterContainer>
IterContainer hla(const IterContainer& a, const IterContainer& b) {
    auto [a_begin, a_end, b_begin, b_end] = std::array<typename IterContainer::const_iterator, 4>{{a.begin(), a.end(), b.begin(), b.end()}};
    IterContainer r(a.size() + b.size());
    
    while (a_begin != a_end && b_begin != b_end) {
        // H1
        int t;
        if (a_end > b_end)
            t = std::floor(std::log2(std::distance(a_begin, a_end) / std::distance(b_begin, b_end)));
        else
            t = std::floor(std::log2(std::distance(b_begin, b_end) / std::distance(a_begin, a_end)));
        
        // H2
        if (*(a_end - 1) < *(b_end - std::pow(2, t))) {
            std::copy(b_end - std::pow(2, t), b_end, r.end() - std::distance(b_end - std::pow(2, t), b.end())); // copy b elements from (b_end - std::pow(2, t) + 1) to b_end
            b_end -= std::pow(2, t);
            continue;
        }

        // H3
        typename IterContainer::iterator k_iter = lower_bound(r, *(a_end - 1));
        if (*k_iter < *(a_end - 1)) {
            *k_iter = *(a_end - 1);
            a_end--;
            b_end = b_begin + std::distance(r.begin(), k_iter);
            continue;
        } else {
            *k_iter = *(a_end - 1);
        }

        // H4
        if (*(b_end - 1) < *(a_end - std::pow(2, t))) {
            std::copy(a_end - std::pow(2, t), a_end, r.end() - std::distance(a_end - std::pow(2, t), a.end())); // copy a elements from (a_end - std::pow(2, t) + 1) to a_end
            a_end -= std::pow(2, t);
            continue;
        }

        // H5
        k_iter = lower_bound(r, *(b_end - 1));
        if (*k_iter < *(b_end - 1)) {
            *k_iter = *(b_end - 1);
            b_end--;
            a_end = a_begin + std::distance(r.begin(), k_iter);
            continue;
        } else {
            *k_iter = *(b_end - 1);
        }
    }
    
    if (a_begin == a_end) {
        std::copy(b_begin, b_end, r.begin());
    } else {
        std::copy(a_begin, a_end, r.begin());
    }
    
    return r;
}

int main() {
    std::vector<int> x = {1, 6};
    std::vector<int> y = {2, 5, 7, 10};

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