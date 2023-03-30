/*
Ideia:
    Temos dois problemas: um mais fácil se o número de linhas for par, e outro mais difícil se o número de linhas for ímpar.
    Dado número de linhas 'lin', número de colunas 'col'.

    A ideia é que para palavras de tamanho 'lin'-1, essas palavras ocupam uma coluna inteira sozinhas. Logo, elas não formam par.
    Para todas as outras palavras, se a entrada for válida, haverá uma outra palavra de tamanho tal que, se somados os tamanhos ...
    ... dessas duas palavras + 1, teremos 'lin'.
    Logo, podemos preencher o jogo usando esses pares, mais essas palavras especiais.
    
    'lin' par:
        Precisamos alocar as palavras de forma que não hajam quadrados pretos na mesma linha em colunas adjacentes.
        Isso só acontece se: 
            1 - A palavra da coluna anterior for de tamanho 'lin'-1 e a atual também, e colocarmos ambas começando na linha 1 ou 2.
            2 - O par de palavras da coluna anterior conter palavras do mesmo tamanho do par da coluna atual, e colocarmos as palavras ...
            ... de mesmo tamanho começando na linha 1.
        Para evitar os dois casos, basta que chequemos qual foi a linha do quadrado negro na coluna anterior.
        Se estivermos no caso 1, colocamos a palavra atual começando na linha 1 (quadrado negro na linha 'lin') ou começando na linha 2 ...
        ... (quadrado negro na linha 1), sendo que a escolha é o contrário do que foi feito na coluna anterior.
        Se estivermos no caso 2, escolhemos a palavra a ser colocada começando na linha 1 de forma que seu tamanho seja diferente ...
        ... do tamanho da palavra colocada na linha 1 na coluna anterior.
        Como 'lin' é par, temos 'lin'-1 quadrados disponíveis para ocupar com as palavras disponíveis atualmente. 'lin'-1 é ímpar, ...
        ... logo as palavras que escolhemos TÊM de ter tamanhos diferentes. Logo, podemos escolher a palavra a ser colocada a partir da linha 1 ...
        ... de forma a colocarmos o quadrado negro da coluna atual em posição diferente da coluna anterior.

    'lin' ímpar:
        Como 'lin' é ímpar, palavras de tamanho ('lin'-1)/2 formam pares com outras palavras de tamanho ('lin'-1)/2.
        Dessa forma, duas colunas adjacentes NUNCA podem ter pares de palavras tal que os tamanhos das palavras dos pares seja ('lin'-1)/2.
        Dado 'n' seja o número de palavras de tamanho ('lin'-1)/2.
        Para contornar o problema citado, as primeiras 'n' colunas ímpares terão pares de palavras de tamanho ('lin'-1)/2.
        Dessa forma, nas primeiras ('n'-1) colunas pares podemos colocar quaisquer pares / palavras de tamanho ('lin'-1).
        Assim, após as 'n' + ('n'-1) primeiras linhas, o problema se torna igual ao se 'lin' fosse par.
*/

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int sort_cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

