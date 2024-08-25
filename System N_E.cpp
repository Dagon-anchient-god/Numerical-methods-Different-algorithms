#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void max_el(int a, vector<vector <double>>& mass, vector<double>& values)
{
    for (int i = a; i < mass.size(); i++)
    {
        if (abs(mass[a][a]) < abs(mass[i][a]))
        {
            swap(mass[a], mass[i]);
            swap(values[a], values[i]);
        }
    }
}

vector<double> Gaus(vector<vector <double>> mass, vector<double> values)
{
    vector<double> ans(mass[0].size());
    double per;
    double del;
    double sum = 0;
    for (int i = 0; i < mass.size() - 1; i++)
    {
        max_el(i, mass, values);
        per = mass[i][i];
        for (int j = i + 1; j < mass.size(); j++)
        {
            del = -(mass[j][i] / per);
            mass[j][i] = 0;
            values[j] += values[i] * del;
            for (int k = i + 1; k < mass[0].size(); k++)
            {
                mass[j][k] += mass[i][k] * del;
            }
        }
    }
    for (int i = mass.size() - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < mass.size(); j++)
        {
            sum += mass[i][j] * ans[j];
        }
        ans[i] = (values[i] - sum) / mass[i][i];
        sum = 0;
    }
    return ans;
}

vector<double> Simple(double (*f1)(double,double), double (*f2)(double), double a, double b, double acc)
{
    vector<double> ans{5 ,1 };
    vector<double> lastans{ a,b };
    bool accuracy = false;
    double temp;
    while (accuracy!=true)
    {

        temp = ans[0];
        ans[0] = f1(lastans[0], lastans[1]);
        lastans[0] = temp;

        temp = ans[1];
        ans[1] = f2(lastans[0]);
        lastans[1] = temp;
        
        for (int i = 0; i < 2; i++)
        {
            if (abs(ans[i] - lastans[i]) < acc)
                accuracy = true;
            else
            {
                accuracy = false;
                break;
            }
        }
    }
    return ans;
}

vector<double> Seidel(double (*f1)(double, double), double (*f2)(double), double a, double b, double acc)
{
    vector<double> ans{ 5,1 };
    vector<double> lastans{ a,b };
    bool accuracy = false;
    double temp;
    while (accuracy != true)
    {
        temp = ans[0];
        ans[0] = f1(lastans[0], lastans[1]);
        lastans[0] = temp;

        temp = ans[1];
        ans[1] = f2(ans[0]);
        lastans[1] = temp;

        for (int i = 0; i < 2; i++)
        {
            if (abs(ans[i] - lastans[i]) < acc)
                accuracy = true;
            else
            {
                accuracy = false;
                break;
            }
        }
    }
    return ans;
}

vector<double> Newton(double (*f1)(double, double), double (*f2)(double, double), double (*f3)(double), double (*f4)(), double (*f5)(double, double), double (*f6)(double, double), double a, double b, double acc)
{
    vector<double> ans{ 0,0 };
    vector<double> lastans{ a,b };
    bool accuracy = false;
    vector<vector<double>> W;
    vector<double> F;
    vector<double> soul;
    double temp;
    while (accuracy != true)
    {
        W = { {f1(lastans[0],lastans[1]),f2(lastans[0],lastans[1])}, {f3(lastans[0]), f4()} };
        F = { -f5(lastans[0],lastans[1]),-f6(lastans[0],lastans[1])};
        soul = Gaus(W, F);

        for (int i = 0; i < 2; i++)
        {
            temp = ans[i];
            ans[i] = lastans[i] + soul[i];
            lastans[i] = temp;
        }

        for (int i = 0; i < 2; i++)
        {
            if (abs(ans[i] - lastans[i]) < acc)
                accuracy = true;
            else
            {
                accuracy = false;
                break;
            }
        }
    }
    return ans;
}

double eq1(double x1, double x2)
{
    return  pow(M_E, x1 * x2)+x1-6;
}

double eq2(double x1, double x2)
{
    return x1*x1-6*x2-1;
}

double eq_1(double x1, double x2)
{
    return sqrt(6 * x2 + 1);
}

double eq_2(double x1)
{
    return log(6-x1)/x1;
}

double eq_P1(double x1, double x2)
{
    return x2* pow(M_E, x1 * x2)+1;
}

double eq_P2(double x1, double x2)
{
    return x2 * pow(M_E, x1 * x2);
}

double eq_P3(double x)
{
    return 2*x;
}

double eq_P4()
{
    return -6;
}

int main()
{
    setlocale(LC_CTYPE, "rus");
    double acc = 0.00001;
    double a = 5;
    double b = 4;
    vector<double> ans(2);
    ans = Simple(eq_1, eq_2,a,b, acc);
    cout << "Корни системы нелинейных уравнений, вычисленный методом простых итераций, равны:  "  << '\n';
    for (int i = 0; i < 2; i++)
    {
        cout<< ans[i]<< '\n';
    }

    ans = Seidel(eq_1, eq_2, a, b, acc);
    cout << "Корни системы нелинейных уравнений, вычисленный методом Зейделя, равны:  " << '\n';
    for (int i = 0; i < 2; i++)
    {
        cout << ans[i] << '\n';
    }

    ans = Newton(eq_P1, eq_P2, eq_P3, eq_P4, eq1, eq2, a, b, acc);
    cout << "Корни системы нелинейных уравнений, вычисленный методом Ньютона, равны:  " << '\n';
    for (int i = 0; i < 2; i++)
    {
        cout << ans[i] << '\n';
    }

}

