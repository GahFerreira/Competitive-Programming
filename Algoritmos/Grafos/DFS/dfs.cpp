#include <bits/stdc++.h>
using namespace std;

#define MAX_N 10000

vector<int> adj[MAX_N];
vector<bool> percorrido(MAX_N, false);

void dfs(int at)
{
    if (percorrido[at]) return;

    percorrido[at] = true;

    for (auto viz : adj[at])
    {
        dfs(viz);        
    }
}

void dfs_i(int ini)
{
    stack<int> s;

    s.push(ini);

    while (!s.empty())
    {
        int at = s.top(); s.pop();

        if (percorrido[at]) continue;

        percorrido[at] = true;

        for (auto it = adj[at].rbegin(); it != adj[at].rend(); it++)
        {
            auto viz = *it;

            s.push(viz);
        }
    }
}