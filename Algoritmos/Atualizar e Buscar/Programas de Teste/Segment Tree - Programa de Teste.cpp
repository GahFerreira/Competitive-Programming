#include <iostream>
#include <vector>

using namespace std;

#define for_(_i, _from, _to) for(int _i = _from; _i < (int) _to; _i++)

#define INF (1 << 30)

struct ArvoreSegmentos
{
    public:
    
    vector<int> arvore;
    int tamanho_vetor;
    int (*merge)(int, int);

    int& operator[] (unsigned indice) { return arvore[indice]; }
    unsigned size() { return arvore.size(); }

    ArvoreSegmentos(int vetor[], int tamanho_vetor, int merge(int, int) = [](int x, int y) { return max(x, y); })
    {
        this->tamanho_vetor = tamanho_vetor;
        this->merge = merge;

        // Inicializa arvore com o tamanho adequado ( 2 * tamanho_vetor )
        arvore.resize(2 * tamanho_vetor);

        // Copia o vetor para a segunda metade da árvore
        for(int i = 0; i < tamanho_vetor; i++)
        {
            arvore[i + tamanho_vetor] = vetor[i];
        }

        // Calcula os nós da árvore de intervalos de tamanho 2 ou mais 
        for(int i_arvore = tamanho_vetor - 1; i_arvore >= 1; i_arvore--)
        {
            arvore[i_arvore] = merge(arvore[2 * i_arvore], arvore[2 * i_arvore + 1]);
        }
    }

    void atualizar(int posicao, int valor)
    {
        int i_arvore = posicao + tamanho_vetor;
        arvore[i_arvore] = valor;

        while(i_arvore > 1)
        {
            i_arvore /= 2;
            arvore[i_arvore] = merge(arvore[2 * i_arvore], arvore[2 * i_arvore + 1]);
        }
    }

    int pesquisar(int inicio, int final, int resultado_base = 0)
    {
        inicio += tamanho_vetor;
        final += tamanho_vetor;

        int resultado = resultado_base;

        while (inicio < final)
        {
            if (inicio %2 != 0) resultado = merge(resultado, arvore[inicio++]);
            if (final %2 != 0) resultado = merge(resultado, arvore[--final]);

            inicio /= 2;
            final /= 2;
        }

        return resultado;
    }
};

int main()
{
    cout << "Programa de Treino de Segment Tree\n";
    cout << "Digite primeiro o tamanho da array de entrada, seguido dos valores da array\n";
    cout << "Depois, para dar UPDATE em um indice, digite 'U {indice} {valor}'\n";
    cout << "Para perguntar o maior de um range, digite 'Q {ini} {ult}'\n";
    cout << "Para printar a arvore, digite 'P'\n";
    cout << "Para inserir uma nova array, digite 'N'\n";
    cout << "Para encerrar o programa, digite '0' no tamanho da array\n\n";

    int n;

    while(cin >> n && n > 0)
    {
        int a[n];
        for_(i, 0, n) cin >> a[i];

        ArvoreSegmentos arvore(a, n);

        cout << "Insercao concluida com sucesso!\n\n";

        char comando;

        while (cin >> comando)
        {
            if (comando == 'U' || comando == 'u')
            {
                int indice, valor;
                cin >> indice >> valor;

                if (indice < 0 || indice >= n) { cout << "Indice invalido!\n\n"; continue; }

                a[indice] = valor;

                arvore.atualizar(indice, valor);

                cout << "Atualizacao feita com sucesso!\n\n";
            }

            else if (comando == 'Q' || comando == 'q')
            {
                int ini, fim;
                cin >> ini >> fim;

                if (ini < 0 || fim > n) { cout << "Intervalo invalido!\n\n"; continue; }

                int maximo = arvore.pesquisar(ini, fim);

                cout << maximo << "\n\n";
            }

            else if (comando == 'P' || comando == 'p')
            {
                cout << "arvore.size(): " << arvore.size() << '\n';
                cout << "arvore.arvore.size(): " << arvore.arvore.size() << '\n';

                for_(i, 1, arvore.size()) cout << arvore[i] << " ";
                cout << "\n\n";
            }

            else if (comando == 'N' || comando == 'n')
            {
                cout << "Insira o tamanho da nova array, seguido pelos seus elementos\n";
                cout << "Para encerrar o programa, digite '0' no tamanho da array\n\n";

                break;
            }
        }
    }

    return 0;
}