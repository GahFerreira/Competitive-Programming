// Obj.: Passar por todos os vértices de uma árvore.
// Compl.: O(v), v = |vérices|

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 10000

// Mais simples, pois não é possível chegar a um vértice de múltiplas direções.

vector<int> adj[MAX_N];

void dfs_tree(int at, int prev)
{
    // Processar `at`
    for (auto viz : adj[at])
    {
        if (viz == prev) continue;
        
        dfs_tree(viz, at);
    }
}