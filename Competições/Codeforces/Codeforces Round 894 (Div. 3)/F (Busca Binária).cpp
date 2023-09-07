/*
    Sei que no dia 100000 consigo resolver só com água ou só com fogo.
    Sei que no dia 0 não consigo resolver.
    Se consigo resolver no dia i, consigo no dia i+1 também.
    Faz uma busca binária para achar o primeiro dia que dá pra resolver.

    Em cada dia candidato, checa a quantidade de água e fogo adquiridos.
    Vê se só com fogo ou só com água resolve mata todos.
        Se sim, é um dia que consigo resolver.
            Nota: se tiver água ou fogo >= 10^6 (que é s * n), SEMPRE consigo resolver. 
                  Ou seja, daqui pra baixo, max(w, f) < 10^6.
        Se não, vejo o máximo de monstros que consigo resolver com água (knapsack).
            Se consigo resolver o resto com fogo, é um dia que consigo resolver.
        Se não, faço a mesma coisa trocando água e fogo.
            Se consigo resolver parte com fogo (knapsack) e o resto com água, é um dia que consigo resolver.
        Se não consigo resolver de nenhuma dessas formas, NÃO é um dia que consigo resolver.

    O( lg(n * s) * (n + min(max(w, f) * dia, 10^6)) )
*/

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

typedef long long ll;

vector<ll> a(101);
bitset<1000001> mem;
ll n;

ll pd(ll peso_max)
{
    // mem[i] é igual a 1 se consigo formar aquele valor somando uma subcoleção de `a`.
    mem.reset();
    mem[0] = true;  // Inicialmente, só 0 é verdadeiro.

    for_(i, 0, n)
    {
        // Se um bit 'x' em `mem` é 1, shiftar 'x' à esquerda por `a[i]` marcará o bit 'x + a[i]' como 1.
        // Isso significa que consigo formar 'x + a[i]'.
        // O '|' é para unir os valores que já sabia formar aos que agora eu aprendi que sei formar.
        mem |= mem << a[i];
    }

    for (ll peso_at = peso_max; peso_at >= 0; --peso_at) 
    {
        if (mem[peso_at]) return peso_at;
    }
}

bool ok(ll s_at, ll w, ll f)
{
    // Quantidade de água e fogo que adquiri no dia `s_at`.
    w *= s_at;
    f *= s_at;

    ll soma = 0;
    for_(i, 0, n) soma += a[i];
    
    // Se consigo matar todos só com água ou só com fogo.
    if (w >= soma or f >= soma) return true;

    // Calculo o máximo que consigo matar com a água que eu tenho, e vejo se consigo matar o resto com fogo.
    // E vice-versa.
    if (w >= soma-pd(f) or f >= soma-pd(w)) return true;

    return false;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int t;
    cin >> t;
    while(t--)
    {
        ll w, f;
        cin >> w >> f >> n;
        for_(i, 0, n) cin >> a[i];

        ll alvo = -1;
        for (ll salto = 1e6 + 20; salto >= 1; salto /= 2)
        {
            while (!ok(alvo+salto, w, f)) alvo += salto;
        }

        cout << alvo+1 << '\n';
    }

    return 0;
}