// Obj.: Passar por todos os vértices de uma árvore.
// Compl.: O(v), v = |vérices|

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 10000

vector<int> adj[MAX_N];
vector<int> nos_subarvore(MAX_N);

// `nos_subarvore[x]` guarda quantos nós existe na subárvore de `adj` cuja raiz é x.
void dfs(int at, int prev)
{
    nos_subarvore[at] = 1;

    for (auto viz : adj[at])
    {
        if (viz != prev) dfs (viz, at);
        nos_subarvore[at] += nos_subarvore[viz];
    }
}