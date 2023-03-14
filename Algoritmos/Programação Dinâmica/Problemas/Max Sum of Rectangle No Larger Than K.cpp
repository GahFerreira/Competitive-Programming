// Max Sum of Rectangle No Larger Than K
// https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/

#include <bits/stdc++.h>

using namespace std;

#define INF 1123456789

// Suporte
int maximum_subarray_sum(vector<int>& vetor, int k)
{
    int soma = 0, melhor = -INF;

    for (int i = 0; i < (int) vetor.size(); i++)
    {
        soma = max(soma + vetor[i], vetor[i]);

        if (soma > melhor) 
        {
            if (soma > k) return k;

            melhor = soma;
        }
    }

    return melhor;
}

int maximum_subarray_sum_less_than_k(vector<int>& vetor, int k)
{
    int melhor = -INF;

    set<int> somas_cumulativas;
    somas_cumulativas.insert(0);

    for (int i = 0, soma = 0; i < (int) vetor.size(); i++)
    {
        soma += vetor[i];

        auto menor_valor_maior_que_soma_menos_k = 
            lower_bound(somas_cumulativas.begin(), somas_cumulativas.end(), soma - k);

        if (menor_valor_maior_que_soma_menos_k != somas_cumulativas.end())
        {
            if (soma - *menor_valor_maior_que_soma_menos_k > melhor)
            {
                melhor = soma - *menor_valor_maior_que_soma_menos_k;
            }
        }

        somas_cumulativas.insert(soma);
    }

    return melhor;
}

int maxSumSubmatrix(vector<vector<int>> matriz, int k)
{
    int n_lin = (int) matriz.size(), n_col = (int) matriz[0].size();

    int melhor = -INF;

    for (int col_inicial = 0; col_inicial < n_col; col_inicial++)
    {
        vector<int> soma_linhas(n_lin, 0);

        for (int col_final = col_inicial; col_final < n_col; col_final++)
        {
            for (int i_lin = 0; i_lin < n_lin; i_lin++)
            {
                soma_linhas[i_lin] += matriz[i_lin][col_final];
            }

            int maior_soma = maximum_subarray_sum(soma_linhas, k);

            if (maior_soma == k) maior_soma = maximum_subarray_sum_less_than_k(soma_linhas, k);

            if (maior_soma > melhor) melhor = maior_soma;
        }
    }

    return melhor;
}