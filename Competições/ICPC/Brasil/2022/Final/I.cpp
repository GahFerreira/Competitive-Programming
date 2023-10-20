/*
Ideia:
  - Começamos uma busca a partir de cada posição da matriz.
    - Em cada busca, ao visitarmos um vértice, agendamos a visita de todos seus vizinhos
    com valor maior (de forma a não ser possível agendar o mesmo vértice duas vezes).
    - Dessa forma, se chegamos a um vértice, é porque viemos de um vértice de valor menor.
    - Enfim, começando a busca de cada posição da matriz, obtemos o melhor de todos os resultado parciais.

- Compl.: O(n⁴), n² buscas que visitam n² elementos.
*/

#include <bits/stdc++.h>
using namespace std;

const int dy[] = {-1, 0, 1, 0}, dx[] = {0, 1, 0, -1};

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int r, c;
    cin >> r >> c;
    int a[r][c];
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> a[i][j];
        }
    }

    // Marca os vértices que não tem vizinhos válidos como não expansíveis.
    vector<bool> expansivel(r*c+1, false);

    for (int rat = 0; rat < r; rat++)
    {
        for (int cat = 0; cat < c; cat++)
        {
            for (int dir = 0; dir < 4; dir++)
            {
                int nr = rat + dy[dir], nc = cat + dx[dir];
                if (nr < 0 or nr >= r or nc < 0 or nc >= c) continue;
                if (a[rat][cat] < a[nr][nc])
                {
                    expansivel[a[rat][cat]] = true;
                    continue;
                }
            }
        }
    }

    vector<bool> visitado(r*c+1);
    vector<bool> visitado_em_alguma_busca(r*c+1, false);
    queue<pair<int, int>> q;
    int melhor = -1, soma;

    for (int rini = 0; rini < r; rini++)
    {
        for (int cini = 0; cini < c; cini++)
        {
            // Se em alguma busca já chegamos a esse vértice, então a resposta daquela
            // busca será maior que uma começando neste vértice.
            if (visitado_em_alguma_busca[a[rini][cini]]) continue;

            for (int i = a[rini][cini]+1; i < r*c+1; i++) visitado[i] = false;
            soma = 0;
            
            q.push({rini, cini});
            visitado[a[rini][cini]] = true;
            visitado_em_alguma_busca[a[rini][cini]] = true;
            soma++;

            while (!q.empty())
            {
                int rat, cat;
                tie(rat, cat) = q.front(); q.pop();

                for (int dir = 0; dir < 4; dir++)
                {
                    int nr = rat + dy[dir], nc = cat + dx[dir];
                    if (nr < 0 or nr >= r or nc < 0 or nc >= c) continue;
                    if (visitado[a[nr][nc]]) continue;
                    if (a[nr][nc] < a[rat][cat]) continue;
                    if (expansivel[a[nr][nc]]) q.push({nr, nc}); 
                    visitado[a[nr][nc]] = true;
                    visitado_em_alguma_busca[a[nr][nc]] = true;
                    soma++;
                }
            }

            if (soma > melhor) melhor = soma;
        }
    }

    cout << melhor << '\n';

    return 0;
}