#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define INF 1000000000000000000

vector<int> caminho;

void dijkstra(vector<vector<pair<int, ll>>>& g, int ini, int ult)
{
    priority_queue<pair<ll, int>> q;
    vector<bool> processado(g.size(), false);
    vector<ll> dist(g.size(), INF);
    vector<int> prev(g.size(), -1);

    q.push({0, ini});
    dist[ini] = 0;

    while(!q.empty())
    {
        int at = q.top().second; q.pop();

        if (processado[at]) continue;
        processado[at] = true;

        for (auto ar : g[at])
        {
            int b = ar.first;
            ll w = ar.second;

            if (dist[at] + w < dist[b])
            {
                dist[b] = dist[at] + w;
                q.push({-dist[b], b});
                prev[b] = at;
            }
        }
    }

    // Constrói caminho de ini a ult
    if (dist[ult] == INF)
    {
        caminho.push_back(-1);
    }

    else
    {
        int b = ult;
        while (b != ini)
        {
            caminho.push_back(b);
            b = prev[b];
        }

        caminho.push_back(ini);

        reverse(caminho.begin(), caminho.end());
    }
}