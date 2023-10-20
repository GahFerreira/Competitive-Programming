#include <bits/stdc++.h>

using namespace std;

#define MAX_N 10000
#define INF ((int) 1e9)

vector<int> adj[MAX_N];
vector<int> dist(MAX_N);

void menor_dist_dfs(int at, int prev)
{
    dist[at] = INF;

    for (auto& viz : adj[at])
    {
        if (prev == viz) continue;

        menor_dist_dfs(viz, at);
        dist[at] = min(dist[at], dist[viz]);
    }

    // Folha.
    if (dist[at] == INF) dist[at] = 0;

    // Pega a distância mínima entre seus filhos, +1.
    else ++dist[at];
}

void maior_dist_dfs(int at, int prev)
{
    dist[at] = -INF;

    for (auto& viz : adj[at])
    {
        if (prev == viz) continue;

        maior_dist_dfs(viz, at);
        dist[at] = max(dist[at], dist[viz]);
    }

    // Folha.
    if (dist[at] == -INF) dist[at] = 0;

    // Pega a distância máxima entre seus filhos, +1.
    else ++dist[at];
}
