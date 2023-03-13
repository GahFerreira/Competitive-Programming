#include <bits/stdc++.h>
using namespace std;

#define INF 1000000000

vector<vector<int>> fw(vector<vector<int>>& adj, int n)
{
    vector<vector<int>> dist(n, vector<int>(n));

    for (int v_at = 0; v_at < n; v_at++)
    {
        for (int viz = 0; viz < n; viz++)
        {
            if (v_at == viz) dist[v_at][viz] = 0;
            else if (adj[v_at][viz]) dist[v_at][viz] = adj[v_at][viz];
            else dist[v_at][viz] = INF;
        }
    }

    for (int v_at = 0; v_at < n; v_at++)
    {
        for (int viz_in = 0; viz_in < n; viz_in++)
        {
            for (int viz_out = 0; viz_out < n; viz_out++)
            {
                dist[viz_in][viz_out] = min(dist[viz_in][viz_out],
                                            dist[viz_in][v_at] + dist[v_at][viz_out]);
            }
        }
    }

    return dist;
}