#include<iostream>
#include<vector>

using namespace std;

// Function to perform Gaussian elimination
void gaussianElimination(vector<vector<double>>& matrix) {
    int n = matrix.size();

    for (int i = 0; i < n; i++) {
        // Pivot element
        double pivot = matrix[i][i];

        // Make the diagonal element 1
        for (int j = i; j < n + 1; j++)
            matrix[i][j] /= pivot;

        // Make the other rows 0
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = i; j < n + 1; j++)
                    matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }
}

// Function to print the solution
void printSolution(const vector<vector<double>>& matrix) {
    int n = matrix.size();
    cout << "Solution to the system of equations:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << matrix[i][n] << endl;
    }   
}

int main() {
    // Example system of linear equations
    vector<vector<double>> coefficients = {
        {-2, 1, -3, -8},
        {3, 1, -6, -9},
        {1, 1, 2, 5}
    };

    // Applying Gaussian elimination
    gaussianElimination(coefficients);

    // Printing the solution
    printSolution(coefficients);

    return 0;
}
