#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

#define str_to_lower(s) transform(s.begin(), s.end(), s.begin(), ::tolower)
#define str_to_upper(s) transform(s.begin(), s.end(), s.begin(), ::toupper)

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)
#define INF 1000000000 // Max int: 2147483647 & Max long long: 9223372036854775807

typedef long long ll;

// const int dx[8] = {+1, +0, -1, +0, +1, +1, -1, -1}, 
//           dy[8] = {+0, +1, +0, -1, -1, +1, -1, +1};

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    for_(i, 0, n) 
    {
        cin >> a[i];
        a[n+i] = a[i];
    }
    for_(i, 0, n) 
    {
        cin >> b[i];
        b[n+i] = b[i];
    }
    int k, l;
    cin >> k >> l;
    ll resp = 0, soma = 0;
    multiset<ll, greater<ll>> maiores, resto;
    priority_queue<ll> aux;

    // Primeiro processamento
    for (int i = 0, ini = n-k; i < k; i++)
    {
        soma += a[ini+i];
        aux.push(b[i]);
    }

    for (int i = 0; i < l; i++)
    {
        ll at = aux.top(); aux.pop();
        maiores.insert(at);
        soma += at;
    }
    
    while (!aux.empty())
    {
        ll at = aux.top(); aux.pop();
        resto.insert(at);
    }

    int ini = n-k, ult = ini+k-1, i = 0;
    while (true)
    {
        

        ++i;
    }

    return 0;
}