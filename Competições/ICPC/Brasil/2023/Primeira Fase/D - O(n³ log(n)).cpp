/*
    A explicação do problema se encontra no arquivo "D - O(n⁴) - Naive.cpp".

    Complexidade: O(n³ log(n)).

    A ideia de trocar um 'n' por 'log(n)' é que podemos dividir nosso problema
    em dois subproblemas de tamanho metade.

    Seja M a matriz base (igual ao grafo G).
    Seja l = 0, r = n-1.

    Nosso problema original é calcular uma matriz de FW de 0 a n-1, excluindo um vértice.
    Podemos então dividir este problema em 2:
        1. Calcular a matriz de FW de l a r/2
        2. Calcular a matriz de FW de r/2 +1 a r.

    Seja M' a matriz resultado do 1º subproblema.
    Podemos usar M' como base para calcular as matrizes dos vértices de r/2 +1 a r.
    
        Seja l' = r/2 +1 e r' = r.

        Agora temos em nossa mão um novo problema: calcular as matrizes de FW de l' a r',
        excluindo um vértice.

        Podemos dividir esse nosso novo problema em 2:
            1. Calcular a matriz de FW de l' a r'/2.
            2. Calcular a matriz de FW de r'/2 +1 a r'.

        Note que esses são dois subproblemas do problema original. 
        Assim, podemos resolvê-los igual resolvemos o problema original.

    Seja M'' a matriz resultado do 2º subproblema.
    Analogamente podemos usar M'' como base para calcular as matrizes dos vértices de l a r/2.

        Seja l'' = l, r'' = r/2.

        Podemos dividir esse novo problema em 2:
            1. Calcular a matriz de FW de l'' a r''/2.
            2. Calcular a matriz de FW de r''/2 +1 a r''.

        Isso também nos gerará dois subproblemas do problema original.
        Assim, podemos resolvê-los igual resolvemos o problema original.
    
    Portanto, sempre conseguimos dividir nosso problema em dois subproblemas de tamanho metade.

    Mas onde excluímos um determinado vértice da computação?
        - Sempre que nosso problema atual tiver tamanho 1, sabemos que temos em mãos
        uma matriz de FW que incluiu todos os outros vértices na computação, exceto por 1.
        - Portanto, essa matriz é resposta para o nosso vértice do intervalo.
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
    vector<vector<ll>> d[n];
    vector<vector<ll>> aux_inicial(n, vector<ll>(n));

    // Inicializa as matrizes.
    for_(i, 0, n)
        for_(j, 0, n)
        {
            if (i == j)
            {
                aux_inicial[i][j] = 0;
                g[i][j] = 0;
            }

            else
            {
                aux_inicial[i][j] = INF;
                g[i][j] = INF;
            }
        }

    vector<pair<int, int>> qs;

    for_(i, 0, m)
    {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;

        g[u][v] = g[v][u] = aux_inicial[u][v] = aux_inicial[v][u] = w;
        qs.push_back({u, v});
    }

    auto calcula_fw = [&, &d](auto self, vector<vector<ll>> aux, int l, int r) -> void
    {
        // Caso base - folha.
        if (l == r)
        {
            d[l] = aux;
            return;
        }

        int meio = (l+r) / 2;

        auto auxl = aux;
        for (int k = l; k <= meio; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    auxl[i][j] = min(auxl[i][j], auxl[i][k] + auxl[k][j]);

        self(self, auxl, meio+1, r);

        auto& auxr = aux;
        for (int k = meio+1; k <= r; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    auxr[i][j] = min(auxr[i][j], auxr[i][k] + auxr[k][j]);

        self(self, auxr, l, meio);
    };

    calcula_fw(calcula_fw, aux_inicial, 0, n-1);

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