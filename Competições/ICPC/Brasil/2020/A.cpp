/*
    Vamos primeiro resolver o problema para 'a' > 0.

    A ideia é que, se um pacote pode ter de A a B figurinhas dentro, e todas tem a mesma chance,
    conseguimos calcular a seguinte recorrência:
        - Seja 'pd[i]' a quantidade de pacotes esperado para conseguir 'i' figurinhas.
        - 'pd[0]' é 0, pois não precisamos de nenhum pacote para conseguir 0 figurinhas.
        - 'pd[i]' é:
            - Pelo menos 1, pois precisamos de pelo menos 1 pacote para conseguir 'i' figurinhas (p/ 'i' > 0)
            - Nesse pacote que acabamos de abrir, sabemos que virá um número de figurinhas entre A e B.
                - Mais precisamente, existe a mesma probabilidade de vir qualquer número de figurinhas
                entre A e B (ambos inclusos).
            - A quantidade de possibilidades quando abrimos um pacote é, portanto, B-A+1.
                - Para simplificar, vamos denotar esse número de possibilidades como L.
                - Ou seja, L = B-A+1.
            - Assim, sabemos que cada possibilidade tem '1 / L' de chance de acontecer.
            - Portanto, 'pd[i]' é 1 + 'SOMATÓRIO de j=A até j=B de pd[i-j] / L'.
                - Em outras palavras, se abrimos um pacote de figurinhas que pode vir 2 ou 3 figurinhas,
                existe 1/2 de chance de vir 2 figurinhas e 1/2 de vir 3 figurinhas.
                - Assim, 'pd[i]' nesse caso seria 1 + pd[i-2]/2 + pd[i-3]/2.
    
    Como 'pd[i]' depende de:
        - 'pd[i-a]'
        - 'pd[i-a-1]'
        - 'pd[i-a-2]'
        ...
        - 'pd[i-b+1]'
        - 'pd[i-b]'

    Podemos manter esses valores numa fila, e quando formos calcular 'pd[k]', tiramos 'pd[k-b-1]' da fila
    e adicionamos 'pd[k-a]' à fila.

    Mantemos a todo momento um somatório de toda a fila atualizada para agilizar no cálculo de 'pd[i]'.
    Isso nos garante O(n).

    Agora, o caso de 'a' = 0.
    
    Nesse caso, nossa fórmula: 
        'pd[i]' = 1 + 'SOMATÓRIO de j=A até j=B de pd[i-j] / L'
    possui um problema.
    Como a = 0, para calcularmos 'pd[i]' durante o somatório precisaremos de 'pd[i-j]' tal que 'j = a'.
        - Ou seja, para calcular 'pd[i]' precisamos do valor de 'pd[i]'.

    A estratégia é isolar esse elemento do somatório, gerando a seguinte (equivalente) fórmula:
        'pd[i]' = 1 + 'pd[i]/L' + 'SOMATÓRIO de j=A+1 até j=B de pd[i-j] / L'

    Podemos então subtrair esse novo membro da equação dos dois lados:
        'pd[i]' - 'pd[i]/L' = 1 + 'SOMATÓRIO de j=A+1 até j=B de pd[i-j] / L'

    E simplificar:
        'pd[i]' * (L-1) / L = 1 + 'SOMATÓRIO de j=A+1 até j=B de pd[i-j] / L'

    Que é igual a:
        'pd[i]' = L / (L-1) * (1 + 'SOMATÓRIO de j=A+1 até j=B de pd[i-j] / L')

    Assim, quando 'a' for 0, basta supor que 'a' seja 1 e multiplicarmos o resultado que
    obteríamos para 'pd[i]' por L / (L-1).
*/

#include <bits/stdc++.h>

using namespace std;

using ld = long double;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n, a, b;
    cin >> n >> a >> b;

    int L = (b-a+1);

    ld pd[n+1];
    pd[0] = 0;

    queue<ld> q;
    ld soma = 0;

    for (int n_fig = 1; n_fig <= n; ++n_fig)
    {
        if ((int) q.size() == L - (a == 0 ? 1 : 0))
        {
            soma -= q.front();
            q.pop();
        }

        if (n_fig - (a == 0 ? 1 : a) >= 0)
        {
            q.push(pd[n_fig - (a == 0 ? 1 : a)] / (ld) L);

            soma += q.back();
        }

        pd[n_fig] = (1 + soma);

        if (a == 0) pd[n_fig] *= (ld) L / (ld) (L-1);
    }

    cout << fixed << setprecision(5) << pd[n] << '\n';

    return 0;
}