/*
    Para cada elemento menor igual à altura, acrescentamos 1 à resposta.
*/

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n, h;
    cin >> n >> h;
    int resp = 0;
    for_(i, 0, n)
    {
        int x;
        cin >> x;
        if (h >= x) ++resp;
    }

    cout << resp << '\n';

    return 0;
}