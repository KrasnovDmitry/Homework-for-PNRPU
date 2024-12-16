#include <iostream>
#include <cmath>
#include <iomanip>
#include <clocale>

using std::cout;
using std::endl;
using std::cos;
using std::sin;
using std::fabs;

typedef struct{double a; double b;}Range;

double f0(double x)
{
    return (x-2+sin(1/x));
}
double f1(double x)
{
    return (1 - (cos(1/x) / (x*x)));
}
double f2(double x)
{
    return -(sin(1/x) - 2*x*cos(1/x))/(x*x*x*x);
}
double NewtonFunction(double x, double(*equality)(double), double(*derivity)(double))
{
    return (x - (equality(x)/derivity(x)));
}

double solution(double(*equality)(double), double(*derivity)(double), double(*secondDerivity)(double), Range range, double tolerance = 1e-5, int max_iteration = 1000)
{
    double x0, x1;
    if(secondDerivity(range.a) > 0)
        x1 = range.a;
    else
        x1 = range.b;
    int iterator = 0;
    while(fabs(x1-x0) > tolerance && iterator <= max_iteration)
    {
        iterator++;
        x0 = x1;
        x1 = NewtonFunction(x0, equality, derivity);
        cout << "Итерация №" << iterator << ":\tx0 = " << x0 << "\tx1 = " << x1 << "\te = " << fabs(x1-x0) << endl;
    }
    return x1;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << std::setprecision(10) << std::fixed;
    double result = solution(f0, f1, f2, {1, 2},1e-10);
    return 0;
}
