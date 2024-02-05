#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct NumberWithUncertainty {
    double value;
    double uncertainty;

    NumberWithUncertainty(double val, double unc) : value(val), uncertainty(unc) {}
    NumberWithUncertainty() {}

    NumberWithUncertainty calculate(const NumberWithUncertainty &b, char operation) const {
        NumberWithUncertainty result;

        switch (operation) {
            case '+':
                result.value = value + b.value;
                result.uncertainty = sqrt(pow(uncertainty, 2) + pow(b.uncertainty, 2));
                break;
            case '-':
                result.value = value - b.value;
                result.uncertainty = sqrt(pow(uncertainty, 2) + pow(b.uncertainty, 2));
                break;
            case '*':
                result.value = value * b.value;
                result.uncertainty = fabs(result.value) * sqrt(pow(uncertainty / value, 2) + pow(b.uncertainty / b.value, 2));
                break;
            case '/':
                if (b.value != 0) {
                    result.value = value / b.value;
                    result.uncertainty = fabs(result.value) * sqrt(pow(uncertainty / (value * value), 2) +
                                                                   pow(b.uncertainty / (b.value * b.value), 2));
                } else {
                    cerr << "Error: Division by zero." << endl;
                    result.value = NAN;
                    result.uncertainty = NAN;
                }
                break;
            default:
                cerr << "Error: Unsupported operation." << endl;
                result.value = NAN;
                result.uncertainty = NAN;
                break;
        }

        return result;
    }

    void print() const {
        cout << value << " +/- " << uncertainty;
    }
};

class NumberOperation {
public:
    NumberOperation(double val1, double unc1, double val2, double unc2) : num1(val1, unc1), num2(val2, unc2) {}

    void performOperations() {
        add();
        subtract();
        multiply();
        divide();
    }

private:
    NumberWithUncertainty num1;
    NumberWithUncertainty num2;

    void add() const {
        NumberWithUncertainty result = num1.calculate(num2, '+');
        cout << "Addition: ";
        result.print();
        cout << endl;
    }

    void subtract() const {
        NumberWithUncertainty result = num1.calculate(num2, '-');
        cout << "Subtraction: ";
        result.print();
        cout << endl;
    }

    void multiply() const {
        NumberWithUncertainty result = num1.calculate(num2, '*');
        cout << "Multiplication: ";
        result.print();
        cout << endl;
    }

    void divide() const {
        NumberWithUncertainty result = num1.calculate(num2, '/');
        cout << "Division: ";
        result.print();
        cout << endl;
    }
};

class MatrixSolver {
public:
    MatrixSolver(const vector<vector<double>> &coefficients) : matrix(coefficients) {}

    void solve() {
        gaussianElimination();
    }

    void printSolution() const {
        cout << "Solution to the system of equations:" << endl;
        for (size_t i = 0; i < solution.size(); ++i) {
            cout << "x" << i + 1 << " = " << solution[i] << endl;
        }
    }

    void printMatrix() const {
        cout << "Matrix after Gaussian elimination:" << endl;
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void solveModifiedGauss() {
        vector<vector<double>> modifiedMatrix = matrix;  // Create a copy of the original matrix

        // Apply the modified Gaussian elimination
        modifiedGaussianElimination(modifiedMatrix);

        // Extract the solution from the modified matrix
        vector<double> modifiedSolution;
        for (size_t i = 0; i < modifiedMatrix.size(); ++i) {
            modifiedSolution.push_back(modifiedMatrix[i].back());
        }

        // Print the solution from the modified method
        cout << "\nSolution using Modified Gaussian Elimination:" << endl;
        for (size_t i = 0; i < modifiedSolution.size(); ++i) {
            cout << "x" << i + 1 << " = " << modifiedSolution[i] << endl;
        }
    }

private:
    vector<vector<double>> matrix;
    vector<double> solution;

    void gaussianElimination() {
        int n = matrix.size();

        for (int i = 0; i < n; i++) {
            double pivot = matrix[i][i];

            for (int j = i; j < n + 1; j++)
                matrix[i][j] /= pivot;

            for (int k = 0; k < n; k++) {
                if (k != i) {
                    double factor = matrix[k][i];
                    for (int j = i; j < n + 1; j++)
                        matrix[k][j] -= factor * matrix[i][j];
                }
            }
        }

        extractSolution();
    }

    void extractSolution() {
        int n = matrix.size();
        for (int i = 0; i < n; i++) {
            solution.push_back(matrix[i][n]);
        }
    }

    // Function to perform modified Gaussian elimination
    void modifiedGaussianElimination(vector<vector<double>> &matrix) {
        int n = matrix.size();

        for (int i = 0; i < n; i++) {
            // Find the maximum element below the current row in the current column
            double maxElement = abs(matrix[i][i]);
            int maxRow = i;
            for (int k = i + 1; k < n; k++) {
                if (abs(matrix[k][i]) > maxElement) {
                    maxElement = abs(matrix[k][i]);
                    maxRow = k;
                }
            }

            // Swap the rows to move the maximum element to the diagonal
            swapRows(matrix, i, maxRow);

            double pivot = matrix[i][i];

            for (int j = i; j < n + 1; j++)
                matrix[i][j] /= pivot;

            for (int k = 0; k < n; k++) {
                if (k != i) {
                    double factor = matrix[k][i];
                    for (int j = i; j < n + 1; j++)
                        matrix[k][j] -= factor * matrix[i][j];
                }
            }
        }
    }

    // Function to swap rows in a matrix
    void swapRows(vector<vector<double>> &matrix, int row1, int row2) {
        for (size_t i = 0; i < matrix[row1].size(); ++i) {
            swap(matrix[row1][i], matrix[row2][i]);
        }
    }
};

int main() {
    // Example system of linear equations
    vector<vector<double>> coefficients = {
        {-2, 1, -3, -8},
        {3, 1, -6, -9},
        {1, 1, 2, 5}};

    // Solve the linear system using the standard Gaussian elimination method
    MatrixSolver matrixSolver(coefficients);
    matrixSolver.solve();
    cout << "Solution using Gaussian Elimination:" << endl;
    matrixSolver.printSolution();

    // Solve the linear system using the modified Gaussian elimination method
    matrixSolver.solveModifiedGauss();
    matrixSolver.printMatrix();
    // Example operations with numbers and uncertainties
    NumberOperation numberOperation(2.384, 0.021, 9.485, 0.014);
    numberOperation.performOperations();

    return 0;
}
