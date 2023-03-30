/*
Entrada: Uma matriz de inteiros 3-dimensional, com dimensões x, y, z.
Saída: A maior soma entre todos os subparalelepídos da matriz.
Compl.: O(x²y²z), z >= x >= y.
Compl. Aux.: O(2yz).
*/

#include <bits/stdc++.h>
using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)

#define INF 1000000000000000000

// Soma máxima de subparalelepípedo
// É melhor que: z >= x >= y.
int kadane3d(vector<vector<vector<int>>>& cube, int x, int y, int z)
{
    // int aux[2][y][z];
    vector<vector<vector<int>>> aux(2, vector<vector<int>>(y, vector<int>(z)));
    
    // Se puder sub-paralelepípedo vazio, melhor = 0.
    int melhor = cube[0][0][0];

    // Trava a 1ª coluna de x, a 1ª de y, a últ. de x e a últ. de y.
    // Usa cube[x][y][z] e até (aux[(x-1)%2][y][z] e aux[x][y-1][z]) para saber aux[x][y][z].
    for_(x_ini, 0, x) for_(y_ini, 0, y) for_(x_at, x_ini, x) for_(y_at, y_ini, y)
    {
        for_(z_at, 0, z)
        {
            int v = cube[x_at][y_at][z_at];

            if (x_ini < x_at) v += aux[(x_at-1)%2][y_at][z_at]; // Atrás
            if (y_ini < y_at) v += aux[x_at%2][y_at-1][z_at]; // À esquerda

            // Intersecção repetida
            if (x_ini < x_at and y_ini < y_at) v -= aux[(x_at-1)%2][y_at-1][z_at]; 

            aux[x_at%2][y_at][z_at] = v;
        }

        melhor = max(melhor, kadane(aux[x_at%2][y_at]));
    }

    return melhor;
}

// Suporte
int kadane(vector<int>& vetor)
{
    int soma = vetor[0], melhor = vetor[0];

    for (int i = 1; i < (int) vetor.size(); i++)
    {
        soma = max(soma + vetor[i], vetor[i]);  

        if (soma > melhor) melhor = soma;
    }

    return melhor;
}