
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

vector<double> Gaus_S(vector<vector <double>> mass, vector<double> values)
{
    vector<double> ans(mass[0].size());
    double per;
    double del;
    double sum = 0;
    ans[mass[0].size()-1] = 1;
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
    for (int i = mass.size() - 2; i >= 0; i--)
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

vector < vector < double>> M_multi(vector < vector < double>>a, vector < vector < double>>b)
{
    vector < vector < double>> c;
    c.assign(a.size(), vector<double>(a.size()));
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < a.size(); j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < a.size(); k++)

                c[i][j] += a[i][k] * b[k][j];
        }
    return c;
}

vector<double> Jacobi(vector < vector < double>> coef, double acc)
{
    vector <double> ans(coef.size());
    double max,sum;
    int coef1, coef2;
    bool accuracy = false;
    double angle = 0;
    vector < vector < double>> U;
    vector < vector < double>> UT;
    U.assign(coef.size(), vector<double>(coef.size()));
    UT.assign(coef.size(), vector<double>(coef.size()));
    vector < vector < double>> temp = U;
    while (accuracy == false)
    {
        max = 0;
        sum = 0;
        U = temp;
        UT = temp;
        for (int i = 0; i < coef.size(); i++)
        {
            U[i][i] = 1;
            for (int j = 0; j < i; j++)
            {
                U[i][j] = 0;
                if (abs(coef[i][j]) > abs(max))
                {
                    max = coef[i][j];
                    coef1 = i;
                    coef2 = j;
                }
            }
            for (int j = 0; j < i; j++)
            {
                U[i][j] = 0;
                if (abs(coef[i][j]) > abs(max))
                {
                    max = coef[i][j];
                    coef1 = i;
                    coef2 = j;
                }
            }

        }
        angle = 0.5 * atan(2 * coef[coef1][coef2] / (coef[coef1][coef1] - coef[coef2][coef2]));
        UT = U;
        U[coef1][coef1] = cos(angle);
        U[coef2][coef2] = cos(angle);
        U[coef1][coef2] = sin(angle);
        U[coef2][coef1] = -sin(angle);

        UT[coef1][coef1] = cos(angle);
        UT[coef2][coef2] = cos(angle);
        UT[coef1][coef2] = -sin(angle);
        UT[coef2][coef1] = sin(angle);

        coef = M_multi(UT, coef);
        coef = M_multi(coef, U);
        for (int i = 0; i < coef.size(); i++)
        {

            for (int j = 0; j < i; j++)
            {
                sum += sqrt(coef[i][j] * coef[i][j]);
            }
            for (int j = 0; j < i; j++)
            {
                sum += sqrt(coef[i][j] * coef[i][j]);
            }

        }
        if (sum < acc)
        {
            accuracy = true;
        }
    }
    for (int i = 0; i < coef.size(); i++)
    {
        ans[i] = coef[i][i];
    }
    return ans;
}

int main()
{
    setlocale(LC_CTYPE, "rus");
    vector<vector <double>> a{ {-1,3,4},{3,5,-1}, {4,-1,-5}};
    double acc = 0.01;
    vector<double> ans = Jacobi(a, acc);
    vector<double> vec(ans.size());
    vector<vector <double>> gaus;
    vector<double> sol(ans.size());

    for (int i = 0; i < ans.size(); i++)
    {
        cout <<  "Собственному значению матрицы: " << ans[i]<< '\n'<< "Соответствуют собственный вектор: " << '\n';
        gaus = a;
        for (int j = 0; j < a.size(); j++)
        {
            gaus[j][j] += -ans[i];
        }
        vec = Gaus_S(gaus, sol);
        for (int j = 0; j < vec.size(); j++)
        {
            cout << vec[j] << '\n';
        }
    }
}

