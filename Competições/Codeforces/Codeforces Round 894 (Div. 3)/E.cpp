/*
    A observação mais importante:
        - O decréscimo do entretenimento é proporcional ao número de dias
        até assistir o último filme.

    Além disso, nunca vale a pena assistir um filme com entretenimento negativo, 
    portanto, nem os consideramos.

    Assim, podemos salvar sempre qual o maior entretenimento se considerarmos os primeiros 'i' filmes.
    Como podemos no máximo assistir 'm' filmes, guardamos os 'm' maiores entretenimentos dos filmes passados.

    Seja 'pd[i]' o melhor entretenimento se considerarmos os primeiros 'i' filmes.
    'pd[0]' = 0 (não consideramos nenhum filme).
    'pd[i]' = max entre
              {
                - pd[i-1] : Escolhemos não assistir ao i-ésimo filme
                - 'soma dos maiores m entretenimentos até agora' - (d*i)
              }
    
    Podemos usar um multiset para guardar os m maiores entretenimentos até o momento.
    Basta adicionar o filme atual ao multiset, e, caso ele tenha mais que 'm' elementos, retiramos o menor.
*/

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

typedef long long ll;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        ll n, m, d;
        cin >> n >> m >> d;
        vector<ll> a(n+1, 0), pd(n+1, 0);
        multiset<ll> sm;
        ll soma = 0;
        for_(i, 1, n+1) cin >> a[i];
        for_(i, 1, n+1)
        {
            if (a[i] <= 0) { pd[i] = pd[i-1]; continue; }
            soma += a[i];
            sm.insert(a[i]);
            if ((int) sm.size() > m)
            {
                soma -= *sm.begin();
                sm.erase(sm.begin());
            }
            pd[i] = max(pd[i-1], -d * i + soma);
        }

        cout << pd[n] << '\n';
    }

    return 0;
}