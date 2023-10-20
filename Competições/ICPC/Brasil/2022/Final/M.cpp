/*
Ideia:
  - Gerar um grafo de estados.
    - Seja 'g' o grafo de estados.
    - g[x][y] significa que:
      - Estamos na linha x
      - Movemos a porca y posições para a direita
    - Se não houver nenhuma ponta da porca em uma parede do labirinto, o estado é válido.
  - Iniciamos então uma busca partindo de cada estado válido na primeira linha.
    - Esses estados significam os vários modos de encaixar a porca no início do parafuso.
  - Usando apenas os estados válidos, tentamos chegar até a última linha do grafo.
    - Chegar à última linha significa que terminamos o desafio.
    - Não conseguir chegar à última linha significa que o desafio não tem solução.
  - Por fim, o movimento de virar a porca é equivalente a inverter a string da porca.
    - Portanto, se não conseguimos terminar o desafio com a string da porca inicial,
    invertemos ela e tentamos mais uma vez.

Algoritmo:
  - Para cada linha do tabuleiro: [O(r)]
    - Checamos se a porca movida em x posições para a direita gera um estado válido. [O(c)]
    (Fazemos isso para cada x possível. Note que mover c posições à direita é igual mover 0). 
      - Essa checagem pode ser feita comparando cada posição da porca e da linha atual. [O(c)] 
      - Marcamos então aquele estado de acordo.
  - Rodamos uma BFS (poderia ser também uma DFS) a partir de todos os estados válidos da
  linha 0 (primeira linha do labirinto).

Compl.: O(r*c²)
*/

#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)

typedef long long ll;

const int dx[] = {+1, +0, -1, +0}, 
          dy[] = {+0, +1, +0, -1};

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int r, c;
    cin >> r >> c;
    string s;
    cin >> s;
    vector<string> maze(r);
    for_(i, 0, r) cin >> maze[i];
    
    bool csg = false;
    queue<pair<int, int>> q;
    bool visitado[r][c];
    bool estado[r][c];

    for (int modo_string = 0; modo_string < 2; modo_string++, reverse(all(s)))
    {
        for_(i, 0, r) for_(j, 0, c) estado[i][j] = true;
        for_(i, 0, r) for_(j, 0, c) visitado[i][j] = false;

        // Gera grafo de estados.
        for (int rat = 0; rat < r; rat++)
        {
            for (int cini = 0; cini < c; cini++)
            {
                for (int cat = 0; cat < c; cat++)
                {
                    /*
                        `s[(c + c-cini + cat)%c]`: `c-cini` é o início da string.
                        Usando essa fórmula, ir de um estado x para x+1 na linha r,
                        significa mover a porca para a direita em uma unidade.

                        `s[(cini+cat)%c]` também funciona.
                        Nesse caso, ir pra direita no grafo de estados significaria mover
                        a porca para a esquerda (ou seja, o reverso).
                    */
                    if (s[(c + c-cini + cat)%c] == '1' and maze[rat][cat] == '1')
                    {
                        estado[rat][cini] = false;
                        break;
                    }
                }
            }
        }

        // Vetor de Estados - Útil para ver o caminho da BFS.
        // cout << "\nEstados:\n";
        // for_(i, 0, r)
        // {
        //     for_(j, 0, c)
        //     {
        //         cout << " " << estado[i][j]; 
        //     }
        //     cout << '\n';
        // }

        // Inicializa a BFS com as posições válidas da primeira linha.
        for (int cini = 0; cini < c; cini++)
        {
            if (estado[0][cini])
            {
                q.push({0, cini});
                visitado[0][cini] = true;
            }
        }

        while (!q.empty())
        {
            int rat, cini;
            tie(rat, cini) = q.front(); q.pop();

            // Se a 'row atual' é a última, chegamos ao final.
            // Ela só entraria na fila se fosse válida, então estamos num estado válido.
            if (rat == r-1)
            {
                csg = true;
                break;
            }

            // `nr: next_row, 'ncini': next_coluna_inicial`
            int nr, ncini;
            for (int dir = 0; dir < 4; dir++)
            {
                nr = rat + dy[dir];
                ncini = (cini + dx[dir] + c) % c;
                if (nr < 0 or nr >= r) continue;
                if (estado[nr][ncini] == false) continue;
                if (visitado[nr][ncini]) continue;
                q.push({nr, ncini});
                visitado[nr][ncini] = true;
            }
        }

        if (csg) break;
    }

    if (csg) cout << "Y\n";
    else cout << "N\n";

    return 0;
}