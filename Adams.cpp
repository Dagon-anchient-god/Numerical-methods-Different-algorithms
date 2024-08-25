// Adams.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
using namespace std;

double K1(double h, double x, double y, double (*f)(double, double))
{
    return h * f(x, y);
}

double K2(double h, double x, double y, double (*f)(double, double))
{
    return h * f(x + 0.5 * h, y + 0.5 * K1(h, x, y, f));
}

double K3(double h, double x, double y, double (*f)(double, double))
{
    return h * f(x + 0.5 * h, y + 0.5 * K2(h, x, y, f));
}

double K4(double h, double x, double y, double (*f)(double, double))
{
    return h * f(x + h, y + K3(h, x, y, f));
}

vector<double> Adams(double x1, double x2, double h, double y0, double (*f)(double, double))
{
    vector<double> dots;
    double x = x1;
    double yi = y0;
    dots.push_back(yi);
    
    for (int i = 0; i < 3; i++)
    {
        yi = yi + (1.0 / 6.0) * (K1(h, x, yi, f) + 2 * K2(h, x, yi, f) + 2 * K3(h, x, yi, f) + K4(h, x, yi, f));
        dots.push_back(yi);
        x += h;
    }
    int i = 3;

    double c = double(h / 24);

    while (x <= x2)
    {
        yi += c * (55 * f(x,dots[i]) - 59 * f(x-h,dots[i - 1]) + 37 * f(x-2*h,dots[i - 2]) - 9 * f(x-3*h,dots[i - 3]));
        dots.push_back(yi);
        x += h;
        i++;
    }
    return dots;
}

double Six(double x, double y)
{
    return  (y*(log(x*y)-1))/x;
}

int main()
{
    double a = 1; double b = 2; double y0 = M_E; double h1 = 0.1; double h2 = 0.01;
    vector<double> x1, x2;

    double x = a;
    std::ofstream out;
    out.open("x1_1.txt");
    if (out.is_open())
    {
        out << x << "\n";
        while (abs(x - b) > h1 / 10)
        {
            x += h1;
            out << x << "\n";
        }
    }
    out.close();

    out.open("x1_2.txt");
    if (out.is_open())
    {
        x = a;
        out << x << "\n";
        while (abs(x - b) > h2 / 10)
        {
            x += h2;
            out << x << "\n";
        }
    }
    out.close();

    vector<double> one_one = Adams(a, b, h1, y0, Six);
    vector<double> one_two = Adams(a, b, h2, y0, Six);

    out.open("y1_1.txt");
    if (out.is_open())
    {
        for (int i = 0; i < size(one_one); i++)
        {
            out << one_one[i] << "\n";
        }
    }
    out.close();

    out.open("y1_2.txt");
    if (out.is_open())
    {
        for (int i = 0; i < size(one_two); i++)
        {
            out << one_two[i] << "\n";
        }
    }
    out.close();
}


