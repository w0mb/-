#include <iostream>
#include <cmath>

using namespace std;

#define e 0.00001

double initX();

double f(double x)
{
    return sin(x) + cos(x)/sin(x);
}

void methodNutona()
{
    double lowerBound = -10.0;
    double upperBound = 10.0;

    int steps = 100;

    double stepSize = (upperBound - lowerBound) / steps;

    double initialX = lowerBound;

    while (initialX <= upperBound)
    {
        double value = f(initialX);
        if (value * f(initialX + stepSize) <= 0)
        {
            break; 
        }
        initialX += stepSize;
    }

    int n = 7;
    double dx = 0.00001;
    double x = (int)initialX;

    cout << "num\t   x\t\tf(x)\t\tdf(x)" << endl;
    for (int k = 1; k <= n; k++)
    {
        x = x - f(x) / ((f(x + dx) - f(x)) / dx);

        cout << k << "\t" << -x << "\t" << ((f(x + dx) - f(x)) / dx) << "\t" << f(x) / ((f(x + dx) - f(x)) / dx) << endl;
    }

    cout << "priblizh x: " << (int)initialX << endl;
    cout << "x: " << -x << endl;
}

void methodChord()
{

    double a = -10.00, b = initX();
    double c_p = 0;
    double c = 0;
    bool check = true;
    while (check)
    {
        cout << "a: " << a << "          b: " << b << "     ||     ";
        c = (a * f(b) - b * f(a)) / (f(b) - f(a));
        if (f(a) * f(c) < 0)
        {
            b = c;
        }
        else
        {
            a = c;
        }
        check = (abs(c - c_p) > e);
        cout << "abs(C(n) - C(n-1)): " << abs(c - c_p) << endl;
        if (check)
        {
            c_p = c;
        }
    }
    cout << "otvet: " << c << " ± " << abs(c - c_p) << endl;
}

double initX()
{
    double lowerBound = -10.0;
    double upperBound = 10.0;

    int steps = 1000;

    double stepSize = (upperBound - lowerBound) / steps;


    double initialX = lowerBound;

    while (initialX <= upperBound)
    {
        double value = f(initialX);
        if (value * f(initialX + stepSize) <= 0)
        {
            break; 
        }
        initialX += stepSize;
    }

    return initialX;
}

void methodPD()
{
    double a = -10.00, b = initX();
    while (abs(b - a) > e)
    {
        cout << "a: " << a << "          b: " << b << "     ||     abs(b - a): " << abs(b - a) << endl;
        double c = (a + b) / 2;
        if (f(a) * f(c) < 0)
        {
            b = c;
        }
        else
        {
            a = c;
        }
    }
    cout << "a: " << a << "          b: " << b << "     ||     abs(b - a): " << abs(b - a) << endl;

    cout << "otvet: " << (a + b) / 2 << " ± " << abs(b - a) / 2 << endl;
}

int main()
{
    cout << "choise method" << endl;
    cout << "1 - method Nutona" << endl;
    cout << "2 - method polovinnogo deleniya" << endl;
    cout << "3 - metod chord" << endl;

    int choice;

    cin >> choice;

    switch (choice)
    {
    case 1:
        methodNutona();
        break;
    case 2:
        methodPD();
        break;
    case 3:
        methodChord();
        break;
    default:
        cout << endl
             << "invaild choice";
        break;
    }

    return 0;
}
