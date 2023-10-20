/*
    A explicação do problema se encontra no arquivo "D - O(n⁴) - Naive.cpp".

    Complexidade: O(n³√n).

    A ideia de trocar um 'n' por '√n' é dividir o nosso número de vértices em
    '√n' trechos, cada um de tamanho '√n'.

    Parte 1: 
        Para cada trecho, calculamos uma matriz de FW incluindo todos os vértices 
        em todos os outros trechos. 
            - O(n³) por trecho.
            - Como temos '√n' trechos, O(n³√n) total.

    Parte 2: 
        Então, para cada vértice de um trecho, partimos da matriz de FW calculada 
        para aquele trecho.
            - É a matriz que inclui todos os vértices de todos os outros trechos.
        
        Basta então, incluir todos os outros vértices do mesmo trecho do vértice 
        que estamos olhando.
            - Como temos '√n' outros vértices no mesmo trecho, gastamos O(n²√n) 
            para terminar de computar a matriz de FW para aquele vértice.
            - Como temos 'n' vértices, e gastamos O(n²√n) por vértice, 
            gastamos O(n³√n) total.

    Como a Parte 1 gasta O(n³√n) e a Parte 2 gasta O(n³√n), no total gastamos:
        - 2 * O(n³√n) = O(n³√n).

    Assim, gastamos O(n³√n) no total.
*/

#include <bits/stdc++.h>
using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

using ll = long long;

const ll INF = 1'000'000'000'000'000;

int main()
{
    int n, m;
    cin >> n >> m;

    ll g[n][n];
    ll d[n][n][n];

    // Inicializa as matrizes.
    for_(i, 0, n)
        for_(j, 0, n)
        {
            if (i == j) g[i][j] = 0;

            else g[i][j] = INF;
        }

    vector<pair<int, int>> qs;

    for_(i, 0, m)
    {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;

        g[u][v] = g[v][u] = w;
        qs.push_back({u, v});
    }

    const int sqrt_n = ceill(sqrtl(n));

    for (int i_ini_bloco = 0; i_ini_bloco < n; i_ini_bloco = i_ini_bloco + sqrt_n)
    {
        ll aux[n][n];

        for_(i, 0, n)
            for_(j, 0, n)
                aux[i][j] = g[i][j];

        // Calculamos a matriz de FW com os vértices de todos os outros blocos.
        for (int i_ini_outro_bloco = 0; i_ini_outro_bloco < n; i_ini_outro_bloco += sqrt_n)
        {
            if (i_ini_bloco == i_ini_outro_bloco) continue;

            for (int k = i_ini_outro_bloco; k < i_ini_outro_bloco+sqrt_n and k < n; ++k)
            {
                for_(i, 0, n)
                    for_(j, 0, n)
                        aux[i][j] = min(aux[i][j], aux[i][k] + aux[k][j]);
            }
        }

        /*
            Para cada elemento do bloco atual terminamos o cálculo da matriz de FW dele:
                1. Usamos como base a matriz calculada anteriormente para seu bloco.
                2. Incluímos nela os outros vértices do bloco atual.
        */
        for (int elem = i_ini_bloco; elem < i_ini_bloco+sqrt_n and elem < n; ++elem)
        {
            for_(i, 0, n)
                for_(j, 0, n)
                    d[elem][i][j] = aux[i][j];

            for (int k = i_ini_bloco; k < i_ini_bloco+sqrt_n and k < n; ++k)
            {
                if (elem == k) continue;

                for_(i, 0, n)
                    for_(j, 0, n)
                        d[elem][i][j] = min(d[elem][i][j], d[elem][i][k] + d[elem][k][j]);
            }
        }
    }

    for (auto [u, v] : qs)
    {
        ll mn = INF;

        for_(i, 0, n)
        {
            if (i == u or i == v) continue;

            ll cand = d[v][i][u] + d[u][i][v];

            if (cand < mn) mn = cand;            
        }

        cout << (mn == INF ? -1 : mn) << '\n';
    }
}