#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to perform Gaussian elimination
void gaussianElimination(vector<vector<double>> &matrix)
{
    int n = matrix.size();

    for (int i = 0; i < n; i++)
    {
        // Pivot element
        double pivot = matrix[i][i];

        // Make the diagonal element 1
        for (int j = i; j < n + 1; j++)
            matrix[i][j] /= pivot;

        // Make the other rows 0
        for (int k = 0; k < n; k++)
        {
            if (k != i)
            {
                double factor = matrix[k][i];
                for (int j = i; j < n + 1; j++)
                    matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }
}

// Function to solve the linear system using the modified Gaussian elimination method
vector<double> solveLinearSystem(const vector<vector<double>> &coefficients)
{
    int n = coefficients.size();

    // Create a copy of the coefficients matrix to avoid modifying the original
    vector<vector<double>> matrix = coefficients;

    // Apply Gaussian elimination
    gaussianElimination(matrix);

    // Extract the solution from the augmented matrix
    vector<double> solution;
    for (int i = 0; i < n; i++)
    {
        solution.push_back(matrix[i][n]);
    }

    return solution;
}

void print_matrix(const vector<vector<double>> &matrix)
{
    int n = matrix.size();

    for (int i = 0; i < n; i++)
    {
        cout << endl;
        for (int j = 0; j < matrix[i].size(); j++)
            cout << matrix[i][j] << " ";
    }
    cout << endl;
}

template <typename T>
void printSolution(const T &solution);

// Specialization for vector<double>
template <>
void printSolution(const vector<double> &solution) {
    int n = solution.size();
    cout << "Solution to the system of equations:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << solution[i] << endl;
    }
}

// Specialization for vector<vector<double>>
template <>
void printSolution(const vector<vector<double>> &solution) {
    int n = solution.size();
    cout << "Solution to the system of equations:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << solution[i][n] << endl;
    }
}

int main()
{
    // Example system of linear equations
    vector<vector<double>> coefficients = {
        {-2, 1, -3, -8},
        {3, 1, -6, -9},
        {1, 1, 2, 5}};

    // Solve the linear system
    vector<double> solution = solveLinearSystem(coefficients);
    gaussianElimination(coefficients);
    print_matrix(coefficients);
    // Printing the solution
    printSolution(solution);
    cout << endl;
    printSolution(coefficients);

    return 0;
}
