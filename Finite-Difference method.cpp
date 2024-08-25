
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

vector<double> Progonka(vector<vector <double>> coef, vector<double> res)
{
    vector<double> P(res.size());
    vector<double> Q(res.size());
    vector<double> ans(res.size());
    P[0] = -(coef[0][2] / coef[0][1]);
    Q[0] = (res[0] / coef[0][1]);
    P[res.size() - 1] = 0;
    for (int i = 1; i < res.size() - 1; i++)
    {
        P[i] = -(coef[i][2] / (coef[i][1] + coef[i][0] * P[i - 1]));
        Q[i] = (res[i] - coef[i][0] * Q[i - 1]) / (coef[i][1] + coef[i][0] * P[i - 1]);
    }
    Q[res.size() - 1] = (res[res.size() - 1] - coef[res.size() - 1][0] * Q[res.size() - 2]) / (coef[res.size() - 1][1] + coef[res.size() - 1][0] * P[res.size() - 2]);
    ans[res.size() - 1] = Q[res.size() - 1];
    for (int i = res.size() - 2; i >= 0; i--)
    {
        ans[i] = P[i] * ans[i + 1] + Q[i];
    }
    return ans;
}

vector<double> Finite(double (*p)(double), double (*q)(double), double (*f)(double), double a, double b, double h,
    vector<double> coef0, vector<double> coefN, double F0, double FN)
{
    vector<vector <double>> coef;
    vector<double> res;
    coef.push_back(coef0);
    res.push_back(F0);
    double x = a + h;
    double h2 = 1 / (h * h);
    double hh = 1 / (2 * h);
    while (abs(x - b) > h / 10)
    {
        coef.push_back({ 2 - p(x) * h,-4 - 2 * h * h * q(x) ,2 + h * p(x) });
        res.push_back(2*h*h*f(x));
        x += h;
    }
    coef.push_back(coefN);
    res.push_back(FN);
    vector<double> ans = Progonka(coef, res);
    return ans;
}

double p(double x)
{
    return 4 * x;
}

double q(double x)
{
    return (4 * x*x+2);
}

double f(double x)
{
    return 0;
}


int main()
{
    double a = 0; double b = 2; double h = 0.1; vector<double> coef0 = { 0,1,0 };
    vector<double> coefN = { 0,1,0 }; double f0 = 1; double fN = (23)/(M_E * M_E * M_E * M_E);
    vector<double> one_one = Finite(p, q, f, a, b, h, coef0, coefN, f0, fN);
    double x = a;
    std::ofstream out;
    out.open("x1_1.txt");
    if (out.is_open())
    {
        out << x << "\n";
        while (abs(x - (b)) > h / 10)
        {
            x += h;
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


}

