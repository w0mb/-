#include <iostream>

using namespace std;

double phi(int k, double z, double*x, int n)
{
    int i;
    double res = 1;
    for(i=0;i<k;i++)
    {
        res*=(z-x[i])/(x[k]-x[i]);
    }
    for(i=k+1;i<n;i++)
    {
    res*=(z-x[i])/(x[k]-x[i]);
    }
    return res;
}
double l(double z, double *x, double*y, int n)
{
    double s=0;
    for(int k=0;k<n;k++)
    {
        s+=y[k]*phi(k,z,x,n);
    }
    return s;
}
void line(int m)
{
    for(int k = 1;k<=m;k++)
    {
        cout <<"-";
    }
    cout <<endl;
}
int main()
{
    int k, m = 20;
    const int n = 5;
    double x[n] = {1, 3, 7, 5, 9};
    double y[n] = {0, 2, -1, 1, 3};
    line(m);
    cout << "x\t| l(X)\n";
    line(m);
    for(k=0;k<n;k++)
    {
        cout <<x[k]<<"\t| "<<l(x[k], x, y, n)<<endl;
    }
    double dx=1;
    line(m);
    cout <<"x\t| l(x)\n";
    line(m);
    for(k=0;k<n;k++)
    {
        cout <<x[k]+dx<<"\t| "<<l(x[k]+dx, x, y, n) << endl;
    }
}