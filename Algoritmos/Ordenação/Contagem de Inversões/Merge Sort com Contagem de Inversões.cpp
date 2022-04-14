/*
Objetivo: dada uma lista de inteiros, contar quantos pares de números estão fora de ordem
    Formalmente: contar todos os pares (a[i], a[j]) tal que a[i] > a[j] e i < j
Complexidade: O(n * log(n))

Resumo:
    Usamos o Merge Sort para fazer a contagem:

    Parte 1 - Explicando o Merge Sort:
    Primeiro, dividimos o vetor em 2, recursivamente, até que hajam apenas vetores de tamanho 1.
    Depois, combinamos vetores de tamanho 1, de dois a dois, em novos vetores de tamanho 2. (Se o número de vetores for ímpar, sobra 1 vetor de tamanho 1, mas o algoritmo se mantém igual)
    Ao combinar dois vetores, inserimos os números contidos neles no novo vetor, de forma ordenada.
    Como os vetores a ser combinados já estão ordenados, só precisamos comparar o menor número de cada um entre si ...
    ... sempre que vamos inserir um número no novo vetor. Dessa forma, fazemos O(n) comparações para inserirmos n números.
    Ao combinar todos os vetores, o vetor resultante estará ordenado.

    Parte 2 - A contagem:
    Quando vamos juntar dois vetores, os números do vetor à direita estão à direita dos números do vetor à esquerda no vetor inicial.
    Dessa forma, quando inserimos no novo vetor um número do vetor à direita, é como se invertêssemos esse número ...
    ... com todos os números restantes atualmente no vetor à esquerda. 
    Logo sempre que inserimos um número do vetor à direita no vetor final contamos quantos números estão atualmente no vetor à esquerda ...
    ... e adicionamos essa quantidade ao número de inversões total.

    Uma outra forma de pensar sobre isso é dividindo o vetor inicial ao meio. 
    A quantidade de inversões é: qtd_inversoes no vetor à esquerda + qtd_inversoes no vetor à direita + qtd_inversoes quando juntarmos os dois.

    Como o que estamos fazendo é ordenando o vetor pelo Merge Sort, e realizando até uma operação constante a cada comparação ao juntar dois vetores ...
    ... a complexidade desse algoritmo é a mesma do Merge Sort: O(n * log(n))
*/

#include <iostream> // cin, cout & endl

using namespace std;

// Função recebe o vetor inicial 'a' & os índices dos elementos mais à esquerda 'l' e mais à direita 'r'
int merge_sort_contagem_inversoes(int a[], int l, int r)
{
    if (l == r) return 0;

    int qtd_inversoes = 0;

    // 'mid' é a posição do meio para dividirmos o vetor atual em 2
    // O novo vetor à esquerda irá de [l .. mid] 
    // O novo vetor à direita irá de [mid+1 .. r] 
    int mid = (l+r)/2;
    qtd_inversoes+= merge_sort_contagem_inversoes(a, l, mid);
    qtd_inversoes+= merge_sort_contagem_inversoes(a, mid+1, r);

    // Etapa de merge
    // Comparamos o primeiro valor de cada vetor, pegamos o menor, tiramos ele do vetor dele e colocamos ele no novo vetor
    // A quantidade de inversões só se dá quando colocamos um elemento do vetor à direita no novo vetor
    int temp[r-l+1];
    int l1 = l, l2 = mid+1, k = 0;
    while (l1 <= mid && l2 <= r)
    {
        if (a[l1] <= a[l2])
        {
            temp[k] = a[l1];
            l1++;
        }

        else 
        {
            temp[k] = a[l2];
            l2++;
            qtd_inversoes += (mid+1) - l1;
        }

        k++;
    }

    // Quando todos os elementos do vetor à direita já tiverem sido adicionados, adiciona-se os da esquerda no final
    // Note que a quantidade de inversões para cada número à direita adicionado já foi contada
    while(l1 <= mid)
    {
        temp[k] = a[l1];
        l1++;
        k++;
    }

    // Quando todos os elementos do vetor à esquerda já tiverem sido adicionados, adiciona-se os da direita no final
    while (l2 <= r)
    {
        temp[k] = a[l2];
        l2++;
        k++;
    }

    // Atualizamos o vetor inicial de [l .. r] com o vetor temporário
    // Note que isso é essencial, já que fazemos a combinação de vetores baseando-nos no vetor inicial
    for(int i = l, k = 0; i < r+1; i++, k++) a[i] = temp[k]; 

    return qtd_inversoes;
}

int main()
{
    int tam;
    cin >> tam;

    int a[tam];
    for(int i = 0; i < tam; i++) cin >> a[i];

    int qtd_inversoes = merge_sort_contagem_inversoes(a, 0, tam-1);

    cout << "qtd_inversoes: " << qtd_inversoes << endl;

    return 0;
}