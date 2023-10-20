#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

#define MAXN 200'010

vector<int> g[MAXN];

int a;
int mxa = -1, mxb = -1;

void dfs_find_a(int at, int prev, int d)
{
    if (d > mxa) { a = at; mxa = d; }

    for (int viz : g[at])
    {
        if (viz == prev) continue;

        dfs_find_a(viz, at, d+1);
    }
}

void dfs_find_b(int at, int prev, int d)
{
    if (d > mxb) { mxb = d; }

    for (int viz : g[at])
    {
        if (viz == prev) continue;

        dfs_find_b(viz, at, d+1);
    }
}

int main()
{
    int n;
    cin >> n;
    for_(i, 0, n-1)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs_find_a(1, -1, 0);
    dfs_find_b(a, -1, 0);

    cout << mxb << '\n';

    return 0;
}