#define for_(_i, _from, _to) for(int _i = _from; _i < _to; _i++)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int caso = 0;
    int lin, col, tam;

    while((cin >> lin >> col >> tam) && (lin != 0 && col != 0 && tam != 0))
    {
        cout << "#" << ++caso << endl;

        vector<int> resp; // Vetor em que se salva as respostas. Não printo direto, pois posso descobrir algum erro enquanto encontro a resposta.

        // lin par (Mais fácil!)
        if (lin % 2 == 0)
        {
            int p[tam];
            int qtd_lin_menos_1 = 0, n_palavras = 0;
            for_(i, 0, tam) 
            {
                int aux;
                cin >> aux;
                if (aux == lin-1) qtd_lin_menos_1++; // Mantemos um contador de palavras de tamanho 'lin'-1    
                else p[n_palavras++] = aux;
            }
            
            // Casos bases
            // 1 - n_palavras for ímpar (preciso formar pares de palavras de tamanho != lin-1)
            // 2 - a quantidade de palavras no total não ocupar exatamente a qtd de colunas disponível
            if (n_palavras%2 != 0) { cout << "0\n"; continue; }
            if (qtd_lin_menos_1 + n_palavras/2 != col) { cout << "0\n"; continue; }

            // Na implementação, decidi colocar as palavras de tamanho 'lin'-1 primeiro
            while(qtd_lin_menos_1--)
            {
                if (resp.empty()) resp.push_back(lin);
                else
                {
                    if (resp.back() == lin) resp.push_back(1);
                    else resp.push_back(lin);
                }
            }
            
            // Ordeno o tamanho das palavras p
            // Dessa forma, p[i_p] forma par com p[n_palavras-1 - i_p] (se não formar, então a entrada é inválida!)
            qsort(p, n_palavras, sizeof(int), sort_cmp);
            int i_p = 0;

            // Coloco os pares de palavras na resposta
            while (i_p < n_palavras/2)
            {
                // O par formado não completa a qtd de linhas (entrada inválida!)
                if(p[i_p] + p[n_palavras-1 - i_p] + 1 != lin)
                {
                    cout << "0\n";
                    resp.clear();
                    break;
                }

                if (resp.empty() || resp.back() != p[i_p] + 1) resp.push_back(p[i_p] + 1);
                else resp.push_back(p[n_palavras-1 - i_p] + 1);

                i_p++;
            }
        }

        // lin ímpar (Mais difícil!)
        else
        {
            int p[tam];
            int qtd_lin_menos_1 = 0, qtd_lin_sobre_2 = 0, n_palavras = 0;
            for_(i, 0, tam) 
            {
                int aux;
                cin >> aux;
                if (aux == lin-1) qtd_lin_menos_1++; // Mantemos um contador de palavras de tamanho 'lin'-1   
                else if (aux == lin/2) qtd_lin_sobre_2++; // Mantemos um contador de palavras de tamanho ('lin'-1)/2 (C++ arredonda a divisão pra baixo)
                else p[n_palavras++] = aux;
            }
            
            // Casos bases
            // 1 - n_palavras for ímpar (preciso formar pares de palavras de tamanho != lin-1 e != lin/2))
            // 2 - n de palavras de tamanho lin/2 for ímpar (preciso formar pares com elas também)
            // 3 - a quantidade de palavras no total não ocupar exatamente a qtd de colunas disponível
            if (n_palavras%2 != 0) { cout << "0\n"; continue; }
            if (qtd_lin_sobre_2%2 != 0) { cout << "0\n"; continue; }
            if (qtd_lin_menos_1 + qtd_lin_sobre_2/2 + n_palavras/2 != col) { cout << "0\n"; continue; }

            // Ordeno o tamanho das palavras p
            // Dessa forma, p[i_p] forma par com p[n_palavras-1 - i_p] (se não formar, então a entrada é inválida!)
            qsort(p, n_palavras, sizeof(int), sort_cmp);
            int i_p = 0;

            // Coloco as palavras de tamanho ('lin'-1)/2 nas primeiras 'n' linhas ímpares
            while (qtd_lin_sobre_2 > 0)
            {
                if (resp.empty() || resp.back() != lin/2 + 1) { resp.push_back(lin/2 + 1); qtd_lin_sobre_2-=2; }
                else
                {
                    // Nas linhas pares, tento primeiro colocar palavras de tamanho 'lin'-1
                    if (qtd_lin_menos_1 > 0)
                    {
                        resp.push_back(lin);
                        qtd_lin_menos_1--;
                    }

                    // Se não tiver mais palavras de tamanho 'lin'-1, coloco as palavras de p
                    else if (i_p < n_palavras/2)
                    {
                        if(p[i_p] + p[n_palavras-1 - i_p] + 1 != lin)
                        {
                            cout << "0\n";
                            resp.clear();
                            break;
                        }

                        resp.push_back(p[i_p] + 1);

                        i_p++;
                    }

                    // Não tenho o que usar entre duas colunas que usam par de ('lin'-1)/2
                    else
                    {
                        cout << "0\n";
                        resp.clear();
                        break;
                    }
                }
            }

            // Só acontece quando dou break:
            // 1 - Quando tento usar um de palavras de p, só que ele não completa 'lin'
            // 2 - Não tenho nada para usar entre duas colunas de par de ('lin'-1)/2
            if (qtd_lin_sobre_2 > 0) break;

            // Daqui para frente, é igual ao caso 'lin' par
            while(qtd_lin_menos_1--)
            {
                if (resp.empty()) resp.push_back(lin);
                else
                {
                    if (resp.back() == lin) resp.push_back(1);
                    else resp.push_back(lin);
                }
            }

            while (i_p < n_palavras/2)
            {
                // O par formado não completa a qtd de linhas (entrada inválida!)
                if(p[i_p] + p[n_palavras-1 - i_p] + 1 != lin)
                {
                    cout << "0\n";
                    resp.clear();
                    break;
                }

                if (resp.empty() || resp.back() != p[i_p] + 1) resp.push_back(p[i_p] + 1);
                else resp.push_back(p[n_palavras-1 - i_p] + 1);

                i_p++;
            }
        }
        
        for_(i, 0, (int) resp.size())
        {
            cout << resp[i] << " " << i+1 << endl;
        }
    }

    return 0;
}