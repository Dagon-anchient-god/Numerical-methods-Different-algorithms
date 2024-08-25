
#include <iostream>
#include <vector>
using namespace std;

double half(double (*f)(double), double a, double b,double acc)
{
    double c;
    while (abs(a - b) > acc)
    {
        double c = (a + b) / 2;
        if (f(a) * f(c) < 0)
            b = c;
        else
            a = c;
    }
    return (a + b) / 2;
}

double Simple(double (*f)(double), double a, double b, double acc)
{
    double lastsoul = (a + b) / 2;
    double soul = 0;
    double temp;
    while (abs(soul - lastsoul) > acc)
    {
        temp = soul;
        soul = f(lastsoul);
        lastsoul = temp;
    }
    return soul;
}

double Newton(double (*f1)(double), double (*f2)(double), double a, double b, double acc)
{
    double lastsoul = (a + b) / 2;
    double soul = 0;
    double temp;
    while (abs(soul - lastsoul) > acc)
    {
        temp = soul;
        soul = lastsoul - f1(lastsoul) / f2(lastsoul);
        lastsoul = temp;
    }
    return soul;
}

double Split_Ends(double (*f)(double), double a, double b, double acc)
{
    double soul1 = 5;
    double soul2 = 10;
    double soul = 0;
    double temp;
    while (abs(soul - soul1) > acc)
    {
        temp = soul;
        soul = soul1 - (f(soul1) /( f(soul1)- f(soul2))) *(soul1- soul2);
        soul2 = soul1;
        soul1 = temp;
    }
    return soul;
}

double eq_S(double x)
{
    return sqrt(1 - x * log10(x + 2));
}

double eq(double x)
{
    return x* log10(x + 2)+x*x-1;
}

double eq_P(double x)
{
    return log(x+2)/log(10)+x/(log(10)*(x+2)) +2*x;
}

int main()
{
    setlocale(LC_CTYPE, "rus");
    double a = 0;
    double b = 1;
    double c = 1;
    double d = 10;
    double acc = 0.0001;
    double e;
    e = half(*eq, a, b, acc);
    cout <<  "  корень нелинейного уравнения, вычисленный методом половинного деления, равен  " << e << '\n';
    e = Simple(*eq_S, a, b, acc);
    cout << "  корень нелинейного уравнения, вычисленный методом простой итерации, равен  " << e << '\n';
    e = Newton(*eq,*eq_P, c, d, acc);
    cout << "  корень нелинейного уравнения, вычисленный методом Ньютона, равен  " << e << '\n';
    e = Split_Ends(*eq, a, b, acc);
    cout << "  корень нелинейного уравнения, вычисленный методом секущих, равен   " << e << '\n';
    cout << eq(e);
}

