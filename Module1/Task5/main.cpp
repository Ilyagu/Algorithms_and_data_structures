// Copyright 2021 Ilyagu Nagdimaev

#include <iostream>

#define YG 18
#define OG 80

template<class T>
struct human {
    T day;
    T month;
    T year;
    bool type;
};

bool comp_pair(const human<int> &l, const human<int> &r) {
    return l.year < r.year ||
           l.year == r.year && l.month < r.month ||
           l.year == r.year && l.month == r.month && l.day < r.day ||
           l.year == r.year && l.month == r.month && l.day == r.day && l.type > r.type;
}

template<class T>
void merge(T* A, int p, int q, int r, bool (*comp)(const T &l, const T &r)) {
    int n1, n2, i, j, k;
    n1 = q - p + 1;
    n2 = r - q;
    T * L = new T[n1];
    T * R = new T[n2];
    for (i = 0; i < n1; i++) {
        L[i] = A[p + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = A[q + j + 1];
    }
    i = 0, j = 0;
    for (k = p; i < n1 && j < n2; k++) {
        if (comp(L[i], R[j])) {
            A[k] = L[i++];
        } else {
            A[k] = R[j++];
        }
    }
    while (i < n1) {
        A[k++] = L[i++];
    }
    while (j < n2) {
        A[k++] = R[j++];
    }

    delete[] L;
    delete[] R;
}

template<class T>
void merge_sort(T* A, int p, int r, bool (*comp)(const T &l, const T &r)) {
    int q;
    if (p < r) {
        q = (p + r) / 2;
        merge_sort(A, p, q, comp);
        merge_sort(A, q + 1, r, comp);
        merge(A, p, q, r, comp);
    }
}

template<class T>
bool younger(const human<T> &born, const human<T> &dead) {
    if (dead.year > born.year) {
        return true;
    } else if (dead.year < born.year) {
        return false;
    } else if (dead.month < born.month) {
        return false;
    } else if (dead.month > born.month) {
        return true;
    } else if (dead.day <= born.day) {
        return false;
    } else {
        return true;
    }
}

int solve(human<int> *humans, int n) {
    int max = 0;
    int cur = 0;

    merge_sort(humans, 0, n - 1, comp_pair);

    for (int i = 0; i < n; i++) {
        if (humans[i].type) {
            if (cur > max) max = cur;
            cur--;
        } else {
            if (cur > max) max = cur;
            cur++;
        }
    }

    if (cur > max)
        return cur;
    else
        return max;
}

int main() {
    int n = 0;
    std::cin >> n;
    n *= 2;

    human<int> humans[n];

    int i = 0;
    while (i < n) {
        std::cin >> humans[i].day >> humans[i].month >> humans[i].year >> humans[i + 1].day
            >> humans[i + 1].month >> humans[i + 1].year;
        humans[i].type = false;
        humans[i + 1].type = true;
        if (humans[i + 1].year - humans[i].year > OG) {
            humans[i + 1].year = humans[i].year + OG;
            humans[i + 1].month = humans[i].month;
            humans[i + 1].day = humans[i].day;
        } else if (humans[i + 1].year - humans[i].year == OG && humans[i + 1].month > humans[i].month) {
            humans[i + 1].month = humans[i].month;
            humans[i + 1].day = humans[i].day;
        } else if (humans[i + 1].year - humans[i].year == OG && humans[i + 1].month == humans[i].month &&
                   humans[i + 1].day > humans[i].day) {
            humans[i + 1].day = humans[i].day;
        }
        humans[i].year += YG;
        if (younger(humans[i], humans[i + 1])) {
            i += 2;
        } else {
            n = n - 2;
        }
    }

    std::cout << solve(humans, n) << std::endl;

    return 0;
}
