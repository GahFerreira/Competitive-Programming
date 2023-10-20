// Link: onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2938

#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)

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

    int n, m;
    while (cin >> n >> m and (n != 0 or m != 0))
    {
        vector<vector<int>> g(n+1), g_rev(n+1);
        for_(i, 0, m)
        {
            int a, b, p;
            cin >> a >> b >> p;
            
            g[a].push_back(b);
            g_rev[b].push_back(a);

            if (p == 2)
            {
                g[b].push_back(a);
                g_rev[a].push_back(b);
            }
        }

        cout << (kosaraju(g, g_rev).size() == 1 ? "1\n" : "0\n");
    }

    return 0;
}