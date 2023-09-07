#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> b(n);
        vector<int> resp;
        
        cin >> b[0];
        resp.push_back(b[0]);
        for_(i, 1, n)
        {
            cin >> b[i];
            int cand = min(b[i-1]-1, b[i]);
            if (cand != 0) resp.push_back(cand);
            resp.push_back(b[i]);
        }

        cout << resp.size() << '\n';
        for_(i, 0, resp.size())
        {
            cout << resp[i] << " ";
        }
        cout << '\n';
    }

    return 0;
}