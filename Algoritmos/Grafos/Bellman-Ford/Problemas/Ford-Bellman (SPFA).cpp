// eolymp.com/en/problems/1453

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)
#define INF 30000 // Max int: 2147483647 & Max long long: 9223372036854775807

typedef long long ll;

// `gar`: Grafo de ARestas.
vector<int> spfa(vector<vector<pair<int, int>>>& g, int ini, int n_vertices)
{
    vector<int> dist(n_vertices+1, INF);
    queue<int> q;

    dist[ini] = 0;
    q.push(ini);

    while (!q.empty())
    {
        int at = q.front(); q.pop();

        for (auto& ar : g[at])
        {
            int viz = ar.first, w = ar.second;

            if (dist[at] + w < dist[viz])
            {
                dist[viz] = dist[at] + w;
                q.push(viz);
            }
        }
    }

    return dist;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> g(n+1);

    for (int i = 0; i < m; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;

        g[a].push_back({b, w});
    }

    auto dist = spfa(g, 1, n);

    cout << dist[1];

    for (int i = 2; i < dist.size(); i++)
    {
        cout << " " << dist[i];
    }
    
    cout << '\n';

    return 0;
}