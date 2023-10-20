/*
    O problema descreve uma árvore.
    Cada caminho descrito não repete vértice/aresta, portanto, é um caminho simples.

    O caminho da raiz (vértice 1) ao vértice 'i' compõe uma sequência de valores, 
    as "belezas" dos lugares.
    
    A resposta para cada vértice é o tamanho da maior subsequência crescente
    dentro da sequência obtida ao chegar naquele vértice partindo da raiz.
        - Em outras palavras, o tamanho da LIS da sequência formada da raiz até aquele vértice.
            - LIS significa "Longest Increasing Subsequence".

    Para visitar os vértices, basta percorrer a árvore com uma dfs.
    Sempre que visitamos um vértice na dfs, sua "beleza" é adicionada à nossa sequência atual.
    Sempre que saímos de um vértice da dfs, sua "beleza" é removida da nossa sequência atual.

    Portanto, a sacada é como obter a informação do tamanho da LIS em cada vértice em tempo hábil.
        - Como temos 10^5 vértices, não podemos gastar >= O(n) por vértice!

    Assim, vamos calcular a LIS em tempo O(logn) por vértice.

    A ideia é manter uma árvore de segmentos (ou estrutura semelhante) que permita que atualizemos
    e busquemos um valor num intervalo em tempo O(logn).

    Essa árvore de segmentos manterá, para cada valor possível de beleza, qual a maior LIS que termina
    naquele valor.

    Ao entrar num vértice, buscamos qual a maior LIS que termina em uma "beleza" menor que a "beleza"
    daquele vértice. 
        - Assim, agora encontramos uma LIS possivelmente maior, marcamos na árvore de segmentos na
        posição da "beleza" do vértice atual o valor buscado +1 (ou seja, aquela LIS + o vértice atual).
            - Note que só precisamos atualizar a árvore de segmentos se a nova informação obtida
            for melhor que a já existente na posição da "beleza" do vértice atual.
        - Mantemos essa informação em um multiset também indexado pela "beleza" do vértice atual, para
        que ao sairmos do vértice na dfs, possamos atualizar a LIS de acordo.

    Por fim, a resposta daquele vértice é o maior entre todos os valores da árvore de segmentos, que
    corresponde ao tamanho da maior LIS na sequência até aquele vértice.

    Nota importante:
        - Como os valores possíveis para a "beleza" vão até 10^9, 
        não podemos indexar diretamente por eles.
        - Dessa forma, como temos 10^5 valores distintos (já que temos no máximo 10^5 vértices),
        fazemos uma compressão dos valores de forma ordenada para números entre 0 até 10^5 -1.
        - Subtituímos os valores comprimidos no vetor de "beleza" e assim, conseguimos indexar
        nossas estruturas.
*/

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

#define all(x) x.begin(), x.end()

int cont;
vector<vector<int>> g;
vector<int> a, b;
vector<int> resp;
vector<int> seg;
vector<multiset<int>> historico;

void atualizar(int pos, int x)
{
    pos += cont;
    seg[pos] = x;

    for (pos /= 2; pos >= 1; pos /= 2)
    {
        seg[pos] = max(seg[2*pos], seg[2*pos+1]);
    }
}

int buscar(int pos)
{
    int l = cont, r = pos-1 + cont;

    int mx = 0;
    while (l <= r)
    {
        if (l % 2 == 1) mx = max(mx, seg[l++]);
        if (r % 2 == 0) mx = max(mx, seg[r--]);

        l /= 2; r /= 2;
    }

    return mx;
}

void dfs(int at, int prev)
{
    int melhor = buscar(a[at]) + 1;

    historico[a[at]].insert(melhor);

    if (melhor > seg[a[at] + cont]) atualizar(a[at], melhor);

    resp[at] = seg[1];

    for (auto& viz : g[at])
    {
        if (viz == prev) continue;

        dfs(viz, at);
    }

    historico[a[at]].erase(historico[a[at]].find(melhor));

    if (historico[a[at]].empty()) atualizar(a[at], 0);
    else atualizar(a[at], *historico[a[at]].rbegin());
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n;
    cin >> n;

    g.resize(n);
    a.resize(n);
    b.resize(n);
    resp.resize(n);

    for_(i, 1, n)
    {
        int pai;
        cin >> pai;
        --pai;

        g[i].push_back(pai);
        g[pai].push_back(i);
    }

    for_(i, 0, n)
    {
        cin >> a[i];
        b[i] = a[i];
    }

    sort(all(b));

    // Compressão
    map<int, int> mapa;

    cont = 0;
    for_(i, 0, n)
        if (mapa.count(b[i]) == 0) mapa[b[i]] = cont++;

    for_(i, 0, n) a[i] = mapa[a[i]];

    seg.resize(2*cont, 0);
    historico.resize(cont);

    // Início do percurso
    dfs(0, -1);
    
    for_(i, 1, n)
    {
        cout << resp[i] << ' ';
    }

    cout << '\n';

    return 0;
}