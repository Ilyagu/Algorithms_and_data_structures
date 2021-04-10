#include <iostream>

using namespace std;

static const int byte_in_number = 8;
static const int number_of_bits = 256;

static inline uint8_t get_byte(uint64_t num, int rank) {
    return (num >> (rank * byte_in_number)) & 0xFF;
}

void lsd_sort(uint64_t *arr, ssize_t size) {
    for (int rank = 0; rank < byte_in_number; ++rank) {
        auto *counters = new int[number_of_bits];
        fill_n(counters, number_of_bits, 0);

        for (ssize_t i = 0; i < size; ++i) {
            uint8_t index = get_byte(arr[i], rank);
            counters[index]++;
        }

        for (int i = 1; i < number_of_bits; ++i) {
            counters[i] += counters[i - 1];
        }

        auto *tmp_arr = new uint64_t[size];
        for (ssize_t i = size - 1; i >= 0; --i) {
            uint8_t index = get_byte(arr[i], rank);
            tmp_arr[--counters[index]] = arr[i];
        }

        for (ssize_t i = 0; i < size; ++i) {
            arr[i] = tmp_arr[i];
        }

        delete [] tmp_arr;
        delete [] counters;
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
