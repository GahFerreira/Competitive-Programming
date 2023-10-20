/*
    Só se pode trocar letras cujas posições sejam o mesmo valor mod k.

    Dessa forma, cria-se uma string para cada posição de 0 a k-1.

    Em cada uma das strings coloca-se todos os caracteres correspondentes
    àquela posição (mod k) da string original.

    Ordena cada uma das strings.

    Junta as strings em ordem na string resposta.

    Ex.: caso "njoab 2"
    - Como k é 2, teremos um vetor de duas strings.
        - Isso porque qualquer valor mod 2 terá como resultado 0 ou 1.
    - Seja 'r' nosso vetor de strings.
    - Inicialmente, 'r[0]' terá "nob" e 'r[1]' terá "ja".
    - Ordenando cada string teremos: 'r[0]' = "bno" e 'r[1]' = "aj".
    - Juntando as strings na resposta teremos:
        'r[0][0]' + 'r[1][0]' + 'r[0][1]' + 'r[1][1]' + 'r[0][2]'
        ou seja,
        'b' + 'a' + 'n' + 'j' + 'o'
    - Assim, nossa resposta é "banjo".
*/

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)
#define all(x) x.begin(), x.end()

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    string s;
    int k;
    cin >> s >> k;

    vector<string> r(k);

    for_(i, 0, s.size())
    {
        r[i%k] += s[i];
    } 

    for_(i, 0, k) sort(all(r[i]));

    string resp;
    int cont = 0;
    for (int ch = 0; ; ++ch)
    {
        for_(i, 0, k)
        {
            resp += r[i][ch];
            ++cont;

            if (cont == (int) s.size()) break;
        }
        if (cont == (int) s.size()) break;
    }

    cout << resp << '\n';

    return 0;
}