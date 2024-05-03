#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct NumberWithUncertainty {
    double value;
    double uncertainty;
    NumberWithUncertainty(double val, double unc) : value(val), uncertainty(unc) {}
    NumberWithUncertainty(){}
};

NumberWithUncertainty calculateWithUncertainty(const NumberWithUncertainty &a, const NumberWithUncertainty &b, char operation) {
    NumberWithUncertainty result;

    switch (operation) {
        case '+':
            result.value = a.value + b.value;
            result.uncertainty = sqrt(pow(a.uncertainty, 2) + pow(b.uncertainty, 2));
            break;
        case '-':
            result.value = a.value - b.value;
            result.uncertainty = sqrt(pow(a.uncertainty, 2) + pow(b.uncertainty, 2));
            break;
        case '*':
            result.value = a.value * b.value;
            result.uncertainty = fabs(result.value) * sqrt(pow(a.uncertainty / a.value, 2) + pow(b.uncertainty / b.value, 2));
            break;
        case '/':
            if (b.value != 0) {
                result.value = a.value / b.value;
                result.uncertainty = fabs(result.value) * sqrt(pow(a.uncertainty / (a.value * a.value), 2) +
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

void printNumberWithUncertainty(const NumberWithUncertainty &number) {
    cout << number.value << " +/- " << number.uncertainty;
}

void gaussianElimination(vector<vector<double>> &matrix)
{
    int n = matrix.size();

    for (int i = 0; i < n; i++)
    {
        double pivot = matrix[i][i];

        for (int j = i; j < n + 1; j++)
            matrix[i][j] /= pivot;

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

vector<double> solveLinearSystem(const vector<vector<double>> &coefficients)
{
    int n = coefficients.size();

    vector<vector<double>> matrix = coefficients;

    gaussianElimination(matrix);

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

template <>
void printSolution(const vector<double> &solution) {
    int n = solution.size();
    cout << "Solution to the system of equations:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << solution[i] << endl;
    }
}

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
    vector<vector<double>> coefficients = {
        {-2, 1, -3, -8},
        {3, 1, -6, -9},
        {1, 1, 2, 5}};

    vector<double> solution = solveLinearSystem(coefficients);
    gaussianElimination(coefficients);
    print_matrix(coefficients);
    printSolution(solution);
    cout << endl;
    printSolution(coefficients);

//--------------------------------------------------------------------------------------------------------//
    NumberWithUncertainty a(2.384, 0.021);
    NumberWithUncertainty b(9.485, 0.014);

    NumberWithUncertainty resultAdd = calculateWithUncertainty(a, b, '+');
    NumberWithUncertainty resultSubtract = calculateWithUncertainty(a, b, '-');
    NumberWithUncertainty resultMultiply = calculateWithUncertainty(a, b, '*');
    NumberWithUncertainty resultDivide = calculateWithUncertainty(a, b, '/');

    cout << "Addition: ";
    printNumberWithUncertainty(resultAdd);
    cout << endl;

    cout << "Subtraction: ";
    printNumberWithUncertainty(resultSubtract);
    cout << endl;

    cout << "Multiplication: ";
    printNumberWithUncertainty(resultMultiply);
    cout << endl;

    cout << "Division: ";
    printNumberWithUncertainty(resultDivide);
    cout << endl;


    return 0;
}