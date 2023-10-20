#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)
#define INF 1000000000 // Max int: 2147483647 & Max long long: 9223372036854775807

typedef long long ll;

// `gar`: Grafo de ARestas.
bool spfa(vector<vector<pair<int, int>>>& g, int ini, int n_vertices)
{
    vector<int> dist(n_vertices, INF);
    vector<int> relax(n_vertices, 0);
    queue<int> q;
    vector<bool> na_fila(n_vertices, false); // Otimização
    bool ha_ciclo_negativo = false;

    dist[ini] = 0;
    q.push(ini);
    na_fila[ini] = true;

    while (!q.empty() and !ha_ciclo_negativo)
    {
        int at = q.front(); q.pop();
        na_fila[at] = false;

        for (auto& ar : g[at])
        {
            int viz = ar.first, w = ar.second;

            if (dist[at] + w < dist[viz])
            {
                dist[viz] = dist[at] + w;
                if (!na_fila[viz]) q.push(viz);

                ++relax[viz];
                if (relax[viz] >= n_vertices) 
                {
                    ha_ciclo_negativo = true;
                    break;
                }
            }
        }
    }

    return ha_ciclo_negativo;
}