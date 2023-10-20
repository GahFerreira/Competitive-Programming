#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(ll _i = _de; _i < (ll) _ate; ++_i)

typedef long long ll;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n;
    cin >> n;
    int a[n];
    for_(i, 0, n) cin >> a[i];

    ll resp = 0;
    int at = a[0];
    for_(i, 1, n)
    {
        at = max(at, a[i]);
        if (a[i] < at) resp += at - a[i];
    }

    cout << resp << '\n';

    return 0;
}