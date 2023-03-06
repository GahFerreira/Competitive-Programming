/*
Ideia:
    Simulação simples do jogo.
    Enquanto não houverem vencedores:
        Eu faço uma rodada:
            Dou uma carta a cada jogador.
            Se a carta for a menor até então, eu limpo o grupo dos eliminados intermediários, e incluo ele.
            Se for igual à menor, eu incluo ele no grupo citado.

        Ao final da rodada:
            Se as cartas acabaram, ou todos seriam eliminados:
                Todos vencem
            Se não eu elimino os pertencentes ao grupo dos eliminados.
            Chego então se sobrou só 1. Se sim, ele é o vencedor.
*/

#include <cstdio>
#include <vector>

#define INF 32

using namespace std;

typedef struct 
{
    char nome[17];
    bool eliminado;
} jogador_t;

jogador_t jogadores[20];
int qtd_jogadores;
int baralho[53];

void solve()
{
    int i_baralho = 0;
    int qtd_jogadores_atual = qtd_jogadores;

    // Jogo
    while (qtd_jogadores_atual > 1)
    {
        int menor_carta = INF;
        vector<int> jogadores_a_eliminar;

        // Início de uma rodada
        for (int i_jog = 0; i_jog < qtd_jogadores && i_baralho < 52; i_jog++, i_baralho++)
        {
            // Passo por todos os eliminados sem dar cartas
            while (jogadores[i_jog].eliminado == true)
            {
                i_jog++;

                if (i_jog >= qtd_jogadores) break;
            }
            if (i_jog >= qtd_jogadores) break;

            if (baralho[i_baralho] < menor_carta)
            {
                menor_carta = baralho[i_baralho];

                jogadores_a_eliminar.clear();
                jogadores_a_eliminar.push_back(i_jog);
            }

            else if (baralho[i_baralho] == menor_carta)
            {
                jogadores_a_eliminar.push_back(i_jog);
            }
        }

        // Após a rodada

        // Se as cartas acabaram, todos ganham
        if (i_baralho >= 52) break;

        // Se as cartas não acabaram: checo se todos empataram (se sim, todos ganham)
        if (qtd_jogadores_atual == (int) jogadores_a_eliminar.size()) break;

        // Se o jogo não acabou
        for (int i = 0; i < (int) jogadores_a_eliminar.size(); i++)
        {
            jogadores[ jogadores_a_eliminar[i] ].eliminado = true;    

            qtd_jogadores_atual--;
        }
    }

    // Printar resposta
    bool primeiro_jogador = true;

    for (int i = 0; i < qtd_jogadores; i++)
    {
        if (jogadores[i].eliminado == false)
        {
            if (primeiro_jogador) 
            { 
                printf("%s", jogadores[i].nome); 
                primeiro_jogador = false; 
            }

            else printf(" %s", jogadores[i].nome);
        }
    }

    printf(" \n"); // Espaço antes do '\n' porque no expected output estava assim

    return;
}

int main()
{  
    while (scanf("%d", &qtd_jogadores) == 1)
    {
        if (qtd_jogadores == 0) return 0;

        for (int i = 0; i < qtd_jogadores; i++)
        {
            scanf("%s", jogadores[i].nome);
            jogadores[i].eliminado = false;
        }

        for (int i = 0; i < 52; i++)
        {
            scanf("%d", &baralho[i]);
        }
        
        solve();
    }

    return 0;
}