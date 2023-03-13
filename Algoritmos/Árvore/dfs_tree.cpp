// Obj.: Passar por todos os vértices de uma árvore.
// Compl.: O(v), v = |vérices|

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 10000

vector<int> adj[MAX_N];

// Mais simples, pois não é possível chegar a um vértice de múltiplas direções.
void dfs_tree(int at, int prev)
{
    // Processar `at`
    for (auto viz : adj[at])
    {
        if (viz != prev) dfs_tree(viz, at);
    }
}