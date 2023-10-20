// Obj.: Passar por todos os vértices de uma árvore.
// Compl.: O(v), v = |vérices|

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 10000

vector<int> adj[MAX_N];
int subt[MAX_N];

// `subt[x]` guarda quantos nós existe na subárvore de `adj` cuja raiz é x.
void dfs(int at, int prev)
{
    subt[at] = 1;

    for (auto& viz : adj[at])
    {
        if (viz == prev) continue;
        dfs (viz, at);
        subt[at] += subt[viz];
    }
}