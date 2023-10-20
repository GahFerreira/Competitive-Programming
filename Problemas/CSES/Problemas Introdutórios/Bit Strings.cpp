#include <bits/stdc++.h>

using namespace std;

#define INF 1'000'000'000

typedef long long ll;

const int MOD = INF + 7;

int exp2(int n)
{
    if (n == 0) return 1;

    ll u = exp2(n/2);
    u *= u;

    if (n&1) u *= 2;

    if (u >= MOD) u %= MOD;

    return (int) u;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n;
    cin >> n;

    cout << exp2(n) << '\n';

    return 0;
}