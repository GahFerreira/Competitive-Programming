/*
    2SAT

    Cada sala possui 2 alavancas que determinam se ela ficará aberta ou fechada.

    Sejam 'p,q' as alavancas da sala 's'.
    
    Se 's' estiver inicialmente fechada (estado 0):
        - Exatamente uma entre 'p' e 'q' tem que estar ativas (p XOR q) para abrí-la.
        - (p XOR q) = (p v q) ^ (¬p v ¬q)
    
    Se 's' estiver inicialmente aberta (estado 1):
        - Exatamente nenhuma ou ambas entre 'p' e 'q' tem que estar ativas ¬(p XOR q) para abrí-la.
        - ¬(p XOR q) = (¬p v q) ^ (p v ¬q)
        
    Assim, para cada porta, são adicionadas duas regras ao 2SAT.
    
    O grafo de implicação vai ter 2 * 'm' arestas, sendo 'm' o número de diferentes alavancas.
        - 2 * m: um vértice para p e um para ¬p.

    Para este problema o grafo com arestas reversas é igual ao grafo original.

    Passa Kosaraju no grafo, e na 2ª DFS, checa se existe um par de vértices (p, ¬p) que
    fazem parte da mesma componente.
        - Se existir, não há solução para o 2SAT -> "NO".
        - Se não existir, há -> "YES".
*/

#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

#define all(x) x.begin(), x.end()

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

typedef long long ll;

int n, m;
vector<bool> vis;
vector<vector<int>> g;
stack<int> pilha, tempo;
vector<int> comp;

void dfs(int at)
{
    if (vis[at]) return;

    vis[at] = true;
    for (int viz : g[at]) dfs(viz);
    tempo.push(at);
}

bool dfs_back(int at, int i_comp)
{
    if (vis[at]) return true;

    vis[at] = true;
    comp[at] = i_comp;
    if (comp[at] == comp[(at+m)%(2*m)]) return false;
    for (int viz : g[at]) 
    {
        if (dfs_back(viz, i_comp) == false) return false;
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    
    cin >> n >> m;
    vector<int> estado(n);
    vector<pair<int, int>> alavancas(n, {-1, -1});
    for_(i, 0, n) cin >> estado[i];
    for_(i_alavanca, 0, m)
    {
        int qtd;
        cin >> qtd;
        for_(i_qtd, 0, qtd)
        {
            int sala;
            cin >> sala;
            --sala;
            if (alavancas[sala].ff == -1) alavancas[sala].ff = i_alavanca;
            else alavancas[sala].ss = i_alavanca;
        }
    }

    g.resize(2*m);
    for_(i_sala, 0, n)
    {
        int a1, a2;
        tie(a1, a2) = alavancas[i_sala];

        if (estado[i_sala] == 0)
        {
            g[a1].push_back(a2+m);
            g[a2+m].push_back(a1);

            g[a2].push_back(a1+m);
            g[a1+m].push_back(a2);
        }

        else
        {
            g[a1].push_back(a2);
            g[a2].push_back(a1);

            g[a1+m].push_back(a2+m);
            g[a2+m].push_back(a1+m);
        }
    }

    vis.resize(2*m, false);
    for_(i, 0, 2*m) dfs(i);

    comp.resize(2*m, -1);
    fill(all(vis), false);
    int i_comp = 0;
    while (!tempo.empty())
    {
        int cand = tempo.top(); tempo.pop();
        if (vis[cand]) continue;
        if (dfs_back(cand, i_comp++) == false) { cout << "NO\n"; return 0; }
    }

    cout << "YES\n";
    
    return 0;
}