// Copyright 2021 Ilyagu Nagdimaev

#include <iostream>
#include <cassert>

template<class T>
bool is_less(const T &l, const T &r) {
    return l <= r;
}

template<class T>
int median(const T *arr, const int &l, const int &r) {
    assert(arr != nullptr);

    int mid = (l + r) / 2;

    if (l > r) {
        if (mid > l)
            return l;
        return (r > mid) ? r : mid;
    }
    if (mid > r)
        return r;
    return (l > mid) ? l : mid;
}

template<class T>
int partition(T *arr, const int &l, const int &r,
              bool (*comp)(const T &l, const T &r)) {
    assert(arr != nullptr);

    int mid = median(arr, l, r);
    std::swap(arr[mid], arr[r]);

    int i = l;
    int j = l;
    while (j < r) {
        if (comp(arr[r], arr[i]))
            break;
        i++;
        j++;
    }
    while (j < r) {
        if (comp(arr[r], arr[j])) {
            j++;
        } else {
            std::swap(arr[i], arr[j]);
            i++;
            j++;
        }
    }
    std::swap(arr[i], arr[r]);
    return i;
}

template<class T>
T kth_statistics(T *arr, const int &k, const int &size,
                 bool (*comp)(const T &l, const T &r)) {
    assert(arr != nullptr);

    int l = 0;
    int r = size - 1;

    while (true) {
        int mid = partition(arr, l, r, comp);

        if (k == mid)
            return arr[mid];
        else if (k < mid)
            r = mid;
        else
            l = mid + 1;
    }
}

int main() {
    int n;
    int k;
    std::cin >> n >> k;

    int *arr = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    std::cout << kth_statistics(arr, k, n, is_less) << std::endl;

    delete[] arr;
    return 0;
}
