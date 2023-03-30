// Max Sum of Rectangle No Larger Than K
// https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/

#include <bits/stdc++.h>

using namespace std;

#define INF 1123456789

// Suporte
int kadane(vector<int>& vetor, int k)
{
    int soma = vetor[0], melhor = vetor[0];

    for (int i = 1; i < (int) vetor.size(); i++)
    {
        soma = max(soma + vetor[i], vetor[i]);  

        if (soma > melhor) 
        {
            if (soma > k) return k+1;

            melhor = soma;
        }
    }

    return melhor;
}

int max_subarray_sum_less_equal_k(vector<int>& vetor, int k)
{
    int melhor = -INF;

    set<int> s;
    s.insert(0);

    for (int i = 0, soma = 0; i < (int) vetor.size(); i++)
    {
        soma += vetor[i];

        auto v = lower_bound(s.begin(), s.end(), soma - k);

        if (v != s.end())
        {
            if (soma - *v > melhor)
            {
                melhor = soma - *v;

                if (melhor == k) return k; // Otimização
            }
        }

        s.insert(soma);
    }

    return melhor;
}

int maxSumSubmatrix(vector<vector<int>> matriz, int k)
{
    int n_lin = (int) matriz.size(), n_col = (int) matriz[0].size();

    int melhor = -INF;
 
    for (int col_ini = 0; col_ini < n_col; col_ini++)
    {
        vector<int> soma_linhas(n_lin, 0);

        for (int col_ult = col_ini; col_ult < n_col; col_ult++)
        {
            for (int i_lin = 0; i_lin < n_lin; i_lin++)
            {
                soma_linhas[i_lin] += matriz[i_lin][col_ult];
            }

            int maior_soma = kadane(soma_linhas, k);

            if (maior_soma > k) maior_soma = max_subarray_sum_less_equal_k(soma_linhas, k);

            if (maior_soma > melhor) melhor = maior_soma;
        }
    }

    return melhor;
}