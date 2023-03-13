#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)
#define INF 1000000000 // Max int: 2147483647 & Max long long: 9223372036854775807

typedef long long ll;

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