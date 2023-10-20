#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

#define str_to_lower(s) transform(s.begin(), s.end(), s.begin(), ::tolower)
#define str_to_upper(s) transform(s.begin(), s.end(), s.begin(), ::toupper)

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)
#define INF 1000000000 // Max int: 2147483647 & Max long long: 9223372036854775807

typedef long long ll;

// const int dx[8] = {+1, +0, -1, +0, +1, +1, -1, -1}, 
//           dy[8] = {+0, +1, +0, -1, -1, +1, -1, +1};

#define MAXN 200'010

vector<int> g[MAXN];
int da[MAXN], db[MAXN];
int a, b, mxa = -1, mxb = -1;

void dfs_finda(int at, int prev, int d)
{
    if (d > mxa) { a = at; mxa = d; }

    for (int viz : g[at])
    {
        if (viz == prev) continue;

        dfs_finda(viz, at, d+1);
    }
}

void dfsa(int at, int prev, int d)
{
    da[at] = d;

    if (d > mxb) { b = at; mxb = d; }

    for (int viz : g[at])
    {
        if (viz == prev) continue;

        dfsa(viz, at, d+1);
    }
}

void dfsb(int at, int prev, int d)
{
    db[at] = d;

    for (int viz : g[at])
    {
        if (viz == prev) continue;

        dfsb(viz, at, d+1);
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n;
    cin >> n;
    for_(i, 0, n-1)
    {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs_finda(0, -1, 0);
    dfsa(a, -1, 0);
    dfsb(b, -1, 0);

    for_(i, 0, n)
    {
        cout << max(da[i], db[i]) << " ";
    }
    cout << '\n';

    return 0;
}