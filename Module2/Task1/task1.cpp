// Copyright 2021 Ilyagu Nagdimaev

#include <iostream>
#include <vector>
#include <utility>

#define DEFAULT_SIZE 8
#define COEFFICIENT 0.75

struct HashFunction1 {
    size_t operator()(const std::string& str) const {
        size_t hash = 0;

        for (char i : str) {
            hash = hash * 11 + i;
        }
        return hash;
    }
};
struct HashFunction2 {
    size_t operator()(const std::string& str) const {
        size_t hash = 0;

        for (char i : str) {
            hash = hash * 17 + i;
        }
        return 2 * hash + 1;
    }
};

template <class T, class THash1 = HashFunction1, class THash2 = HashFunction2>
class HashTable {
    struct Node {
        Node() : state(true) {}

        explicit Node(T& _value) : value(_value) {}
        T value;
        bool state = false;
    };
    std::vector<Node> buckets;
    int full_cells;
    void grow() {
        std::vector<Node> temp_buckets = std::move(buckets);
        buckets.resize(temp_buckets.capacity() * 2);
        full_cells = 0;

        for (const auto &it : temp_buckets) {
            if (it.state  == false)
                add(it.value);
        }
    }

 public:
    HashTable():
        buckets(DEFAULT_SIZE),
        full_cells(0) {}
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    HashTable(HashTable&&) = delete;
    HashTable& operator=(HashTable&&) = delete;
    ~HashTable() = default;

    bool add(const T& value, const THash1& hash1 = THash1(),
             const THash2& hash2 = THash2()) {
        if (full_cells + 1 >  static_cast<int>(COEFFICIENT * buckets.size()))
            grow();
        size_t h1 = hash1(value);
        size_t h2 = hash2(value);
        if (find(value) == true)
            return false;
        for (int i = 0; i < buckets.size(); i++) {
            int current_hash = (h1 + i * h2) % buckets.capacity();
            if (buckets[current_hash].state == true) {
                buckets[current_hash].value = value;
                buckets[current_hash].state = false;
                full_cells++;
                return true;
            }
        }
        return false;
    }
    bool find(const T& value, const THash1& hash1 = THash1(),
              const THash2& hash2 = THash2()) {
        size_t h1 = hash1(value);
        size_t h2 = hash2(value);
        for (int i = 0; i < buckets.size(); i++) {
            int current_hash = (h1 + i * h2) % buckets.capacity();
            if (buckets[current_hash].value == value &&
                buckets[current_hash].state == false)
                return true;
            else if (buckets[current_hash].value.size() == 0
                    && buckets[current_hash].state == true)
                return false;
        }
        return false;
    }
    bool erase(const T& value, const THash1& hash1 = THash1(),
                const THash2& hash2 = THash2()) {
        if (find(value)) {
            size_t h1 = hash1(value);
            size_t h2 = hash2(value);

            for (size_t i = 0; i != buckets.capacity(); ++i) {
                int current_hash = (h1 + i * h2) % buckets.capacity();
                if (buckets[current_hash].value == value &&
                    buckets[current_hash].state == false) {
                    buckets[current_hash].state = true;
                    full_cells--;
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    std::string value;
    bool result;
    char command = '\0';

    HashTable<std::string, HashFunction1, HashFunction2> hash_table;
    while (std::cin >> command >> value) {
        switch (command) {
            case '+':
                result = hash_table.add(value);
                break;
            case '-':
                result = hash_table.erase(value);
                break;
            case '?':
                result = hash_table.find(value);
                break;
            default:
                return 1;
        }
        if (result) {
            std::cout << "OK" << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
        }
    }

    return 0;
}
