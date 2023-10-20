#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    ll n;
    cin >> n;

    cout << n;

    while (n > 1)
    {
        if (n & 1) n = n*3 + 1;
        else n /= 2;

        cout << ' ' << n;
    }

    cout << '\n';

    return 0;
}