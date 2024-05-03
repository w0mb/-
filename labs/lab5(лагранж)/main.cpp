#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double factorial(int x) {
    double fact = 1;
    for (int i = 2; i <= x; ++i) {
        fact *= i;
    }
    return fact;
}

double lagrange(vector<double>& x_arr, vector<double>& y_arr, int n, double x) {
    double result = 0.0;
    for (int i = 0; i <= n; ++i) {
        double q = 1.0;
        for (int j = 0; j <= n; ++j) {
            if (i != j) {
                q *= (x - x_arr[j]) / (x_arr[i] - x_arr[j]);
            }
        }
        result += y_arr[i] * q;
    }
    return result;
}


int main() {
    vector<double> x_arr = {1.0, 3.0, 7.0, 5.0, 9.0};
    vector<double> y_arr;
    for (double x : x_arr) {
        y_arr.push_back(sqrt(x));
    }
    
    int n = 5;
    double x = 2.5;

    // Лагранж
    cout << "lagra: " << lagrange(x_arr, y_arr, n, x) << endl;

    return 0;
}
