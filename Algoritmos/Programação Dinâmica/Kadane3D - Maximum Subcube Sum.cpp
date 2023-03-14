/*
Objetivo: encontrar o subcubo contígua de cube (x, y, z) com maior soma.
Compl.: O(x²y²z)
Compl. Aux.: O(2yz)
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define INF 1000000000000000000

ll kadane(const vector<ll>& vetor)
{
    ll soma = 0, melhor = 0;

    for (int i = 0; i < (int) vetor.size(); i++)
    {
        soma = max(soma + vetor[i], vetor[i]);

        if (soma > melhor) melhor = soma;
    }

    return melhor;
}

// Soma máxima de subcubo
ll kadane3d(const vector<vector<vector<ll>>>& cube, const int x, const int y, const int z)
{
    // ll aux[2][y][z];
    vector<vector<vector<ll>>> aux(2, vector<vector<ll>>(y, vector<ll>(z)));
    ll melhor = -INF; // Alt.: = cube[0][0][0]

    // Trava a 1ª coluna de x, a 1ª de y, a últ. de x e a últ. de y.
    // Usa cube[x][y][z] e até aux[(x-1)%2][y][z] e aux[x][y][z] para saber aux[x][y][z].
    for (int x_ini = 0; x_ini < x; x_ini++)
    {
        for (int y_ini = 0; y_ini < y; y_ini++)
        {
            for (int x_at = x_ini; x_at < x; x_at++)
            {
                for (int y_at = y_ini; y_at < y; y_at++)
                {
                    for (int z_at = 0; z_at < z; z_at++)
                    {
                        ll v = cube[x_at][y_at][z_at];

                        if (x_ini < x_at) v += aux[(x_at-1)%2][y_at][z_at];
                        if (y_ini < y_at) v += aux[x_at%2][y_at-1][z_at];

                        if (x_ini < x_at and y_ini < y_at) v -= aux[(x_at-1)%2][y_at-1][z_at];

                        aux[(x_at)%2][y_at][z_at] = v;
                    }

                    // Se não puder ter subcubo vazio, iniciar
                    // vetor/soma com vetor[0] e o for de 1.
                    melhor = max(melhor, kadane(aux[x_at%2][y_at]));
                }
            }
        }
    }

    return melhor;
}