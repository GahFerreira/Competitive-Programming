/*
    Sempre vale a pena fazer todas as atividades recreativas primeiro.
        - Ou seja, soma-se à disposição inicial os valores de cada atividade recreativa.
    Posteriormente, vê até qual atividade cansativa consegue-se fazer.
*/

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int d, c, r;
    cin >> d >> c >> r;

    vector<int> cans(c);
    for_(i, 0, c) cin >> cans[i];

    for_(i, 0, r)
    {
        int x;
        cin >> x;
        d += x;
    }

    int resp = r;
    for_(i, 0, c)
    {
        if ((d -= cans[i]) >= 0) ++resp;
        else break;
    }

    cout << resp << '\n';

    return 0;
}