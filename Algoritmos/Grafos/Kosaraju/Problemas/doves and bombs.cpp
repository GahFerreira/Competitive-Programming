#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

#define str_to_lower(s) transform(s.begin(), s.end(), s.begin(), ::tolower)
#define str_to_upper(s) transform(s.begin(), s.end(), s.begin(), ::toupper)

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)
#define INF 1000000000 // Max int: 2147483647 & Max long long: 9223372036854775807

typedef long long ll;

// const int dx[8] = {+1, +0, -1, +0, +1, +1, -1, -1}, 
//           dy[8] = {+0, +1, +0, -1, -1, +1, -1, +1};

vector<int> kosaraju(vector<vector<int>>& g, vector<vector<int>>& g_rev)
{
    vector<int> ancestral(g.size(), -1);
    vector<bool> visitado(g.size(), false);
    queue<int> q;

    stack<pair<int, int>> s;
    s.push({0, -1});

    while (!s.empty())
    {
        int at, prev;
        tie(at, prev) = s.top(); s.pop();
        if (at < 0) q.push(-at);
        if (visitado[at]) continue;
        visitado[at] = true;
        ancestral[at] = prev;
        s.push({-at, -1});
        for (int i_viz = (int) g[at].size()-1; i_viz >= 0; i_viz--) s.push({g[at][i_viz], at});
    }

    fill(all(visitado), false);

    int resp = 0;

    while(!q.empty())
    {
        int cand = q.front(); q.pop();
        if (visitado[cand]) continue;
        // DFS
        ++resp;
        stack<int> s;
        vector<int> nova_componente;
        s.push(cand);
        while (!s.empty())
        {
            int at = s.top(); s.pop();
            if (visitado[at]) continue;
            visitado[at] = true;
            nova_componente.push_back(at);
            for (int i_viz = (int) g_rev[at].size()-1; i_viz >= 0; i_viz--)
            {
                s.push(g_rev[at][i_viz]);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n, m;
    while (cin >> n >> m and (n != 0 or m != 0))
    {
        vector<vector<int>> g(n);
        int x, y;
        while (cin >> x >> y and (x != -1 or y != -1))
        {
            g[x].push_back(y);
            g[y].push_back(x);
        }
    }
    
    return 0;
}