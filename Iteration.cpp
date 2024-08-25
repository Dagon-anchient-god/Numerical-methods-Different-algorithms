

#include <iostream>
#include <vector>
using namespace std;

vector<double> Simple(vector<vector <double>> coef, vector<double> ans, double acc)
{
    bool accuracy = false;
    vector<double> soul(ans.size());
    vector<double> lastsoul(ans.size());
    soul = ans;
    while (accuracy != true)
    {
        lastsoul = soul;
        for (int i = 0; i < ans.size(); i++)
        {
           soul[i] = ans[i]/ coef[i][i];
            for (int j = 0; j < i; j++)
            {
                soul[i] += -coef[i][j]/ coef[i][i] * lastsoul[j];
            }
            for (int j = i+1; j < ans.size(); j++)
            {
                soul[i] += -coef[i][j]/ coef[i][i] * lastsoul[j];
            }
        }
        for (int i = 0; i < ans.size(); i++)
        {
            if (abs(soul[i] - lastsoul[i]) < acc)
            {
                accuracy = true;
            }
            else
            {
                accuracy = false;
                break;
            }
        }
    }
    return soul;
}

vector<double> Seidel(vector<vector <double>> coef, vector<double> ans, double acc)
{
    bool accuracy = false;
    vector<double> soul(ans.size());
    vector<double> lastsoul(ans.size());
    soul = ans;
    while (accuracy != true)
    {
        lastsoul = soul;
        for (int i = 0; i < ans.size(); i++)
        {
            soul[i] = ans[i] / coef[i][i];
            for (int j = 0; j < i; j++)
            {
                soul[i] += -coef[i][j] / coef[i][i] * soul[j];
            }
            for (int j = i + 1; j < ans.size(); j++)
            {
                soul[i] += -coef[i][j] / coef[i][i] * lastsoul[j];
            }
        }
        for (int i = 0; i < ans.size(); i++)
        {
            if (abs(soul[i] - lastsoul[i]) < acc)
            {
                accuracy = true;
            }
            else
            {
                accuracy = false;
                break;
            }
        }
    }
    return soul;
}

int main()
{
    setlocale(LC_CTYPE, "rus");
    vector<vector <double>> a{ {22,-3,-8,7},{-8,-22,-4,-8 }, {8,-2,-18,2}, {7,2,-9,-24} };
    vector<double> b{ -158, 254, -108,  -24 };
    double acc = 0.01;
    vector<double> c = Simple(a, b,acc);
    vector<double> d = Seidel(a, b, acc);
    for (int i = 0; i < c.size(); i++)
    {
        cout << i + 1 << "  неизвестная, вычисленная методом простых итераций, равна:" << c[i] << '\n';
        cout << i + 1 << "  неизвестная, вычисленная методом Зейделя, равна:" << d[i] << '\n';
    }
}

