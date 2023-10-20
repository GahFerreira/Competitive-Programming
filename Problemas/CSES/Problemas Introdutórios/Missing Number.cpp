#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n;
    cin >> n;
    vector<bool> achou(n+1, false);
    for_(i, 0, n-1)
    {
        int x;
        cin >> x;
        achou[x] = true;
    }

    for_(i, 1, n+1)
    {
        if (achou[i] == false)
        {
            cout << i << '\n';
            break;
        }
    }

    return 0;
}