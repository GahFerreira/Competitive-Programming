/*
    Note: Ideia ERRADA para o problema.

    A ideia seria usar uma versão de Floyd Warshall que calcula o menor caminho
    entre todos os vértices sem usar a aresta direta entre eles.

    Ou seja, o menor caminho indireto entre todos os vértices.

    A ideia seria baseada na observação de que, se desconsiderasse as arestas diretas, nas
    primeiras k iterações do algoritmo, todos os caminhos incluiriam apenas os vértices de 0 a k-1.

    Assim, seria possível descobrir o menor caminho para cada aresta u->v em O(n³).
    
    Problema: nessa implementação, o menor caminho indireto de u->v ainda pode incluir a aresta u->v.
        - Isso porque o relaxamento de aresta entre 'i' e 'j' considera a distância de 'i->k' + 'k->j'.
        - Entretanto, a menor distância entre 'i->k' poderia ser algo como 'i->j->k'.
        - Assim, apesar de que o caminho entre 'i->j' deveria ser indireto, ele não o é.
*/

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#define watch(x) cerr << (#x) << " is " << (x) << endl;
#else
#define watch(x)
#endif

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

using ll = long long;

const ll INF = 1'000'000'000'000'000;

int main()
{
    int n, m;
    cin >> n >> m;

    ll g[n][n];
    ll d[n][n];

    for_(i, 0, n)
        for_(j, 0, n)
        {
            if (i == j) g[i][j] = 0;
            else g[i][j] = INF;

            d[i][j] = INF;
        }

    vector<pair<int, int>> qs;

    for_(i, 0, m)
    {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;

        if (u > v) swap(u, v);

        g[u][v] = g[v][u] = w;
        qs.push_back({u, v});
    }

    for_(k, 0, n)
        for_(i, 0, n)
            for_(j, i+1, n)
            {
                if (k == i or k == j) continue;

                if (i+j == 1)
                {
                    watch(k);
                    watch(i);
                    watch(j);
                    watch(d[i][j]);
                    watch(g[i][k]);
                    watch(d[i][k]);
                    watch(g[k][j]);
                    watch(d[k][j]);
                }
                d[i][j] = min(d[i][j], min(g[i][k], d[i][k]) + min(g[k][j], d[k][j]));
                if (i+j == 1) watch(d[i][j]);
            }

    for_(i, 0, qs.size())
    {
        int u, v;
        tie(u, v) = qs[i];

        if (d[u][v] == INF) cout << "-1\n";
        else cout << d[u][v] << '\n';
    }

    return 0;
}