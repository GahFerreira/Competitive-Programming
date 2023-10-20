#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

#define all(x) x.begin(), x.end()

int prefix_function(const string& s, int d)
{
    const int n = (int)s.length();
    vector<int> lps(1, 0);

    if (n <= d) return n;

    for (int i = 1; i < n; ++i)
    {
        int j = lps[i-1];

        while (j > 0 and s[i] != s[j]) j = lps[j-1];

        if (s[i] == s[j]) ++j;

        lps.push_back(j);

        // Primeiro caractere após D caracteres da LPS é 0, então printa D caracteres.
        if (i == d and lps[i] == 0) return d;

        // Algum caractere após D+1 caracteres faz a substring não ser mais cíclica.
        if (i > d and lps[i-1] >= lps[i]) return i;
    }

    // Computou LPS até o fim (achou substring cíclica de tamanho até D).
    return n;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    string s;
    int d;
    cin >> s >> d;

    if ((int)s.size() == d)
    {
        cout << "1\n";
        return 0;
    }

    int start = 0;
    int resp = 0;

    while (start < (int) s.size())
    {
        start += prefix_function(s.substr(start), d);
        ++resp;
    }

    cout << resp << '\n';

    return 0;
}