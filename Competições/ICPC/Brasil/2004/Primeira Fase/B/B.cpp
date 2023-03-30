/*
Ideia:
    Eu crio o seguinte grafo:
        Cada estação é um vértice.

        Para cada itinerário de trem, eu ligo as estações adjacentes por uma aresta de custo:
            0, se as estações forem da mesma zona
            4, se as estações forem de zonas diferentes

        Para cada itinerário de ônibus, eu ligo cada estação do itinerário com todas as outras, por arestas de custo 1.

        Notas: 
            Se duas estações não são ligadas, a aresta entre elas tem custo infinito.
            Eu só mantenho a aresta de menor custo entre duas estações.
            'grafo[a][b]' vai ser igual 'grafo[b][a]'.

    Depois de montado o grafo, eu passo um Dijkstra (sem fila de prioridade), com início na estação 'x' e fim na estação 'y'.
*/

#include <iostream>
#include <vector>

using namespace std;

#define for_(_i, _from, _to) for(int _i = _from; _i < _to; _i++)

#define INF (1 << 30)

int main()
{
    int z, s;

    cin >> z >> s;

    while (z != 0 || s != 0)
    {
        vector<vector<int>> zonas(z);
        for_(i, 0, z)
        {
            int k;
            cin >> k;
            zonas[i].reserve(k);
            for_(j, 0, k)
            {
                int estacao;
                cin >> estacao;
                zonas[i].push_back(estacao);
            }
        }
        int t, b;
        cin >> t >> b;
        vector<vector<int>> itinerarios_trem(t);
        vector<vector<int>> itinerarios_onibus(b);
        for_(i, 0, t)
        {
            int l;
            cin >> l;
            itinerarios_trem[i].reserve(l);
            for_(j, 0, l)
            {
                int estacao;
                cin >> estacao;
                itinerarios_trem[i].push_back(estacao);
            }
        }
        for_(i, 0, b)
        {
            int l;
            cin >> l;
            itinerarios_onibus[i].reserve(l);
            for_(j, 0, l)
            {
                int estacao;
                cin >> estacao;
                itinerarios_onibus[i].push_back(estacao);
            }
        }
        int x, y;
        cin >> x >> y;

        // Solve
        {
            // Montagem do grafo
            int grafo[s+1][s+1];
            for_(i, 0, s+1) for_(j, 0, s+1) grafo[i][j] = INF;

            // Definindo a zona de cada estação
            int zona_estacao[s+1];
            for_(i, 0, (int) zonas.size()) for_(j, 0, (int) zonas[i].size()) zona_estacao[ zonas[i][j] ] = i;

            // Adicionando valores das estações de trem
            for_(i, 0, (int) itinerarios_trem.size())
            {
                for_(j, 0, (int) itinerarios_trem[i].size()-1)
                {
                    int valor;
                    int estacao_atual = itinerarios_trem[i][j];
                    int proxima_estacao = itinerarios_trem[i][j+1];
                    
                    // Se duas estações do mesmo itinerário de trem estão na mesma zona, o valor entre elas é 0 
                    // Se não, o valor é 4 (mudança de estação)
                    if (zona_estacao[estacao_atual] == zona_estacao[proxima_estacao]) valor = 0;
                    else valor = 4;

                    // Em tese, desnecessário, pois sempre deve dar true
                    if (grafo[estacao_atual][proxima_estacao] > valor)
                    {
                        grafo[estacao_atual][proxima_estacao] = valor;
                        grafo[proxima_estacao][estacao_atual] = valor;
                    }
                }
            }

            // Adicionando valores das estações de ônibus
            for_(i, 0, (int) itinerarios_onibus.size())
            {
                for_(j, 0, (int) itinerarios_onibus[i].size()-1)
                {
                    int estacao_atual = itinerarios_onibus[i][j];

                    for_(k, j+1, (int) itinerarios_onibus[i].size())
                    {
                        int proxima_estacao = itinerarios_onibus[i][k];

                        if (grafo[estacao_atual][proxima_estacao] > 1)
                        {
                            grafo[estacao_atual][proxima_estacao] = 1;
                            grafo[proxima_estacao][estacao_atual] = 1;
                        }
                    }
                }
            }

            // Dijkstra
            // 'estacoes' guarda um par { dist_ate_x, vertice_anterior_no_caminho_ate_X }
            vector<pair<int, int>> estacoes;
            vector<int> nao_visitados;
            bool visitados[s+1];
            estacoes.reserve(s+1);
            nao_visitados.reserve(s);

            for_(i, 0, s+1) estacoes.push_back( { INF, -1 } );
            for_(i, 1, s+1) nao_visitados.push_back(i);
            for_(i, 1, s+1) visitados[i] = false;
            estacoes[x].first = 0;

            while(nao_visitados.empty() == false)
            {
                // Obtendo próximo vértice de menor custo
                int i_estacao_atual = 0;
                for_(i, 1, (int) nao_visitados.size())
                {
                    if (estacoes[ nao_visitados[i] ].first < estacoes[ nao_visitados[i_estacao_atual] ].first)
                    {
                        i_estacao_atual = i;
                    }
                }

                int estacao_atual = nao_visitados[i_estacao_atual];

                visitados[estacao_atual] = true;
                nao_visitados.erase( nao_visitados.begin() + i_estacao_atual );

                for_(proxima_estacao, 1, s+1)
                {
                    // Se eu não visitei ainda a proxima_estacao e existe aresta entre ela e a estação atual
                    if (visitados[proxima_estacao] == false && grafo[estacao_atual][proxima_estacao] != INF)
                    {
                        if (estacoes[estacao_atual].first + grafo[estacao_atual][proxima_estacao] < 
                            estacoes[proxima_estacao].first)
                        {
                            estacoes[proxima_estacao].first = estacoes[estacao_atual].first + grafo[estacao_atual][proxima_estacao];
                            estacoes[proxima_estacao].second = estacao_atual;
                        }
                    }
                }
            }

            cout << estacoes[y].first + 2 << endl;
        }

        cin >> z >> s;
    }

    return 0;
}