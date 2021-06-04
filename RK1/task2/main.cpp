// Copyright 2021 Ilyagu Nagdimaev

#include <iostream>
#include <cassert>

template <typename T>
class Stack {
 private:
    unsigned int size;
    unsigned int capacity;
    T *arr;

    void resize() {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity = capacity * 2;
        }
        T *new_arr = new T[capacity];

        for (int i = 0; i < size; ++i) {
            new_arr[i] = arr[i];
        }

        delete[] arr;
        arr = new_arr;
    }

 public:
    Stack() : size(0), capacity(0), arr(nullptr) {}
    explicit Stack(unsigned int _capacity) : size(0), capacity(_capacity) {
        arr = new T[capacity];
    }
    ~Stack() {
        delete[] arr;
    }

    void push(const T new_element) {
        if (size == capacity) {
            resize();
        }

        arr[size] = new_element;
        size++;
    }

    void pop() {
        assert(!is_empty());
        size--;
    }

    T top() {
        assert(size != 0);
        return arr[size-1];
    }

    unsigned int get_size() {
        return size;
    }
    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << ' ';
        }
        std::cout << std::endl;
    }
    bool is_empty() {
        if (size == 0) {
            return true;
        } else {
            return false;
        }
    }
};

void anagramm(Stack<char> stack, std::string first, std::string second) {
    int i = 0, j = 0, stSize = first.size();
    while (i < stSize && j < stSize) {
        if (!stack.is_empty() && stack.top() == second[j]) {
            stack.pop();
            j++;
        } else {
            stack.push(first[i]);
            i++;
        }
    }

    while (!stack.is_empty()) {
        if (stack.top() == second[j]) {
            stack.pop();
            j++;
        } else {
            break;
        }
    }
    if (stack.is_empty()) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
}

int main() {
    std::string first, second;
    std::cin >> first >> second;
    Stack<char> stack;
    anagramm(stack, first, second);
    return 0;
}
