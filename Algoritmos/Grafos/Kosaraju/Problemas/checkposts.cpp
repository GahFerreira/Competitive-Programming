#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)
#define INF INT_MAX // Max int: 2147483647 & Max long long: 9223372036854775807
#define MOD 1000000007

vector<vector<int>> kosaraju(vector<vector<int>>& g, vector<vector<int>>& g_rev)
{
    vector<vector<int>> componentes_conexas;

    vector<bool> visitado(g.size(), false);
    stack<int> ordem_termino;

    stack<int> s;

    for_(i, 1, g.size())
    {
        if (visitado[i]) continue;
        s.push(i);
        while (!s.empty())
        {
            int at = s.top(); s.pop();
            if (at < 0) 
            {
                at = -at;
                ordem_termino.push(at);
            }
            if (visitado[at]) continue;
            visitado[at] = true;
            s.push(-at);
            for (int i_viz = (int) g[at].size()-1; i_viz >= 0; i_viz--) s.push(g[at][i_viz]);
        }
    }
        
    fill(all(visitado), false);

    while(!ordem_termino.empty())
    {
        int cand = ordem_termino.top(); ordem_termino.pop();
        if (visitado[cand]) continue;
        // DFS
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
        componentes_conexas.push_back(nova_componente);
    }

    return componentes_conexas;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n;
    cin >> n;
    vector<int> custo(n+1);
    for_(i, 1, n+1) cin >> custo[i];
    int m;
    cin >> m;
    vector<vector<int>> g(n+1), g_rev(n+1);
    for_(i, 0, m)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g_rev[v].push_back(u);
    }
    auto comps = kosaraju(g, g_rev);
    int mn_custo = 0, resp = 1;
    for (auto& comp : comps)
    {
        int mn = INF, qtd = 0;
        for (int at : comp)
        {
            if (custo[at] < mn)
            {
                mn = custo[at];
                qtd = 1;
            }
            else if (custo[at] == mn) qtd++;
        }

        mn_custo += mn;
        resp = (resp*qtd)%MOD;
    }

    cout << mn_custo << " " << resp << endl;

    return 0;
}