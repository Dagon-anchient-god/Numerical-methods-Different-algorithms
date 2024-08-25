// Runge-Kutty.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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
    return h * f(x+0.5*h, y+0.5*K1(h,x,y,f));
}

double K3(double h, double x, double y, double (*f)(double, double))
{
    return h * f(x + 0.5 * h, y + 0.5 * K2(h, x, y, f));
}

double K4(double h, double x, double y, double (*f)(double, double))
{
    return h * f(x +h, y + K3(h, x, y, f));
}


vector<double> R_K_rank_4(  double x1, double x2, double h, double y0, double (*f)(double, double))
{
    vector<double> dots;
    double x = x1;
    double yi = y0;
    dots.push_back(yi);

    while (abs(x - x2) >= h / 10)
    {
        yi = yi+ (1.0 / 6.0) * (K1(h, x, yi, f) + 2 * K2(h, x, yi, f) + 2 * K3(h, x, yi, f) + K4(h, x, yi, f));
        dots.push_back(yi);
        x += h;
    }
    return dots;
}

double Six(double x, double y)
{
    double a = y / x;
    return  ( - a * a - a - 1);

}

int main()
{
    double a = 1; double b = 2; double y0 = 2.71828; double h1 = 0.1; double h2 = 0.01;
    vector<double> x1, x2;


    double x = a;
 
    vector<double> one_one = R_K_rank_4(a, b, h1, y0, Six);
    vector<double> one_two = R_K_rank_4(a, b, h2, y0, Six);

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
        while (abs(x - b) > h2/10)
        {
            x += h2;
            out << x << "\n";
        }
    }
    out.close();

    out.open("y1_1.txt");
    if (out.is_open())
    {
        for (int i = 0; i < size(one_one); i++)
        {
            out << one_one[i] << "\n";
            cout << one_one[i] << "\n";
        }
    }
    out.close();

    out.open("y1_2.txt");
    if (out.is_open())
    {
        for (int i = 0; i < size(one_two); i++)
        {
            out << one_two[i] << "\n";
            cout << one_two[i] << "\n";
        }
    }
    out.close();
}

