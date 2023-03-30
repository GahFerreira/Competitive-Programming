// onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1696

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)

ll kadane(vector<ll>& vetor)
{
    ll soma = vetor[0], melhor = vetor[0];

    for (int i = 1; i < (int) vetor.size(); i++)
    {
        soma = max(soma + vetor[i], vetor[i]);  

        if (soma > melhor) melhor = soma;
    }

    return melhor;
}

ll kadane3d(vector<vector<vector<ll>>>& cube, int x, int y, int z)
{
    vector<vector<vector<ll>>> aux(2, vector<vector<ll>>(y, vector<ll>(z)));
    ll melhor = cube[0][0][0];

    for_(x_ini, 0, x) for_(y_ini, 0, y) for_(x_at, x_ini, x) for_(y_at, y_ini, y)
    {
        for_(z_at, 0, z)
        {
            ll v = cube[x_at][y_at][z_at];

            if (x_ini < x_at) v += aux[(x_at-1)%2][y_at][z_at]; // Atrás
            if (y_ini < y_at) v += aux[x_at%2][y_at-1][z_at]; // À esquerda

            if (x_ini < x_at and y_ini < y_at) v -= aux[(x_at-1)%2][y_at-1][z_at]; 

            aux[x_at%2][y_at][z_at] = v;
        }

        melhor = max(melhor, kadane(aux[x_at%2][y_at]));
    }

    return melhor;
}

int main()
{
    int t;
    cin >> t;
    for (int tc = 0; tc < t; tc++)
    {
        if (tc > 0) cout << '\n';

        int x, y, z;
        cin >> x >> y >> z;

        vector<vector<vector<ll>>> cube(x, vector<vector<ll>>(y, vector<ll>(z)));

        for (int x_at = 0; x_at < x; x_at++)
        {
            for (int y_at = 0; y_at < y; y_at++)
            {
                for (int z_at = 0; z_at < z; z_at++)
                {
                    ll aux;
                    cin >> aux;
                    cube[x_at][y_at][z_at] = aux;
                }
            }
        }

        cout << kadane3d(cube, x, y, z) << '\n';
    }

    return 0;
}