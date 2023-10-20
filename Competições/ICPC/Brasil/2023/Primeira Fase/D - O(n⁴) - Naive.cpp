/*
    Naive [O(n⁴)], mas ainda é accepted (ao menos no Codeforces).

    A ideia é gerar 'n' matrizes de Floyd Warshall, onde cada uma não possui um vértice 'i'.
    
    Então, para descobrir a menor distância entre 'i->j', basta:
        - Checar para cada vértice 'w', t.q. 'w' seja diferente de 'i' e de 'j',
          a distância de 'w' para 'i' na matriz que desconsidera 'j' +
          a distância de 'w' para 'j' na matriz que desconsidera 'i'.
        - Pegar a menor delas.

    Isso funciona porque na matriz em que 'i' não é considerado, não existe nenhum caminho
    que passe por 'i'. Portanto, um caminho da forma 'w-> ... ->"i->j"' não existe.
        - Exceto o próprio caminho entre 'i' e 'j', mas ele não é considerado na resposta, por causa
        da checagem de 'w' ser diferente de 'i' e 'j'.
    
    Dessa forma, a aresta 'i->j' é desconsiderada.
    Sem perda de generalidade, o mesmo argumento vale para o caminho de 'w -> j' na matriz sem o 'i'.

    Teoricamente, a complexidade de calcular a matriz de Floyd Warshall para cada vértice é O(n⁴).
    Entretanto, a ideia para acelerar o algoritmo é usar a matriz já calculada até o vértice 'i' para
    o vértice 'i+1'.
        - Se queremos excluir o vértice 'i' da matriz, basta calcularmos as distâncias com 'k' de 0 até n-1,
        saltando a iteração em que 'k' seria 'i'.
        - Entretanto, note que para calcularmos 'i', no momento que 'k' seria 'i', podemos fazer uma cópia
        da matriz para quando formos excluir o vértice 'i+1'.
        - No momento em que fazemos a cópia, também calculamos nessa matriz do vértice 'i+1' as menores
        distâncias incluindo o vértice 'i'.
            - Note que estamos lidando com 2 matrizes nesse momento:
                1. A matriz que exclui o vértice 'i', que NÃO possui o vértice 'i'.
                2. A matriz que exclui o vértice 'i+1', que é uma cópia da matriz do vértice 'i'
                com a adição da iteração em que 'k' é 'i'.

    Dessa forma, fazemos O(n²) iterações de Floyd Warshall:
        - n-1 vezes para o vértice 1.
        - n-2 vezes para o vértice 2.
        - n-3 vezes para o vértice 3.
        ...

    Resultando em ((n-1) * n / 2) = O(n²) iterações.

    Complexidade final: O(n²) * O(n²) = O(n⁴). ¯\_(ツ)_/¯
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
    ll d[n+1][n][n];

    int N = 0;

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

        if (u > v) swap(u, v);

        g[u][v] = g[v][u] = d[N][u][v] = d[N][v][u] = w;
        qs.push_back({u, v});
    }

    for (int faltando = 0; faltando < n; ++faltando)
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