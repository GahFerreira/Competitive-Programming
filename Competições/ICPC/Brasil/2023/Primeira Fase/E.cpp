/*
    Nota: Eu estou chamando o valor de elementos de "altura" na explicação.
          Não sei bem o porquê. ¯\_(ツ)_/¯
    
    Inicialmente, pré-computa-se para cada valor o que ele se tornará ao ser colhido.
        Ex.: pd[123] = 123 - (1+2+3);
    
    Para todo valor distinto da configuração inicial, guarda-se a quantidade de vezes
    que ele aparece, e a informação que ele aparece (numa priority_queue).

    Então, processa-se a simulação em lotes.

    Para a maior altura, checa-se quantas vezes ela aparece.
        1. Se for maior igual a k, sabe-se que aquela altura é a resposta.
            1.1 É necessário manipular aquela altura para gerar o valor do pólen.
        2. Se for menor que k, significa que todas aquelas flores serão processadas antes
        de chegar à resposta. 
            2.1 Sabemos que se a altura atual é 'x', todas aquelas flores se tornarão 'pd[x]'.
            2.2 Portanto, basta adicionar 'pd[x]' à lista das alturas que existem (priority_queue),
                e remover aquela quantidade de 'k', e adicionar aquela quantidade a 'qtd[pd[x]]'.
        
    Eventualmente:
        1. Ou a altura se torna 0, e é garantido que responderemos 0.
            1.1 Note que mesmo que não tratarmos o caso 'at' ser igual a 0 no if
                não dará TLE.
            1.2 Isso porque como 'qtd[pd[at]] = qtd[at]', mesmo que inicialmente
                'qtd[0]' seja 1, o valor dobra por iteração.
            1.3 Dessa forma, temos no máximo log(k) operações.
            1.4 Ex.: Caso "1 1000000000 1".
        2. Ou a quantidade é >= k, portanto responderemos à altura atual.
*/

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

#define INF 1'000'000'000

const int MAXN = 1'000'005;
int pd[MAXN];
int qtd[MAXN];

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    for_(i, 0, MAXN)
    {
        qtd[i] = 0;

        int x = i;
        pd[i] = x;

        while (x > 0)
        {
            pd[i] -= x % 10;
            x /= 10;
        }
    }

    int n, k;
    cin >> n >> k;

    priority_queue<int> q;
    for_(i, 0, n)
    {
        int x;
        cin >> x;
        if (qtd[x] == 0) q.push(x);
        ++qtd[x];
    }

    while (true)
    {
        int at = q.top(); q.pop();

        if (qtd[at] >= k)
        {
            int resp = 0;
            while (at > 0)
            {
                resp += at % 10;
                at /= 10;
            }

            cout << resp << '\n';

            return 0;
        }

        if (qtd[pd[at]] == 0) q.push(pd[at]);
        qtd[pd[at]] += qtd[at];
        k -= qtd[at];
    }

    return 0;
}