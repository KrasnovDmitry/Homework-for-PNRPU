#include <iostream>
#include <iomanip>
#include <cmath>
#include <clocale>
#define DOUBLE_INFINITY 0x9fffffffffffffff

using std::cout;
using std::endl;
using std::cos;
using std::fabs;
using std::sin;

typedef struct{double a; double b;}Range;

double f(double x)
{
    return (2 - sin(1/x));
}

double solution(double(*equality)(double), Range range, double tolerance = 1e-5, double(*derivity)(double) = [](double x){return (cos(1/x)/x*x);}, int max_iteration = 1000)
{
    double x0, x1;
    x0 = DOUBLE_INFINITY;
    if(fabs(derivity(range.a)) < 1)
        x1 = range.a;
    else if(fabs(derivity(range.b)) < 1)
        x1 = range.b;
    int iterator = 0;
    while(fabs(x1-x0) > tolerance && iterator <= max_iteration)
    {
        iterator++;
        x0 = x1;
        x1 = equality(x0);
        cout << "Итерация №" << iterator << ":\tx0 = " << x0 << "\tx1 = " << x1 << "\te = " << fabs(x1-x0) << endl;
    }
    return x1;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    cout << std::setprecision(10) << std::fixed;
    double result = solution(f, {1,2},1e-10);
    cout << "x равен " << result << endl;
    return 0;
}
