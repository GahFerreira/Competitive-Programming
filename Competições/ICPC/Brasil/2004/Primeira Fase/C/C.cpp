/*
Ideia:
    É um problema de simulação.

    Constrói-se o seguinte grafo:
        Se a cidade x tem estrada para a cidade y, e a estrada tem n km:
        grafo[x][y] = grafo[y][x] = n
    
    Enquanto o número de turnos for maior que 0:
        Se eu estiver em uma cidade:
            Procuro a cidade (de menor índice) com maior "idleness".
            Coloco em um contador o tamanho da estrada entre a cidade atual e essa próxima cidade.
        
        Se não (eu estou na estrada):
            Realizo um passo na estrada, composto pelo seguinte:
                Aumento 1 na "idleness" de todas as cidades, e somo esse valor acrescido à minha resposta.
                Decremento o número de turnos em 1, e o contador em 1.
            
            Se após esse passo eu tiver chegado a alguma cidade:
                Eu decremento o "idleness" da cidade que eu cheguei da resposta (afinal, havia acrescentado erroneamente na instrução anterior)
                Atribuo 0 ao "idleness" dessa cidade
    
    Quando o número de turnos acabar, a minha resposta será o total de "idleness" de todas as minhas cidades após 'n' turnos.
*/

#include <iostream>

using namespace std;

#define for_(_i, _from, _to) for(int _i = _from; _i < _to; _i++)

int grafo[1010][1010];

int main()
{
    int c, r, n, s;
    
    cin >> c >> r >> n >> s;

    while (c != 0 && r != 0 && n !=0 && s != 0)
    {
        for_(i, 0, c+1) for_(j, 0, c+1) grafo[i][j] = -1;

        for_(i, 0, r)
        {
            int x, y, d;
            cin >> x >> y >> d;
            grafo[x][y] = d;
            grafo[y][x] = d;
        }

        // 'ci' significa "city idleness"
        int ci[c+1];
        for_(i, 0, c+1) ci[i] = 0;

        int resp = 0;

        // Começo na cidade 's'
        while(n > 0)
        {
            // Encontrar próxima cidade (a partir da cidade atual (s))
            int i_max = -1;
            for_(i, 1, c+1)
            {
                if (grafo[s][i] != -1)
                {
                    if (i_max == -1 || ci[i] > ci[i_max]) i_max = i;
                }
            }
            int cont = grafo[s][i_max];
            s = i_max;
            // Realizo um passo
            while (cont > 0 && n > 0)
            {
                cont--;
                n--;
                // Aumento o "idleness" de todas as cidades em 1, e somo o valor acrescido à resposta
                for_(i, 1, c+1)
                {
                    ci[i]++;
                    resp+= ci[i];
                }
                // Cheguei na cidade s no passo atual, retiro seu "idleness" da resposta e o reseto
                if (cont == 0)
                {
                    resp-= ci[s];
                    ci[s] = 0;
                }
            }
        }

        cout << resp << endl;

        cin >> c >> r >> n >> s;
    }

    return 0;
}