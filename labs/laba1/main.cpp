#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Structure to represent numbers with uncertainty
struct NumberWithUncertainty
{
    double value;
    double uncertainty;

    // Constructor to create a number with uncertainty
    NumberWithUncertainty(double val, double unc) : value(val), uncertainty(unc) {}
    NumberWithUncertainty() {}
};

// Structure to represent improper fractions
struct ImproperFraction
{
    int whole;       // Whole part of the fraction
    int numerator;   // Numerator
    int denominator; // Denominator
};

// Function to calculate with uncertainty for basic operations: +, -, *, /
NumberWithUncertainty calculateWithUncertainty(const NumberWithUncertainty &a, const NumberWithUncertainty &b, char operation)
{
    NumberWithUncertainty result;

    switch (operation)
    {
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
        if (b.value != 0)
        {
            result.value = a.value / b.value;
            result.uncertainty = fabs(result.value) * sqrt(pow(a.uncertainty / (a.value * a.value), 2) +
                                                           pow(b.uncertainty / (b.value * b.value), 2));
        }
        else
        {
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

// Function to print a number with uncertainty
void printNumberWithUncertainty(const NumberWithUncertainty &number)
{
    cout << number.value << " +/- " << number.uncertainty;
}

// Function to perform Gaussian elimination for regular numbers
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

// Function to perform Gaussian elimination for improper fractions
// Function to perform Gaussian elimination for improper fractions
// Function to perform Gaussian elimination for improper fractions
// Function to perform Gaussian elimination for improper fractions
// Function to perform Gaussian elimination for improper fractions
// Function to perform Gaussian elimination for improper fractions
void gaussianElimination(vector<vector<ImproperFraction>> &matrix)
{
    cout << "Entering gaussianElimination function" << endl;
    int n = matrix.size();

    for (int i = 0; i < n; i++)
    {
        ImproperFraction pivot = matrix[i][i];

        cout << "Pivot element: " << pivot.whole << " " << pivot.numerator << "/" << pivot.denominator << endl;

        for (int j = i; j < n + 1; j++)
        {
            matrix[i][j].whole /= pivot.whole;
            matrix[i][j].numerator /= pivot.numerator;
            matrix[i][j].denominator /= pivot.denominator;
        }

        for (int k = 0; k < n; k++)
        {
            if (k != i)
            {
                ImproperFraction factor = matrix[k][i];
                cout << "Factor element for row " << k + 1 << ": " << factor.whole << " " << factor.numerator << "/" << factor.denominator << endl;
                for (int j = i; j < n + 1; j++)
                {
                    if (pivot.numerator != 0)
                    {
                        matrix[i][j].whole /= pivot.whole;
                        matrix[i][j].numerator /= pivot.numerator;
                        matrix[i][j].denominator /= pivot.denominator;
                    }
                    else
                    {
                        cerr << "Error: Division by zero." << endl;
                        return;
                    }
                }
            }
        }
    }

    cout << "Exiting gaussianElimination function" << endl;
}

// Function to solve the linear system using Gaussian elimination for regular numbers
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

// Function to solve the linear system using Gaussian elimination for improper fractions
vector<ImproperFraction> solveLinearSystem(const vector<vector<ImproperFraction>> &coefficients)
{
    cout << "Entering solveLinearSystem function" << endl;
    int n = coefficients.size();
    vector<vector<ImproperFraction>> matrix = coefficients;
    gaussianElimination(matrix);
    vector<ImproperFraction> solution;
    for (int i = 0; i < n; i++)
    {
        solution.push_back(matrix[i][n]);
    }
    cout << "Solution found: ";
    for (auto &fraction : solution)
    {
        cout << fraction.whole << " " << fraction.numerator << "/" << fraction.denominator << " ";
    }
    cout << endl;
    return solution;
}

// Function to print a regular matrix
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

// Function to print a matrix of improper fractions
void print_matrix(const vector<vector<ImproperFraction>> &matrix)
{
    int n = matrix.size();
    for (int i = 0; i < n; i++)
    {
        cout << endl;
        for (int j = 0; j < matrix[i].size(); j++)
            cout << matrix[i][j].whole << " " << matrix[i][j].numerator << "/" << matrix[i][j].denominator << " ";
    }
    cout << endl;
}

// Function to print the solution of a linear system for regular numbers
void printSolution(const vector<double> &solution)
{
    int n = solution.size();
    cout << "Solution to the system of equations:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "x" << i + 1 << " = " << solution[i] << endl;
    }
}

// Function to print the solution of a linear system for improper fractions
// Function to print the solution of a linear system for improper fractions
void printSolution(const vector<ImproperFraction> &solution)
{
    int n = solution.size();
    cout << "Solution to the system of equations:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "x" << i + 1 << " = " << solution[i].whole << " " << solution[i].numerator << "/" << solution[i].denominator << endl;
    }
}

int main()
{
    char choice;
    cout << "Enter 'n' for regular numbers or 'f' for improper fractions: ";
    cin >> choice;

    if (choice == 'n')
    {
        // Solving linear system with regular numbers
        vector<vector<double>> coefficients;
        // Input matrix from user
        cout << "Enter the coefficients matrix:" << endl;
        // Assuming the matrix is square
        int size;
        cout << "Enter the size of the square matrix: ";
        cin >> size;
        cout << "Enter the coefficients separated by space:" << endl;
        for (int i = 0; i < size; i++)
        {
            vector<double> row;
            for (int j = 0; j < size + 1; j++)
            {
                double num;
                cin >> num;
                row.push_back(num);
            }
            coefficients.push_back(row);
        }

        // Solve the linear system
        vector<double> solution = solveLinearSystem(coefficients);

        // Print the solution
        printSolution(solution);
    }
    else if (choice == 'f')
    {
        // Solving linear system with improper fractions
        vector<vector<ImproperFraction>> coefficients = {
            {{-2, 1, 1}, {1, 1, 1}, {-3, 1, 1}, {-8, 1, 1}},
            {{3, 1, 1}, {1, 1, 1}, {-6, 1, 1}, {-9, 1, 1}},
            {{1, 1, 1}, {1, 1, 1}, {2, 1, 1}, {5, 1, 1}}};
        // Input matrix from user
        // cout << "Enter the coefficients matrix:" << endl;
        // // Assuming the matrix is square
        // // Assuming the matrix is square
        // int size;
        // cout << "Enter the size of the square matrix: ";
        // cin >> size;
        // cout << "Enter coefficients separated by space in the format 'whole numerator/denominator':" << endl;
        // for (int i = 0; i < size; i++)
        // {
        //     vector<ImproperFraction> row;
        //     for (int j = 0; j < size + 1; j++)
        //     {
        //         ImproperFraction fraction;
        //         char slash;
        //         cout << "Enter the coefficient for row " << i + 1 << ", column " << j + 1 << " in the format 'whole numerator/denominator': ";
        //         cin >> fraction.whole >> fraction.numerator >> slash >> fraction.denominator;
        //         row.push_back(fraction);
        //     }
        //     coefficients.push_back(row);
        // }

        // Solve the linear system
        vector<ImproperFraction> solution = solveLinearSystem(coefficients);

        // Print the solution
        printSolution(solution);
    }
    else
    {
        cerr << "Invalid choice. Please enter 'n' or 'f'." << endl;
    }

    return 0;
}
