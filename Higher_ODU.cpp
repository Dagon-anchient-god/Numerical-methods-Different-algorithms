#include <iostream>
#include <vector>
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

double K1(double h, double x, double y, double z, double (*f)(double, double, double))
{
    return h * f(x, y,z);
}

double K2(double h, double x, double y, double z, double (*f)(double, double, double))
{
    return h * f(x + 0.5 * h, y + 0.5 * K1(h, x, y,z, f),z);
}

double K3(double h, double x, double y, double z, double (*f)(double, double, double))
{
    return h * f(x + 0.5 * h, y + 0.5 * K2(h, x, y,z, f),z);
}

double K4(double h, double x, double y, double z, double (*f)(double, double, double))
{
    return h * f(x + h, y + K3(h, x, y,  z, f),z);
}

vector<vector<double>> R_K_H_rank(double x1, double x2, double h, double y0, double z0, double (*f1)(double, double), double (*f2)(double, double,double))
{
    vector<vector<double>> dots(2);
    double x = x1;
    double yi = y0;
    double zi = z0;
    dots[0].push_back(yi);
    dots[1].push_back(zi);

    while (abs(x - x2) >= h / 10)
    {
        yi = yi + (1.0 / 6.0) * (K1(h, x, zi, f1) + 2 * K2(h, x, zi, f1) + 2 * K3(h, x, zi, f1) + K4(h, x, zi, f1));
        dots[0].push_back(yi);
        zi += (1.0 / 6.0) * (K1(h, x, zi,yi, f2) + 2 * K2(h, x, zi, yi, f2) + 2 * K3(h, x, zi, yi, f2) + K4(h, x, zi, yi, f2));
        dots[1].push_back(zi);
        x += h;
    }
    return dots;
}

double Six(double x, double y)
{
    return  y;

}

double Six(double x, double z,double y)
{
    return  (z/x+y/(x*x));

}


int main()
{
    double a = 1; double b = 2; double y0 = 2; double z0 = 4; double h1 = 0.1; double h2 = 0.01;
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

    vector<vector<double>> one_one = R_K_H_rank(a, b, h1, y0,z0, Six,Six);
    vector<vector<double>> one_two = R_K_H_rank(a, b, h2, y0,z0, Six, Six);

    out.open("y1_1.txt");
    if (out.is_open())
    {
        for (int i = 0; i < size(one_one[0]); i++)
        {
            out << one_one[0][i] << "\n";
        }
    }
    out.close();

    out.open("y2_1.txt");
    if (out.is_open())
    {
        for (int i = 0; i < size(one_two[0]); i++)
        {
            out << one_two[0][i] << "\n";
        }
    }
    out.close();

    out.open("y1_2.txt");
    if (out.is_open())
    {
        for (int i = 0; i < size(one_one[1]); i++)
        {
            out << one_one[1][i] << "\n";
        }
    }
    out.close();

    out.open("y2_2.txt");
    if (out.is_open())
    {
        for (int i = 0; i < size(one_two[1]); i++)
        {
            out << one_two[1][i] << "\n";
        }
    }
    out.close();
}

