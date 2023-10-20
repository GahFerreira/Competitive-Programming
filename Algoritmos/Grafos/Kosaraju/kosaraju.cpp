#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)

vector<vector<int>> kosaraju(vector<vector<int>>& g, vector<vector<int>>& g_rev)
{
    // Cada 'vector<int>' terá os vértices de uma componente conexa distinta.
    vector<vector<int>> componentes_conexas;

    // Início DFS 1 - Temporizador
    vector<bool> visitado(g.size(), false);
    stack<int> ordem_termino;
    stack<int> s; // Stack DFS

    for_(i, 1, g.size())
    {
        if (visitado[i]) continue;
        s.push(i);
        while (!s.empty())
        {
            int at = s.top(); s.pop();
            if (at < 0) // Negativo para marcar o término do vértice `at` na DFS.
            {
                at = -at;
                ordem_termino.push(at);
            }
            if (visitado[at]) continue;
            visitado[at] = true;
            s.push(-at);
            for (int i_viz = (int) g[at].size()-1; i_viz >= 0; i_viz--) 
                s.push(g[at][i_viz]);
        }
    }
        
    fill(all(visitado), false);

    // DFS 2 - Na ordem da pilha de término, encontra as componentes conexas.
    while(!ordem_termino.empty())
    {
        int cand = ordem_termino.top(); ordem_termino.pop();
        if (visitado[cand]) continue;
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