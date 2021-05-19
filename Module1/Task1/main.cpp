#include <iostream>

using namespace std;

template <class T>
struct Point {
    T x = 0;
    T y = 0;
};

double area(Point<double> * arr, int n) {
    double sum = 0;
    for(int i = 0; i < n - 1; i++) {
        sum += 0.5 * (arr[i].y + arr[i+1].y) * (arr[i].x - arr[i+1].x);
    }
    return sum;
}

int main() {
    int n = 0;
    cin >> n;
    n++;
    auto * arr  = new Point<double>[n];

    for(int i = 0; i < n-1; i++){
        cin >> arr[i].x >> arr[i].y;
    }
    arr[n-1].x = arr[0].x;
    arr[n-1].y = arr[0].y;

    cout << area(arr,n) <<endl;
    return 0;
}
