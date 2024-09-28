#include <algorithm>
#include <iostream>
#include <vector>
#include <list>


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

template <typename IterContainer>
int get_amount_of_comptassions(IterContainer& arr) {
    return std::floor( std::log2(arr.size())) + 1;
}


int main() {
    // Example using std::vector
    std::vector<int> vec = {1, 3, 5, 7, 9};

    int vec_amount_of_comprassions = get_amount_of_comptassions(vec);
    std::cout << "Expected amount of comprassions: " << vec_amount_of_comprassions << std::endl;

    binary_insertion(vec, 4);
    std::cout << "Vector after insertion: ";
    for (const auto& v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    // Example using std::list
    std::list<int> lst =  {1, 3, 5, 7, 9};
    
    int list_amount_of_comprassions = get_amount_of_comptassions(lst);
    std::cout << "Expected amount of comprassions: " << list_amount_of_comprassions << std::endl;

    binary_insertion(lst, 4);
    std::cout << "List after insertion: ";
    for (const auto& l : lst) {
        std::cout << l << " ";
    }
    std::cout << std::endl;

    return 0;
}