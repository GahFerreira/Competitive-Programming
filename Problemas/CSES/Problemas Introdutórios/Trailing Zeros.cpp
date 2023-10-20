/*
    A ideia é que o número de zeros no fim é igual ao menor entre:
        - Número de vezes que 2 divide n!
        - Número de vezes que 5 divide n!

    Como n! tem muito mais múltiplos de 2, basta contarmos quantos vezes 5 divide n!.

    Para isso, contamos quantos números múltiplos de 5 aparecem em n!.
        - A cada 5 números aparece um novo, logo a resposta é n/5.

    Entretanto, alguns múltiplos de 5 dividem 5 mais de uma vez, como por ex.: 25, 125, 625, etc.
    Como nós já contamos esses números 1 vez (ao fazer n/5), precisamos contar agora também quantos
    números múltiplos de 25 há em n!.
        - A cada 25 números aparece um novo, logo a resposta é n/25.
    
    Repetimos a mesma coisa para 125, 625, etc, até superarmos n.
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n;
    cin >> n;

    int resp = 0;

    for (int i = 5; i <= n; i *= 5) resp += n / i;

    cout << resp << '\n';

    return 0;
}