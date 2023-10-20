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
int subt[MAXN];
ll soma_dists[MAXN];

int n;

void dfs_pp(int at, int prev, int d)
{
    // Calcula a soma de todas as distâncias para o vértice 1.
    soma_dists[1] += d;
    
    subt[at] = 1;

    for (int viz : g[at])
    {
        if (viz == prev) continue;

        dfs_pp(viz, at, d+1);

        subt[at] += subt[viz];
    }
}

void dfs_q(int at, int prev)
{
    if (prev != -1) soma_dists[at] = soma_dists[prev] + n - (2 * subt[at]);

    for (int viz : g[at])
    {
        if (viz == prev) continue;

        dfs_q(viz, at);
    }
}

int main()  
{
    ios::sync_with_stdio(false); cin.tie(0);

    cin >> n;
    for_(i, 0, n-1)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    soma_dists[1] = 0;

    dfs_pp(1, -1, 0);
    dfs_q(1, -1);

    for_(i, 1, n+1)
    {
        cout << soma_dists[i] << '\n';
    }

    return 0;
}