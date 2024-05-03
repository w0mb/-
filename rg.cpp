#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double *seidel(double **a, double *y, int n, double eps)
{
    // Модификация матрицы для диагонального преобладания
    for (int i = 0; i < n; i++)
    {
        double maxVal = abs(a[i][i]);
        int maxIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (abs(a[j][i]) > maxVal)
            {
                maxVal = abs(a[j][i]);
                maxIndex = j;
            }
        }

        // Обмен строк
        if (maxIndex != i)
        {
            swap(a[i], a[maxIndex]);
            swap(y[i], y[maxIndex]);
        }
    }

    double *x = new double[n];
    double *xNew = new double[n];
    bool exceedEpsilon = false;
    int iterations = 1;

    do
    {
        cout << "Iteration " << iterations << endl;

        for (int i = 0; i < n; i++)
        {
            xNew[i] = y[i];
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                {
                    xNew[i] -= a[i][j] * xNew[j];
                }
            }
            xNew[i] /= a[i][i];
        }

        exceedEpsilon = true;
        for (int i = 0; i < n; i++)
        {
            if (abs(xNew[i] - x[i]) > eps)
            {
                exceedEpsilon = false;
                break;
            }
        }

        // Вывод значений переменных и эпсилона для каждой переменной
        for (int i = 0; i < n; i++)
        {
            cout << "X" << i + 1 << " = " << xNew[i] << " (epsilon = " << xNew[i] - x[i] << ")" << endl;
        }

        for (int i = 0; i < n; i++)
        {
            x[i] = xNew[i];
        }

        iterations++;

    } while (!exceedEpsilon);

    delete[] xNew;

    return x;
}

double *iter(double **a, double *y, int n, double eps)
{
    double *res = new double[n];
    int i, j;
    bool flag = false;

    for (i = 0; i < n; i++)
    {
        res[i] = y[i] / a[i][i];
    }

    double *Xn = new double[n]; // Перенесли инициализацию сюда

    int iteration = 1; // Переменная для отслеживания номера итерации

    // Установим начальные значения Xn в нули перед первой итерацией
    for (i = 0; i < n; i++)
    {
        res[i] = 0;
    }

    do
    {
        cout << "Iteration " << iteration << ":" << endl;
        for (i = 0; i < n; i++)
        {
            Xn[i] = y[i] / a[i][i];
            for (j = 0; j < n; j++)
            {
                if (i == j)
                    continue;
                else
                {
                    Xn[i] -= a[i][j] / a[i][i] * res[j];
                }
            }
            // отключи abs если показывать что epsilon может быть отрицательным
        }

        flag = false;
        for (i = 0; i < n; i++)
        {
            if (abs(Xn[i] - res[i]) < eps)
            {
                flag = true;
                break;
            }
        }
        for (i = 0; i < n; i++)
        {
            cout << "X" << i + 1 << " = " << Xn[i] << " (epsilon = " << (Xn[i] - res[i]) << ")" << endl; // Вывод текущего значения эпсилон
        }

        for (i = 0; i < n; i++)
        {
            res[i] = Xn[i];
        }

        iteration++; // Увеличиваем номер итерации
    } while (!flag);

    return res;
}
int countLines(std::string filename)
{
    std::ifstream file(filename);
    int n = 0;
    std::string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            n++;
        }
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file " << filename << std::endl;
    }

    return n;
}
int main()
{
    std::string filename = "matrix.txt";
    int n = countLines(filename);
    char choice;

    do
    {

        double **a;
        double *y;
        double *x;
        ifstream infile;
        int i, j;
        infile.open("matrix.txt");
        double eps;
        cout << "Enter the value of epsilon: ";
        cin >> eps;

        y = new double[n];
        a = new double *[n];
        for (i = 0; i < n; i++)
        {
            a[i] = new double[n];
        }

        for (i = 0; i < n; i++)
        {
            for (j = 0; j <= n; j++)
            {
                if (j != n)
                {
                    infile >> a[i][j];
                }
                else
                {
                    infile >> y[i];
                }
            }
        }
        infile.close();

        for (i = 0; i < n; i++)
        {
            for (j = 0; j <= n; j++)
            {
                if (j != n)
                {
                    cout << a[i][j] << "\t";
                }
                else
                {
                    cout << y[i] << "\t";
                }
            }
            cout << endl;
        }
        cout << "Enter 'S' to use Simple iterations or 'Z' Zeitzel Method: ";
        cin >> choice;

        if (choice == 'S')
        {
            x = iter(a, y, n, eps);
            cout << "Final result:" << endl;
            for (i = 0; i < n; i++)
            {
                cout << "X" << i + 1 << " = " << x[i] << endl;
            }
        }
        else if (choice == 'Z')
        {
            cout << "The Zeitzel Method" << endl;
            x = seidel(a, y, n, eps);
            cout << "Final result:" << endl;
            for (i = 0; i < n; i++)
            {
                cout << "X" << i + 1 << " = " << x[i] << endl;
            }

            delete[] y;
            for (i = 0; i < n; i++)
            {
                delete[] a[i];
            }
            delete[] a;
            delete[] x;
        }
        else
        {
            cout << "Invalid choice. Please enter 'S' or 'Z' next time." << endl;
        }

        cout << "Press 'E' to exit or any other key to continue: ";
        cin >> choice;

    } while (choice != 'E');
}