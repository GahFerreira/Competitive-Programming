/*
Ideia:
  - Apenas simular.

Compl.: O(n)
*/

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n, h, w;
    cin >> n >> h >> w;

    for_(i, 0, n)
    {
        char f, s;
        cin >> f >> s;

        if (f == 'Y' or w == 0)
        {
            cout << "Y ";
            h--; w++;
        }
        else cout << "N ";

        if (s == 'Y' or h == 0)
        {
            cout << "Y\n";
            h++; w--;
        }
        else cout << "N\n";
    }

    return 0;
}