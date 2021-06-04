// Copyright 2021 Ilyagu Nagdimaev

#include <iostream>

template <class T>
int binary_search(T *arr, T key, int left, int right) {
    while (left < right) {
        int mid = (left + right) / 2;
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}

template <class T>
int exponential_search(T *arr, int size, T key) {
    int bound = 1;
    while (bound < size && arr[bound] < key) {
        bound *= 2;
    }

    return binary_search(arr, key, (bound == 1) ? 0 : bound/2, (bound < size) ? bound : size);
}

int * input_array(int * len) {
    std::cin >> *len;
    int * arr = new int[*len];
    for (int i = 0; i < *len; ++i) {
        std::cin >> arr[i];
    }
    return arr;
}

int main() {
    int len1 = 0;
    int len2 = 0;

    int * A = input_array(&len1);
    int k = 0;
    std::cin >> k;


    std::cout << exponential_search(A, len1, k) << " ";

    delete [] A;

    return 0;
}
