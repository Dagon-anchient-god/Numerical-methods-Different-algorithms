
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector<double> Euler(double a, double b, double h, double y0, double (*y)(double, double))
{
    vector<double> dots;
    double x = a;
    double yi = y0;
    dots.push_back(yi);
    while (abs(x - b) >= h/10)
    {
        yi += h * y(x, yi);
        dots.push_back(yi);
        x += h;
    }
    return dots;
}

double Six(double x, double y)
{
    return (y * log(abs(x)) + x) / (x * log(abs(x)));
}

vector<double> Euler_Cauchy(double a, double b, double h, double y0, double (*y)(double, double))
{
    vector<double> dots;
    double x = a;
    double yi = y0;
    dots.push_back(yi);
    while (abs(x - b) >= h/10)
    {
        yi += h*0.5 * (y(x, yi)+y(x+h,yi+h* y(x, yi)));
        dots.push_back(yi);
        x += h;
    }
    return dots;
}


int main()
{
    double a = 2; double b = 3; double y0 = -0.733026; double h1 = 0.1; double h2 = 0.01;
    vector<double> x1, x2;

    double x = a;

    vector<double> one_one = Euler(a, b, h1, y0, Six);
    vector<double> one_two = Euler(a, b, h2, y0, Six);

    vector<double> two_one = Euler_Cauchy(a, b, h1, y0, Six);
    vector<double> two_two = Euler_Cauchy(a, b, h2, y0, Six);

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
        while (abs(x-b) > h2/10)
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

    out.open("y2_1.txt");
    if (out.is_open())
    {
        for (int i = 0; i < size(two_one); i++)
        {
            out << two_one[i] << "\n";
        }
    }
    out.close();

    out.open("y2_2.txt");
    if (out.is_open())
    {
        for (int i = 0; i < size(two_two); i++)
        {
            out << two_two[i] << "\n";
        }
    }
    out.close();
   
}

