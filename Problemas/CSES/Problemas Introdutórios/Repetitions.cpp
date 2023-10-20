#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    string s;
    cin >> s;
    int mx = 1, at = 1;
    for_(i, 1, s.size())
    {
        if (s[i] == s[i-1]) mx = max(mx, ++at);
        else at = 1;
    }

    cout << mx << '\n';

    return 0;
}