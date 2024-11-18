#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <algorithm>
#include <vector>
#include <list>
#include <array>
#include <cmath>
#include <functional>

// Standard merging of 2 sorted arrays with n and m lenghts
template <typename IterContainer>
IterContainer tape_merge(const IterContainer& a, const IterContainer& b) {
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

std::vector<int> simple_binary_merge(const std::vector<int>& a, std::vector<int>& b) {
    int m = static_cast<int>(a.size()) - 1;
    int n = static_cast<int>(b.size()) - 1;

    while (m >= 0) {
        auto b_end = b.begin();
        std::advance(b_end, n + 1);

        // binary search for the insert position
        auto it = std::lower_bound(b.begin(), b_end, a[m]);

        n = static_cast<int>(std::distance(b.begin(), it)) + 1;

        b.insert(it, a[m]);
        m--;
    }

    return b;
}


// Generalized Binary Merge Algorithm
std::vector<int> generalized_binary_merge(std::vector<int>& A, std::vector<int>& B) {
    int m = A.size();
    int n = B.size();

    std::vector<int> R(m + n);
    auto it = R.end();

    while (m > 0 && n > 0) {
        // GB1:
        int alpha = static_cast<int>(std::log2(static_cast<double>(n) / m));
        int x = n - static_cast<int>(std::pow(2, alpha)) + 1;

        int am = A[m - 1];
        int bx = B[x - 1];

        if (am < bx) {
            // GB2:
            int copied_count = std::distance(B.begin() + x - 1, B.end());
            it -= copied_count; 

            std::copy(B.begin() + x - 1, B.end(), it);

            B.erase(B.begin() + x - 1, B.end());

            n = B.size();
        } else {
            // GB3
            auto pos = std::lower_bound(B.begin(), B.begin() + x, am);
            B.insert(pos, am);
            A.pop_back();

            m = A.size();
            n = B.size();
        }

        if (n < m) {
            std::swap(A, B);
            std::swap(m, n);
        }
    }

    it -= A.size();
    std::copy(A.begin(), A.end(), it);
    it -= B.size();
    std::copy(B.begin(), B.end(), it); 

    return R;
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
        int t, s;
        auto [m, n] = std::array<int, 2>{{static_cast<int>(std::distance(a_left, a_right)), static_cast<int>(std::distance(b_left, b_right))}};
        if (m > n) {
            t = std::floor(std::log2(m / n));
            s = std::pow(2, t);

            // H4
            if (*(b_right - 1) < *(a_right - s)) {
                k_iter -= s;
                std::copy(a_right - s, a_right, k_iter); // copy elements from (a_right - s) to a_right to result vector
                a_right -= s;
                continue;
            }
        }
        else {
            t = std::floor(std::log2(n / m));
            s = std::pow(2, t);

            // H2
            if (*(a_right - 1) < *(b_right - s)) {
                k_iter -= s;
                std::copy(b_right - s, b_right, k_iter); // copy elements from (b_right - s) to b_right to result vector
                b_right -= s;
                continue;
            }
        }

        // H3
        if (*(b_right - 1) < *(a_right - 1)) {
            *(--k_iter) = *(a_right - 1);
            a_right--;
            continue;
        }

        // H5
        if (*(a_right - 1) <= *(b_right - 1)) {
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

// Binary Merge Algorithm (https://github.com/rklaehn/binary-merge)
template <typename IterContainer>
IterContainer binary_merge(const IterContainer& a, const IterContainer& b) {
    IterContainer r(a.size() + b.size());
    
    auto a_begin = a.begin();
    auto b_begin = b.begin();
    auto r_begin = r.begin();
    
    // Определение вложенной функции binary_merge_recursive
    std::function<void(typename IterContainer::const_iterator&, 
                       typename IterContainer::const_iterator&,
                       typename IterContainer::iterator&,
                       size_t, size_t)> binary_merge_recursive;
    
    binary_merge_recursive = [&](typename IterContainer::const_iterator& a_it, 
                                 typename IterContainer::const_iterator& b_it,
                                 typename IterContainer::iterator& r_it,
                                 size_t an, size_t bn) {
        if (an == 0) {
            std::copy(b_it, b_it + bn, r_it);
            r_it += bn;
            b_it += bn;
            return;
        } else if (bn == 0) {
            std::copy(a_it, a_it + an, r_it);
            r_it += an;
            a_it += an;
            return;
        } else {
            // neither a nor b are 0
            size_t am = an / 2;
            auto a_mid = a_it + am;
         
            auto b_mid = std::lower_bound(b_it, b_it + bn, *a_mid);
            size_t bm = std::distance(b_it, b_mid);
            
            binary_merge_recursive(a_it, b_it, r_it, am, bm);
            
            if (b_mid != b_it + bn && *b_mid == *a_mid) {
                // same elements
                *r_it++ = *a_mid++;
                *r_it++ = *b_mid++;
                binary_merge_recursive(a_mid, b_mid, r_it, an - am - 1, bn - bm - 1);
            } else {
                // not found
                *r_it++ = *a_mid++;
                binary_merge_recursive(a_mid, b_mid, r_it, an - am - 1, bn - bm);
            }
        }
    };
    
    binary_merge_recursive(a_begin, b_begin, r_begin, a.size(), b.size());

    return r;
}

#endif // ALGORITHMS_H