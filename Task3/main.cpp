#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
class Stack {
private:
    unsigned int size;
    unsigned int capacity;
    T *arr;

    void resize() {
        if (capacity == 0) capacity = 1;
        else capacity = capacity * 2;
        T *new_arr = new T[capacity];

        for (int i = 0; i < size; ++i) {
            new_arr[i] = arr[i];
        }

        delete[] arr;
        arr = new_arr;
    }

public:
    Stack() : size(0), capacity(0), arr(nullptr) {}
    Stack(unsigned int _capacity)
    : size(0), capacity(_capacity) {
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

    unsigned short int pop() {
        if (is_empty()) return 1;
        size--;
        return 0;
    }

    T top() {
        assert(size != 0);
        return arr[size-1];
    }

    unsigned int get_size() {
        return size;
    }
    void print() {
        for(int i = 0; i < size; i++) {
            cout << arr[i] << ' ';
        }
        cout << endl;
    }
    bool is_empty() {
        if (size == 0) return true;
        else return false;
    }
};

template <typename T>
class Queue {
private:
    Stack<int> stackIn;
    Stack<int> stackOut;
    unsigned int size;

    void trans() {
        while(!stackIn.is_empty()) {
            stackOut.push(stackIn.top());
            stackIn.pop();
        }
    }
public:
    Queue() : size(0), stackIn(), stackOut(){}
    ~Queue() = default;

    void push_back(const T new_element) {
        stackIn.push(new_element);
    }

    void pop() {
        if (stackOut.is_empty()) trans();
        stackOut.pop();
    }

    T top() {
        if (stackOut.is_empty())
            trans();
        return stackOut.top();
    }

    bool is_empty() {
        if (stackIn.is_empty() && stackOut.is_empty())
            return true;
        else return false;
    }

    unsigned int get_size() {
        return stackOut.get_size() + stackIn.get_size();
    }
};

int main() {
    int n;
    cin >> n;
    Queue<int> queue;
    for (int i = 0; i < n; ++i) {
        unsigned short func = 0;
        int el;
        cin >> func >> el;
        switch (func) {
            case 3:
                queue.push_back(el);
                break;
            case 2:
                if (queue.is_empty() && el != -1) {
                    cout << "NO";
                    return 0;
                } else if (!queue.is_empty() && queue.top() != el) {
                    cout << "NO";
                    return 0;
                } else {
                    queue.pop();
                }
                break;
            default:
                cout << "ERROR";
                return 0;
        }
    }
    cout << "YES";
    return 0;
}
