#include <iostream>
#include <cassert>

using namespace std;

template<class T>
bool is_less(const T &l, const T &r) {
    return l < r;
}

template<class T>
int median(const T *arr, const int &l, const int &r, bool (*comp)(const T &l, const T &r)) {
    assert(arr != nullptr);

    int mid = (l + r) / 2;

    if (comp(arr[mid], arr[l])) {
        if (comp(arr[l], arr[r])) {
            return l;
        }
        if (comp(arr[l], arr[mid]))
            return mid;
        else
            return r;
    }

    if (comp(arr[mid], arr[r])) {
        return mid;
    }
    if (comp(arr[r], arr[l]))
        return l;
    else
        return r;
}

template<class T>
int partition(T *arr, const int &l, const int &r, bool (*comp)(const T &l, const T &r)) {
    assert(arr != nullptr);

    int mid = median(arr, l, r, comp);
    swap(arr[mid], arr[r]);

    int i = l;
    int j = l;
    while (j < r) {
        if (arr[r] <= arr[j]) {
            j++;
        } else {
            swap(arr[i], arr[j]);
            i++;
            j++;
        }
    }
    swap(arr[i], arr[r]);
    return i;
//    int mid = median(arr, l, r, comp);
//    std::swap(arr[r], arr[mid]);
//
//    if (r - l == 1){
//        return l;
//    }
//    int pivot = arr[mid];
//    int i = l;
//    int j = i;
//    while(j<r){
//        if (comp(pivot, arr[i]))
//            break;
//        i++;
//        j++;
//    }
//    while(j<r){
//        if(comp(pivot, arr[j])){
//            j++;
//        } else {
//            std::swap( arr[i], arr[j]);
//            i++;
//            j++;
//        }
//    }
//    std::swap( arr[i], arr[r]);
//    return i;
}

template<class T>
T kth_statistics(T *arr, const int &k, const int &size, bool (*comp)(const T &l, const T &r)) {
    assert(arr != nullptr);

    int l = 0;
    int r = size - 1;
    int mid = 0;

    while (true) {
        mid = partition(arr, l, r, comp);

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
    cin >> n >> k;

    int arr[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    cout << kth_statistics(arr, k, n, is_less) << endl;

    return 0;
}
