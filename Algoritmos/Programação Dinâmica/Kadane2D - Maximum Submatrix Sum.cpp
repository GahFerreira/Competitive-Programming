/*
Entrada: Uma matriz de inteiros 2-dimensional, com dimensões c, l.
Saída: A maior soma entre todos os sub-retângulos da matriz.
Compl.: O(c²l), l = |linhas|, c = |colunas|, c <= l.
*/

#include <bits/stdc++.h>

using namespace std;

// Soma máxima de submatriz
int kadane2d(vector<vector<int>>& matriz)
{
    int n_lin = (int) matriz.size(), n_col = (int) matriz[0].size();

    // Se puder submatriz vazia, inicia com 0.
    int melhor = matriz[0][0];
 
    for (int col_ini = 0; col_ini < n_col; col_ini++)
    {
        vector<int> soma_linhas(n_lin, 0);

        for (int col_ult = col_ini; col_ult < n_col; col_ult++)
        {
            for (int i_lin = 0; i_lin < n_lin; i_lin++)
            {
                // Cada posição de `soma_linha` é a soma de matriz[i_lin][col_ini:col_ult]
                soma_linhas[i_lin] += matriz[i_lin][col_ult];
            }

            // A resposta será a maior soma entre as submatrizes de matriz[:][col_ini:col_ult]
            int maior_soma = kadane(soma_linhas);

            if (maior_soma > melhor) melhor = maior_soma;
        }
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