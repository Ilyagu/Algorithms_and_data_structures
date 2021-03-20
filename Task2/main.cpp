#include <iostream>
#include <random>

using namespace std;


template <class T>
int binary_search(T *arr, T key, int left, int right) {
    while (right - left > 1) {
        int mid = (left + right) / 2;
        if (arr[mid] < key) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if ((key - arr[left]) <= (arr[right] - key)) return left;
    else return right;
}

template <class T>
int exponential_search(T *arr, int size, T key) {
    if (size == 1) return 0;
    int bound = 1;
    while (bound < size && arr[bound] < key) {
        bound *= 2;
    }

    return binary_search(arr, key, (bound == 1) ? 0 : bound / 2, (bound < size) ? bound : size - 1 );
}

int * input_array(int * len) {
    cin >> *len;
    int * arr = new int[*len];
    for (int i = 0; i < *len; ++i) {
        cin >> arr[i];
    }
    return arr;
}

int main() {
    int len1 = 0;
    int len2 = 0;

    int * A = input_array(&len1);
    int * B = input_array(&len2);

    for (int i = 0; i < len2; ++i) {
        cout << exponential_search(A, len1, B[i]) << " ";
    }

    delete [] A;
    delete [] B;

    return 0;
}