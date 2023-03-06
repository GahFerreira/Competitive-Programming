/*
Complexidade: n * log(n)
Desvantagem: gasta bem mais memória.

Melhoria em relação ao Suffix Array Base:
    No Suffix Array Base, para cada uma das iterações em que se transformava k->k+1 (log(n) iterações no total), ...
    ordenavamos o array de classes de equivalência em N * log(n). Dessa forma, a complexidade tinha como gargalo ...
    log(n) * N * log(n).

    Usando Radix Sort, que tem como complexidade O(n), para cada passo k->k+1 gastamos O(n), ...
    assim temos como complexidade log(n) * O(n).

    Infelizmente para usarmos o Radix Sort, nessa implementação, gastamos cerca de 3 * n de memória adicional.
*/

#include <iostream> // cin, cout & endl
#include <algorithm> // sort()
#include <utility> // pair<>
#include <vector>
#include <string>

// #include <bits/stdc++.h> // Já inclui tudo

using namespace std;

void radix_sort(vector<pair<pair<int, int>, int>> &p) // Nota: estudar porque é passado o vetor com & antes
{
    int tam_p = (int) p.size();

    // Ordena pelo segundo
    {
        // Vetor em que se conta a quantidade de vezes que a classe de equivalência da direita repete
        vector<int> cont(tam_p, 0);

        for (int i = 0; i < tam_p; i++)
        {
            int i_cont = p[i].first.second;
            
            cont[i_cont]++;
        }

        // Vetor que guarda a posição inicial em que vamos colocar cada elemento no nosso novo vetor (os baldes do radix sort)
        vector<int> pos(tam_p);

        pos[0] = 0;

        for (int i = 1; i < tam_p; i++)
        {
            // O início de um balde de um elemento 'i' é onde iniciou o balde do elemento 'i-1' mais a quantidade de vezes que o elemento 'i-1' foi contado
            pos[i] = pos[i-1] + cont[i-1];
        }

        // Vetor onde será salvo o resultado da ordenação pela classe de equivalência à direita
        vector<pair<pair<int, int>, int>> novo_p(tam_p);

        // Radix sort em ação
        for (int i = 0; i < tam_p; i++)
        {
            int i_pos = p[i].first.second;

            novo_p [ pos[i_pos] ] = p[i];

            pos[i_pos]++;
        }

        p = novo_p;
    }

    // Ordena pelo primeiro
    {
        // Vetor em que se conta a quantidade de vezes que a classe de equivalência da esquerda repete
        vector<int> cont(tam_p, 0);

        for (int i = 0; i < tam_p; i++)
        {
            int i_cont = p[i].first.first;
            
            cont[i_cont]++;
        }

        vector<int> pos(tam_p);

        pos[0] = 0;

        for (int i = 1; i < tam_p; i++)
        {
            pos[i] = pos[i-1] + cont[i-1];
        }

        // Vetor onde será salvo o resultado da ordenação pela classe de equivalência à esquerda
        vector<pair<pair<int, int>, int>> novo_p(tam_p);

        // Radix sort em ação
        for (int i = 0; i < tam_p; i++)
        {
            int i_pos = p[i].first.first;

            novo_p [ pos[i_pos] ] = p[i];

            pos[i_pos]++;
        }

        p = novo_p;
    }
}

// Cria e retorna a suffix array da string s
vector<int> gerar_suffix_array(string s)
{
    s+= "$";
    int tam_s = (int) s.size();
    vector<int> suffix_array(tam_s), classes_de_equivalencia(tam_s);

    // k = 0
    {
        vector<pair<char, int>> p(tam_s);   // Possui a primeira letra de cada sufixo

        for (int i = 0; i < tam_s; i++) p[i] = {s[i], i};

        sort(p.begin(), p.end());

        classes_de_equivalencia[ p[0].second ] = 0;
        for (int i = 1; i < tam_s; i++)
        {
            if (p[i].first == p[i-1].first) classes_de_equivalencia[p[i].second] = classes_de_equivalencia[p[i-1].second];

            else classes_de_equivalencia[p[i].second] = classes_de_equivalencia[p[i-1].second] + 1;
        }

        for (int i = 0; i < tam_s; i++) suffix_array[i] = p[i].second;
    }
    
    int k = 0;

    // k -> k+1

    // Antes de entrar no while meu k é igual a 0
    // Se o tamanho dos sufixos já calculados (1 << k) == (2 ^ k) for igual ou maior que tam_s...
    // ... então já calculei todos os sufixos de tamanho pelo menos tam_s, que é suficiente para eu saber todos os sufixos de s
    // Eu entro no while se eu quiser tornar meu k -> k+1
    while ((1 << k) < tam_s)
    {
        // 'p' possui as classes de equivalência de cada sufixo intermediário de s
        // e seu índice
        vector<pair<pair<int, int>, int>> p(tam_s);

        for (int i = 0; i < tam_s; i++) 
            p[i] = {{classes_de_equivalencia[i], classes_de_equivalencia[(i + (1 << k))%tam_s]}, i};

        radix_sort(p);

        classes_de_equivalencia[ p[0].second ] = 0;

        for (int i = 1; i < tam_s; i++)
        {
            if (p[i].first == p[i-1].first) classes_de_equivalencia[p[i].second] = classes_de_equivalencia[p[i-1].second];

            else classes_de_equivalencia[p[i].second] = classes_de_equivalencia[p[i-1].second] + 1;
        }

        for (int i = 0; i < tam_s; i++) suffix_array[i] = p[i].second;

        // Melhoria!
        // Se em uma iteração, a minha maior classe de equivalência for igual a tam_s - 1, ...
        // ... como as classes de equivalência se iniciam em 0, isso significa que todas são distintas.
        // Dessa forma, todos os meus sufixos intermediários já estão completamente ordenados!
        // Aumentar k só ajuda a distinguir sufixos intermediários iguais, então posso apenas retornar suffix_array.
        if (classes_de_equivalencia[p[tam_s - 1].second] == tam_s - 1) break;

        k++;
    }

    return suffix_array;
}

int main()
{
    string s;
    cin >> s;

    vector<int> suffix_array = gerar_suffix_array(s);

    for (int i = 0; i < (int) suffix_array.size(); i++) cout << s.substr(suffix_array[i]) << " ";

    return 0;
}