/*
    Se começarmos com um set vazio, notamos que sempre que adicionamos um elemento distinto, conseguimos
    formar +tamanho_set sorvetes.

    {} : Total de 0 sorvetes.

    Add(1) -> {+1} : +0 sorvetes (Total de 0 sorvetes)
    Add(2) -> {1, +2} : +1 sorvete (Total de 1 sorvete)
    Add(3) -> {1, 2, +3} : +2 sorvetes (Total de 3 sorvetes)
    Add(4) -> {1, 2, 3, +4} : +3 sorvetes (Total de 6 sorvetes)
    Add(5) -> {1, 2, 3, 4, +5} : +4 sorvetes (Total de 10 sorvetes)

    Vê-se então que temos um somatório dos naturais aqui.
    Se adicionarmos um elemento repetido a um set, conseguimos fazer exatamente +1 sorvete.

    {1, 2, 3} : Total de 3 sorvetes.

    Add(1) -> {1, +1, 2, 3} : +1 sorvete (Total de 4 sorvetes)
    Add(3) -> {1, 1, 2, 3, +3} : +1 sorvete (Total de 5 sorvetes)

    Essa é a melhor forma de construir os sets, pois sempre adicionando elementos distintos,
    conseguimos minimizar o tamanho do set, e caso precisemos formar um número entre os totais
    das somas dos naturais, apenas adicionamos os elementos repetidos necessários.
    
    Assim, basta fazer uma busca binária na quantidade pedida, visando encontrar o maior set
    de elementos distintos que seja menor que a quantidade pedida.

    Por fim, completamos esse set com a diferença entre o quanto ele realmente produz, e quanto precisamos.
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n;
ll f(ll a)
{
    if ((a * (a+1) / 2) > n) return true;
    return false;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;

        ll alvo = -1;
        for (ll b = 2 * (1e9); b >= 1; b /= 2)
        {
            while (!f(alvo+b)) alvo += b;
        }
        
        cout << alvo+1 + (n - ((alvo*(alvo+1)) / 2)) << '\n';
    }

    return 0;
}