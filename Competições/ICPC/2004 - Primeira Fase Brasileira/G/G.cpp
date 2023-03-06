/*
Ideia:
    Dado 'SI' para "Substância Inicial", 'SIt' para "Substância Intermediária" & 'R' para "Substância Final"

    Uma 'SI' requer 0 constainers para ser produzida.
    Uma 'SIt' pode ser produzida de 3 formas:
        1 - SI + SI : Requer 1 container para produzir (TRIVIAL)
        2 - SI + SIt : Requer 1 container para produzir, dado que SIt já esteja pronto
        3 - SIt + SIt : Requer 2 containers para produzir, dado que as substâncias já estejam prontas

    Analisando melhor as fórmulas 2 e 3 para produzir uma 'SIt':
        Para a fórmula 2, precisamos utilizar uma 'SIt' anterior.
        Como essa 'SIt' anterior já estava pronta, ela precisou ser produzida.
        Para ser produzida, ela usou um número 'n' de containers.
        Assim, como a nova 'SIt' a ser produzida vai ser produzida por outra que usou um número 'n' de containers, ...
        ... em algum momento houve pelo menos 'n' containers ...
        ... e dessa forma, a nova 'SIt' precisou de pelo menos 'n' containers para ser produzida.

        Para a fórmula 3, precisamos utilizar duas 'SIt's anteriores.
        Note que uma foi produzida depois da outra.
        Tecnicamente, elas poderiam ter sido produzidas paralelamente, mas gastaria mais containers, ... 
        ... porque se uma delas foi produzida até o fim antes da outra, essa produzida até o fim gasta constantemente 1 container apenas.
        Dessa forma, a melhor escolha é produzir uma delas até o fim antes da outra.
        A melhor 'SIt' para produzir primeiro é aquela que gasta mais containers.
        Isso porque, se um gasta pelo menos 1 container a mais que a outra pra ser produzida, então ...
        ... ao produzir a segunda, como 1 container estará ocupado guardando a primeira, não precisarão ...
        ... ser adicionados novos containers.
        Se ambas precisarem do mesmo número de containers para serem produzidas, entretanto, ...
        ... serão gastos esse número + 1, pois durante a produção da segunda, a primeira estará constantemente ...
        ... ocupando um container.

    Dessa forma, é possível criar uma PD.
    Para 'SI's, o valor na PD é 0 (gasta 0 containers para ser produzida).
    Para 'SIt's e 'R', o valor na PD é:
        Dado que S1 e S2 são as substâncias que produzem 'SIt's ou 'R'
        Dado que S1 gasta mais ou a mesma quantidade de containers que S2
        O maior valor entre PD[S1] e PD[S2] + 1
*/

#include <iostream>
#include <map>

using namespace std;

#define for_(_i, _from, _to) for(int _i = _from; _i < _to; _i++)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int r;

    while ((cin >> r) && (r != 0))
    {
        map<string, int> pd;
        string ultimo;

        for_(i, 0, r)
        {
            string el1, lixo, el2, lixo2, el3;

            cin >> el1 >> lixo >> el2 >> lixo2 >> el3;

            // Se não existir 'el1' ou 'el2' em pd, significa que são substâncias iniciais
            if (pd.count(el1) == 0) pd[el1] = 0;
            if (pd.count(el2) == 0) pd[el2] = 0;

            string maior = (pd[el1] > pd[el2]) ? el1 : el2;
            string menor = (maior == el1) ? el2 : el1;

            // Para produzir uma substância você precisa de duas
            // Uma delas vai ser produzida primeiro, e ficará guardada em um conteiner
            // Escolha de forma gulosa a que requer mais containers para ser produzida, para ser produzida primeiro
            // Dessa forma, se a primeira precisar de pelo menos 1 container a mais que a segunda ...
            // ... a segunda terá acesso a todos os containers que precisa, sem precisar interferir na primeira
            if (pd.count(el3) == 0) 
            {
                pd[el3] = max(pd[maior], pd[menor]+1);
            }

            else
            {
                int candidato = max(pd[maior], pd[menor]+1);

                pd[el3] = min(candidato, pd[el3]);
            }

            if (i == r-1) ultimo = el3;
        }

        cout << ultimo << " requires " << pd[ultimo] << " containers\n";
    }

    return 0;
}