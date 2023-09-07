/*
    A solução desse problema está nas seguintes observações:
        - Um array ordenado de números distintos terá um vetor de diferenças em que
        cada posição terá um número positivo.
        - Aplicar a fórmula do enunciado (a0 += n, a1 += n-1 ... an += 1) diminui cada posição do
        vetor de diferenças em 1 por iteração.
       
       *-* O número de iterações será a maior diferença do vetor de diferenças.

        - Além disso, nota-se que: o último elemento do vetor nunca será ultrapassado em tamanho
        no final de uma iteração.
            - Isso porque o número na posição i vai receber 'n-i' na iteração, mas ele está também
            'n-i' posições distante do último.
            - E como a diferença entre cada número é de pelo menos +1, estar 'n-i' posições distante
            do último significa que o número da posição i precisa de pelo menos 'n-i' a mais para
            alcançar o último.
                - Note que isso só ocorre porque não há elementos repetidos no vetor!
        - Portanto, sempre que um elemento se iguala ao último, podemos removê-lo do vetor.
        
       *-* Assim, o último elemento sempre ficará vivo, e será o último elemento a ser removido.

        - Como nós sabemos que o número de iterações será a maior diferença do vetor de diferenças,
        e que o último elemento do vetor será o último a ser removido, a resposta final será:
            - n_iterações + valor_ultimo_elemento.

    Para sabermos o maior elemento do vetor e a maior diferença, podemos usar dois multisets.
        - Para iniciar os multisets, gastamos O(n * lg(n)).
    Depois, para cada query, fazemos um número fixo de operações nos multisets.
        - Como cada operação gasta O(lg(n)), gastamos ao todo (q * lg(n)).
    
    Por fim, a complexidade será O((n+q) * lg(n)).
*/

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(ll _i = _de; _i < (ll) _ate; ++_i)
#define INF 1000000000 // Max ll: 2147483647 & Max long long: 9223372036854775807

typedef long long ll;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    ll t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        vector<ll> a(n);
        for_(i, 0, n) cin >> a[i];

        multiset<ll> ns, ds;
        for_(i, 0, n) ns.insert(a[i]);

        for (auto it = ns.begin(); ;)
        {
            ll prev = *it;

            if (++it != ns.end())
            {
                ds.insert(*it - prev);
            }

            else break;
        }

        ll q;
        cin >> q;
        for_(i_q, 0, q)
        {
            ll pos, x;
            cin >> pos >> x;
            --pos;

            // Se só 1 elemento, só ele pode ser atualizado.
            if (n == 1) { cout << x << ' '; continue; }

            // Extraio o anterior e próximo do elemento a ser removido do multiset.
            ll prev = -INF, next = -INF;
            auto it = ns.find(a[pos]);
            if (it != ns.begin())
            {
                --it;
                prev = *it;
                ++it;
            }
            if (++it != ns.end())
            {
                next = *it;
            }
            --it;

            // Retiro o elemento.
            // Caso: o elemento NÃO é o maior/menor do multiset.
            ns.erase(it);
            if (prev != -INF and next != -INF)
            {
                ds.insert(next-prev);

                ds.erase(ds.find(a[pos] - prev));
                ds.erase(ds.find(next - a[pos]));
            }

            // Caso: o elemento É o maior/menor do multiset.
            else
            {
                // Caso: maior do multiset.
                if (prev != -INF) ds.erase(ds.find(a[pos] - prev));

                // Caso: menor do multiset.
                else ds.erase(ds.find(next - a[pos]));
            }

            // Adiciono o novo elemento.
            // Casos análogos aos anteriores.
            a[pos] = x;
            prev = -INF, next = -INF;

            it = ns.insert(a[pos]);
            if (it != ns.begin())
            {
                --it;
                prev = *it;
                ++it;
            }
            if (++it != ns.end())
            {
                next = *it;
            }

            if (prev != -INF and next != -INF)
            {
                ds.erase(ds.find(next-prev));

                ds.insert(a[pos] - prev);
                ds.insert(next - a[pos]);
            }

            else
            {
                if (prev != -INF) ds.insert(a[pos] - prev);
                else ds.insert(next - a[pos]);
            }

            cout << *ns.rbegin() + *ds.rbegin() << ' ';
        }

        cout << '\n';
    }

    return 0;
}