// Binary Merge Algorithm (https://github.com/rklaehn/binary-merge)
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>

template <typename IterContainer>
void binary_merge_recursive(typename IterContainer::const_iterator& a_it, 
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
        
        binary_merge_recursive<IterContainer>(a_it, b_it, r_it, am, bm);
        
        if (b_mid != b_it + bn && *b_mid == *a_mid) {
            // same elements
            *r_it++ = *a_mid++;
            *r_it++ = *b_mid++;
            binary_merge_recursive<IterContainer>(a_mid, b_mid, r_it, an - am - 1, bn - bm - 1);
        } else {
            // not found
            *r_it++ = *a_mid++;
            binary_merge_recursive<IterContainer>(a_mid, b_mid, r_it, an - am - 1, bn - bm);
        }
    }
}

template <typename IterContainer>
IterContainer binary_merge(const IterContainer& a, const IterContainer& b) {
    IterContainer r(a.size() + b.size());
    
    auto a_begin = a.begin();
    auto b_begin = b.begin();
    auto r_begin = r.begin();
    
    binary_merge_recursive<IterContainer>(a_begin, b_begin, r_begin, a.size(), b.size());

    return r;
}

int main() {
    std::vector<int> x = {1, 3, 5, 5, 5};
    std::vector<int> y = {2, 4, 6, 7};

    std::cout << "Vector x: \n";
    for (auto & e : x)
        std::cout << e << " ";
    std::cout << std::endl;

    std::cout << "Vector y: \n";
    for (auto & e : y)
        std::cout << e << " ";
    std::cout << std::endl;

    std::vector<int> z = binary_merge(x, y);

    std::cout << "Resulting vector z: \n";
    for (auto & e : z)
        std::cout << e << " ";
    std::cout << std::endl;

    return 0;
}