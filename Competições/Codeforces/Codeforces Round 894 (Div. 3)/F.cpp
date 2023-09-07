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
        ll w, f, n;
        cin >> w >> f >> n;
        int a[n];
        for_(i, 0, n) cin >> a[i];
        ll soma = 0;
        for_(i, 0, n) soma += a[i];

        // Knapsack, usando bitset para representar se consigo formar 'x' usando uma subcoleção de 'a'.
        bitset<1000001> pd;
        pd[0] = true;
        for_(i, 0, n) pd |= pd << a[i];
        
        ll resp = 1000000;
        
        // Como eu itero por todas as possibilidades de soma, se soma = p+q, pd[p] é true e pd[q] também.
        // Assim, quando eu ofereço 'p' para água matar, ofereço 'q' para fogo, mas eventualmente
        // oferecerei 'q' para água e 'p' para fogo.
        // Isso porque tanto 'p' quanto 'q' são <= 10^6, logo estão em pd.
        for_(soma_parte_inimigos, 0, soma+1)
        {
            if (pd[soma_parte_inimigos] == true)
            {
                // Aqui vejo qual a menor quantidade de dias para eu obter a água/fogo suficiente
                // para matar seus respectivos monstros.

                // O 'w-1' (ou 'f-1') é para evitar o arredondamento para baixo na divisão entre inteiros.
                ll qtd_dias_p_obter_agua_suficiente_para_matar = (soma_parte_inimigos + (w-1)) / w;
                ll qtd_dias_p_obter_fogo_suficiente_para_matar = (soma - soma_parte_inimigos + (f-1)) / f;

                resp = min(resp, max(qtd_dias_p_obter_agua_suficiente_para_matar,
                                     qtd_dias_p_obter_fogo_suficiente_para_matar));
            }
        }

        cout << resp << '\n';
    }

    return 0;
}