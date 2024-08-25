// Gaus.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
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
    for (int i = 0; i < mass.size()-1; i++)
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
        for (int j = i + 1; j < mass.size() ; j++)
        {
            sum += mass[i][j] * ans[j];
        }
        ans[i] = (values[i] - sum) / mass[i][i];
        sum = 0;
    }
    return ans;
}

int main()
{
    setlocale(LC_CTYPE, "rus");
    cout << fixed;
    cout.precision(8);
    //vector<vector <double>> a{ {-5,2,4,-4},{4,9,-7,-5},{0,-5,6,7},{4,8,-6,-6}};
    //vector<double> b{ 57,-23,23,-20 };
    vector<vector <double>> a{ {22,-3,-8,7},{-8,-22,-4,-8 }, {8,-2,-18,2}, {7,2,-9,-24} };
    vector<double> b{ -158, 254, -108,  -24 };
    vector<double> c = Gaus(a, b);
    for (int i = 0; i < c.size(); i++)
    {
        cout <<i+1<<"  неизвестная равна:"<< c[i] << '\n';
    }


}

