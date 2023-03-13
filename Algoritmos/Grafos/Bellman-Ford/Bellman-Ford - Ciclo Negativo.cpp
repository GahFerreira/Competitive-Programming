// Obj.: Descobrir a dist. entre vértice ini e os outros.
// Obj.: Descobrir se há ciclo negativo.
// Compl.: O(va), v = |vértices|, a = |arestas|

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)
#define INF 1000000000 // Max int: 2147483647 & Max long long: 9223372036854775807

typedef long long ll;

// `gar`: Grafo de ARestas.
bool bmf(vector<tuple<int, int, int>>& gar, int ini, int n_vertices)
{
    vector<int> dist(n_vertices+1, INF);
    vector<bool> descoberto(n_vertices+1, false);

    dist[ini] = 0;
    descoberto[ini] = true;

    // Não há otimização `relaxou` para ciclo negativo.
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

    for (auto& ar : gar)
    {
        int a, b, w;
        tie(a, b, w) = ar;

        if (dist[a] + w < dist[b])
        {
            return true;
        }
    }

    return false;
}