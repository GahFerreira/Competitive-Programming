#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)
#define INF 1000000000 // Max int: 2147483647 & Max long long: 9223372036854775807

typedef long long ll;

// `gar`: Grafo de ARestas.
vector<int> bmf(vector<tuple<int, int, int>>& gar, int ini, int n_vertices)
{
    // `descoberto` garante que `dist` vai ter a menor distância entre ini e o resto.
    // Ex.: n_vertices = 3, ini = 1, gar = { {2, 3, -1} }.
    vector<int> dist(n_vertices+1, INF);
    vector<bool> descoberto(n_vertices+1, false);

    dist[ini] = 0;
    descoberto[ini] = true;

    for (int passo = 1; passo <= n_vertices-1; passo++)
    {
        for (auto& ar : gar)
        {
            int a, b, w;
            tie(a, b, w) = ar;

            if (!descoberto[a]) continue;

            if (dist[a] + w < dist[b])
            {
                if (!descoberto[b]) descoberto[b] = true;
                dist[b] = dist[a] + w;
            }
        }
    }

    return dist;
}