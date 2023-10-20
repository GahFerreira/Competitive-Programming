/*
    A ideia é guardar quantos subvetores com uma quantidade ímpar/par de 1s termina na posição 'i'.

    Se 'a[i]' for 1:
        - Temos garantidamente +1 subvetor com nº ímpar de 1s que termina em 'i'.
        - Para cada subvetor com nº par de 1s que termina em 'i-1', conseguimos formar
        um novo subvetor com nº ímpar de 1s que termina em 'i'.
        - Para cada subvetor com nº ímpar de 1s que termina em 'i-1', conseguimos formar
        um novo subvetor com nº par de 1s que termina em 'i'.

    Se 'a[i]' for 0:
        - Temos garantidamente +1 subvetor com nº par de 1s que termina em 'i'.
        - Para cada subvetor com nº par de 1s que termina em 'i-1', conseguimos formar
        um novo subvetor com nº par de 1s que termina em 'i'.
        - Para cada subvetor com nº ímpar de 1s que termina em 'i-1', conseguimos formar
        um novo subvetor com nº ímpar de 1s que termina em 'i'.

    Assim, temos a informação de quantos subvetores com nº ímpar de 1s terminam em cada 'i'.
    Portanto, basta somar essa informação para todos os 'i's.
*/

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(ll _i = _de; _i < (ll) _ate; ++_i)

using ll = long long;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n;
    cin >> n;
    int a[n];
    for_(i, 0, n) cin >> a[i];

    ll imp[n];
    ll par[n];

    imp[0] = a[0];
    par[0] = 1 - a[0];

    for_(i, 1, n)
    {
        if (a[i] == 1)
        {
            imp[i] = 1 + par[i-1];
            par[i] = imp[i-1];
        }

        else 
        {
            par[i] = 1 + par[i-1];
            imp[i] = imp[i-1];
        }
    }

    ll total = 0;
    for_(i, 0, n)
    {
        total += imp[i];
    }

    cout << total << '\n';

    return 0;
}