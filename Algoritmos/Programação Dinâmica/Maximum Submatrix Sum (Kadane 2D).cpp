/*
Objetivo: encontrar a submatriz contígua de matriz com maior soma.
Compl.: O(c²l) para  l = |linhas|, c = |colunas|.
*/

#include <bits/stdc++.h>

using namespace std;

// Suporte
int maximum_subarray_sum(vector<int>& vetor)
{
    // Se subarray não vazia, inicia com vetor[0] e começa o for do 1.
    int soma = 0, melhor = 0;

    for (int i = 0; i < (int) vetor.size(); i++)
    {
        // Vai somando os números da array.
        // Quando encontrar um número cujo valor seja maior que a soma atual + ele,
        // é melhor escolher ele sozinho para compor uma nova subarray de maior soma.
        soma = max(soma + vetor[i], vetor[i]);

        if (soma > melhor) melhor = soma;
    }

    return melhor;
}

// Soma máxima de submatriz
int kadane2d(vector<vector<int>>& matriz)
{
    int n_lin = (int) matriz.size(), n_col = (int) matriz[0].size();

    // Se for submatriz não vazia, inicia com matriz[0][0].
    int melhor = 0;

    for (int col_inicial = 0; col_inicial < n_col; col_inicial++)
    {
        vector<int> soma_linhas(n_lin, 0);

        for (int col_final = col_inicial; col_final < n_col; col_final++)
        {
            for (int i_lin = 0; i_lin < n_lin; i_lin++)
            {
                // Cada posição de `soma_linha` é a soma de matriz[i_lin][col_inicial:col_final]
                soma_linhas[i_lin] += matriz[i_lin][col_final];
            }

            // A resposta será a maior soma entre as submatrizes de matriz[:][col_inicial:col_final]
            int maior_soma = maximum_subarray_sum(soma_linhas);

            if (maior_soma > melhor) melhor = maior_soma;
        }
    }

    return melhor;
}