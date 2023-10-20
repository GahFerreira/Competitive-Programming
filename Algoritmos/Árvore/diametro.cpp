// Obj.: Calcular o diâmetro da árvore; o maior caminho entre dois nós.
// Compl.: O(n)
// A ideia é chegar em um dos extremos da árvore na 1ª DFS 
// e descobrir a distância até o outro com a 2ª.

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 10000

vector<int> adj[MAX_N];

pair<int, int> find_ab(int at, int prev, int dist)
{
    // `dist` primeiro para `max` priorizá-la.
    pair<int, int> melhor = {dist, at};

    for (auto viz : adj[at])
    {
        if (viz == prev) continue;

        melhor = max(melhor, find_ab(viz, at, dist+1));
    }

    return melhor;
}

// O vértice inicial pode ser arbitrário, mas tem que pertencer à árvore.
void diameter(int ini)
{
    int a = find_ab(ini, -1, 0).second;
    int b = find_ab(a, -1, 0).second;
}