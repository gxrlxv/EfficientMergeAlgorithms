#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <algorithm>
#include <vector>
#include <list>
#include <array>
#include <cmath>

// Standard merging of 2 sorted arrays with n and m lenghts
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

template <typename IterContainer, typename T>
void binary_insertion(IterContainer& arr, const T& elem) {
    typename IterContainer::iterator l = arr.begin();
    typename IterContainer::iterator u = arr.end();

    while (std::distance(l, u) > 0) {
        typename IterContainer::iterator j = l;
        int mid = std::distance(l, u) / 2;
        std::advance(j, mid);

        if (*j < elem) {
            l = std::next(j);
        } else {
            u = j;
        }
    }

    arr.insert(l, elem);
}

// Hwang-Lin Merging Algorithm (Art of Computer Programming Volume 3 Sorting & Searching)
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

#endif // ALGORITHMS_H