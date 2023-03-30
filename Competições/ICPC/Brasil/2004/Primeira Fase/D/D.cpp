/*
Problema:
    Eu recebo um número de caixas que preciso vender 'n' e todas as caixas do estoque.
    Eu recebo o volume do produto que preciso colocar na caixa.
    Nota: o cliente quer 'n' caixas IGUAIS.
    A resposta é:
        Se eu tiver 'n' de uma caixa no estoque && essa caixa couber o produto: essa caixa é um candidato.
        Eu olho todos os meus candidatos e escolho a que tiver menor diferença entre o volume da caixa e o volume do produto.
        Eu printo essa menor diferença.

Ideia:
    Eu ordeno as dimensões do produto, e de todas as caixas do estoque (já que posso girar a caixa como eu quiser).
    Dessa forma, consigo checar se o produto cabe na caixa, checando as dimensões individualmente.
    Caso em uma caixa não caiba o produto, eu nem incluo essa caixa no estoque.

    Eu ordeno as caixas, de forma que caixas iguais fiquem adjacentes no estoque (ordeno pela menor dimensão, então pela segunda menor, por fim terceira menor).

    Busco no estoque por caixas que tenham 'n' cópias.
    Quando eu encontrar, eu salvo a diferença do volume dessa caixa e o volume do produto.
    
    No final, eu tenho:
        1 - A menor diferença entre volume da caixa e volume produto
        2 - Não encontrei nenhuma caixa com 'n' cópias, logo a resposta é 'impossível'
*/

#include <iostream>

using namespace std;

#define for_(_i, _from, _to) for(int _i = _from; _i < _to; _i++)

#define INF (1 << 30)

// Ordena em ordem crescente
int sort_cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

// Ordena um vetor de 3 elementos, com maior peso no elemento na posição 0, depois posição 1, depois posição 2
int sort_cmp2(const void *a, const void *b)
{
    int *x = (int *) a;
    int *y = (int *) b;

    if (x[0] < y[0]) return -1;
    else if (x[0] > y[0]) return 1;

    if (x[1] < y[1]) return -1;
    else if (x[1] > y[1]) return 1;

    if (x[2] < y[2]) return -1;
    else if (x[2] > y[2]) return 1;

    return 0;
}

int main()
{
    int caso = 0;

    int n, m;
    cin >> n >> m;
    while(n != 0)
    {
        int dim_alvo[3];
        int caixas[m][3];

        for_(i, 0, 3) cin >> dim_alvo[i];
        qsort(dim_alvo, 3, sizeof(int), sort_cmp);  // Ordeno em ordem crescente

        int n_caixas = 0;
        for_(i, 0, m) 
        {
            int aux[3];
            for_(i, 0, 3) cin >> aux[i];
            qsort(aux, 3, sizeof(int), sort_cmp);

            // Se a caixa for inválida (não cabe o produto), nem inclui ela na lista
            // Infelizmente, no pior caso, todas devem ser válidas, então isso aqui só atrasa
            // Mas é um pré-processamento argumentavelmente interessante ainda assim
            if (aux[0] < dim_alvo[0] ||
                aux[1] < dim_alvo[1] ||
                aux[2] < dim_alvo[2])
            {
                continue;
            }

            caixas[n_caixas][0] = aux[0];
            caixas[n_caixas][1] = aux[1];
            caixas[n_caixas][2] = aux[2];
            ++n_caixas;
        }
        
        for_(i, 0, n_caixas) qsort(caixas[i], 3, sizeof(int), sort_cmp); // Ordem crescente
        qsort(caixas, n_caixas, sizeof(int[3]), sort_cmp2); // Deixo todas as caixas de tamanho igual juntas na lista

        int qtd_caixas_validas = 0;
        int menor_diferenca = INF;
        int volume_produto = dim_alvo[0] * dim_alvo[1] * dim_alvo[2];

        for (int i = 0; i < n_caixas; i++)
        {
            if (i != 0)
            {
                // Se a caixa que estou analisando é diferente das que estava analisando previamente
                if (caixas[i][0] != caixas[i-1][0] || 
                    caixas[i][1] != caixas[i-1][1] || 
                    caixas[i][2] != caixas[i-1][2])
                {
                    qtd_caixas_validas = 0;
                }
            }

            // Se o produto cabe na caixa atual
            if (caixas[i][0] >= dim_alvo[0] &&
                caixas[i][1] >= dim_alvo[1] &&
                caixas[i][2] >= dim_alvo[2])
            {
                ++qtd_caixas_validas;

                // Se eu tenho n elementos de alguma caixa, ela é uma candidata à melhor resposta
                if (qtd_caixas_validas == n)
                {
                    int volume_caixa_atual = caixas[i][0] * caixas[i][1] * caixas[i][2];

                    if ((volume_caixa_atual - volume_produto) < menor_diferenca)
                    {
                        menor_diferenca = (volume_caixa_atual - volume_produto);
                    }
                }
            }
        }

        if (menor_diferenca == INF) cout << "impossible\n";
        else cout << menor_diferenca << endl;

        cin >> n >> m;
    }

    return 0;
}