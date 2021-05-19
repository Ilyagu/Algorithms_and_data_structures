#include <iostream>

using namespace std;

#define BYTE_IN_MEMBER 8
#define NUMBER_OF_BITS 256

uint8_t get_byte(uint64_t number, int digit) {
    return (number >> (digit * BYTE_IN_MEMBER)) & 0xFF;
}

void lsd_sort(uint64_t *arr, ssize_t size) {
    for (int digit = 0; digit < BYTE_IN_MEMBER; ++digit) {
        int *counts = new int[NUMBER_OF_BITS];
        for (int i = 0; i < NUMBER_OF_BITS; i++)
            counts[i] = 0;

        for (ssize_t i = 0; i < size; ++i) {
            uint8_t byte = get_byte(arr[i], digit);
            counts[byte]++;
        }

        for (int i = 1; i < NUMBER_OF_BITS; ++i) {
            counts[i] += counts[i - 1];
        }

        auto *temp_arr = new uint64_t[size];
        for (ssize_t i = size - 1; i >= 0; --i) {
            uint8_t byte = get_byte(arr[i], digit);
            counts[byte]--;
            temp_arr[counts[byte]] = arr[i];
        }

        for (ssize_t i = 0; i < size; ++i) {
            arr[i] = temp_arr[i];
        }

        delete [] temp_arr;
        delete [] counts;
    }
}

int main() {

    ssize_t n = 0;
    std::cin >> n;
    auto * arr = new uint64_t[n];

    for (ssize_t i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    lsd_sort(arr, n);

    for (ssize_t i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete [] arr;
    return 0;
}
