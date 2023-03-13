#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define INF 1000000000000000000

deque<int> dijkstra(vector<vector<pair<int, ll>>>& g, int ini, int ult)
{
    deque<int> ret;

    priority_queue<pair<ll, int>> q;
    vector<bool> processado(g.size(), false);
    vector<ll> dist(g.size(), INF);
    vector<int> prev(g.size(), -1);

    q.push({0, ini});
    dist[ini] = 0;

    while(!q.empty())
    {
        int v = q.top().second; q.pop();

        if (processado[v]) continue;
        processado[v] = true;

        for (auto ar : g[v])
        {
            int b = ar.first;
            ll w = ar.second;

            if (dist[v] + w < dist[b])
            {
                dist[b] = dist[v] + w;
                q.push({-dist[b], b});
                prev[b] = v;
            }
        }
    }

    if (dist[ult] == INF)
    {
        ret.push_back(-1);
    }

    else
    {
        int b = ult;
        while (b != ini)
        {
            ret.push_front(b);
            b = prev[b];
        }

        ret.push_front(ini);
    }

    return ret;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, ll>>> adj(n+1);

    for (int i = 0; i < m; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    deque<int> ordem = dijkstra(adj, 1, n);

    for (auto v : ordem)
    {
        cout << v << " ";
    }

    cout << '\n';

    return 0;
}