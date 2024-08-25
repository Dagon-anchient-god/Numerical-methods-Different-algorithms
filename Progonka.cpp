

#include <iostream>
#include <vector>
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

int main()
{
    setlocale(LC_CTYPE, "rus");
    vector<vector <double>> a{ {0,6,3},{-9,-17,3 }, {-3,12,-7}, {2,-9,-6}, {-4,5,0} };
    vector<double> b{ 0 , -99, -107, 5, -6 };
    //vector<vector <double>> a{ {0,12,-5},{-3,-18,-8 }, {-2,-16,-9}, {-4,18,-7}, {4,-9,0} };
    //vector<double> b{ 148 , 45, -155, 11, 3 };
    vector<double> c = Progonka(a, b);
    for (int i = 0; i < c.size(); i++)
    {
        cout << i + 1 << "  неизвестная равна:" << c[i] << '\n';
    }
}

