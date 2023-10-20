/*
    A explicação do problema se encontra no arquivo "D - O(n⁴) - Naive.cpp".

    A otimização aqui está em pré-calcularmos 2 matrizes de Floyd Warshall
    até metade de n.

    A primeira, considera apenas os primeiros n/2 vértices.
        - Ou seja, varia k de 0 a n/2.

    A segunda, considera apenas os últimos n/2 vértices.
        - Ou seja, varia k de n-1 a n/2.

    Para os últimos n/2 vértices, usamos como ponto de início a primeira matriz.
    Para os primeiros n/2 vértices, usamos como ponto de início a segunda matriz.

    Isso ainda gera O(n²) iterações, mas cai pela metade em relação ao Naive:
    - n/2 iterações para o vértice 1.
    - n/2 -1 iterações para o vértice 2.
    - n/2 -2 iterações para o vértice 3.
    ...

    - n/2 iterações para o vértice n-1.
    - n/2 -1 iterações para o vértice n-2.
    - n/2 -2 iterações para o vértice n-3.
    ...

    Isso dá (2 * (n/2) * (n+1/2) / 2) = (n/2) * (n+1/2) = O(n²) iterações.
    Note que cortamos pela metade o número de iterações.

    Complexidade final: ainda O(n²) * O(n²) = O(n⁴). ¯\_(ツ)_/¯
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

    int N = n/2;

    for_(i, 0, n)
        for_(j, 0, n)
        {
            if (i == j)
            {
                d[N][i][j] = 0;
                g[i][j] = 0;
            }
            else
            {
                d[N][i][j] = INF;
                g[i][j] = INF;
            }
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

    for_(i, 0, n)
        for_(j, 0, n)
            d[N][i][j] = d[N][j][i] = g[i][j];

    for (int k = 0; k < N; ++k)
        for_(i, 0, n)
            for_(j, 0, n)
                d[N][i][j] = min(d[N][i][j], d[N][i][k] + d[N][k][j]);

    for (int faltando = N; faltando < n; ++faltando)
    {
        if (faltando +1 < n)
        {
            for_(i, 0, n)
                for_(j, 0, n)
                    d[faltando+1][i][j] = d[faltando][i][j];

            for_(i, 0, n)
                for_(j, 0, n)
                    d[faltando+1][i][j] = 
                        min(d[faltando+1][i][j], d[faltando+1][i][faltando] + d[faltando+1][faltando][j]);
        }

        for (int k = faltando+1; k < n; ++k)
        {
            for_(i, 0, n)
                for_(j, 0, n)
                    d[faltando][i][j] = min(d[faltando][i][j], d[faltando][i][k] + d[faltando][k][j]);
        }
    }

    for_(i, 0, n)
        for_(j, 0, n)
            d[N][i][j] = d[N][j][i] = g[i][j];


    for (int k = n-1; k > N; --k)
        for_(i, 0, n)
            for_(j, 0, n)
                d[N][i][j] = min(d[N][i][j], d[N][i][k] + d[N][k][j]);

    for (int faltando = N; faltando >= 0; --faltando)
    {
        if (faltando -1 >= 0)
        {
            for_(i, 0, n)
                for_(j, 0, n)
                    d[faltando-1][i][j] = d[faltando][i][j];

            for_(i, 0, n)
                for_(j, 0, n)
                    d[faltando-1][i][j] = 
                        min(d[faltando-1][i][j], d[faltando-1][i][faltando] + d[faltando-1][faltando][j]);
        }

        for (int k = faltando-1; k >= 0; --k)
        {
            for_(i, 0, n)
                for_(j, 0, n)
                    d[faltando][i][j] = min(d[faltando][i][j], d[faltando][i][k] + d[faltando][k][j]);
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

    return 0;
}