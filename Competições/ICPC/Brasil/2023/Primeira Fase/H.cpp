/*
    A ideia se baseia em olhar para as tarefas ordenadas pelo dia de início.

    Vamos olhar para elas da direita para a esquerda.
        - Ou seja, da última tarefa a começar, até a primeira.

    Quando analisamos uma tarefa 'i', temos 3 possibilidades:
        1. Fazemos ela por completo.
            - E então escolhemos de forma ótima as tarefas que começam depois de 'i'.
        2. Não fazemos ela.
            - Equivale a escolher a melhor forma de fazer as tarefas que começam
            no mesmo dia de 'i' pra frente.
        3. Fazemos ela, mas trocamos para outra antes de seu término.
            - Analisamos todas as tarefas cujo início ocorre entre o segundo dia de 'i' e
            o último dia de 'i'.
            - Escolhemos a de forma ótima para qual trocar.

    Para o caso 1:
        - Basta calcularmos quanto que fazer 'i' nos oferece.
        - Depois, basta pegarmos o melhor entre as tarefas que começam estritamente após
        o fim de 'i'.

    Para o caso 2:
        - Basta pegarmos o melhor entre as tarefas que começam no mesmo dia que 'i' ou depois.

    Para o caso 3:
        - É necessário observar que há uma escolha ótima (gulosa).
        - Como partimos do princípio que estamos pegando a tarefa 'i', gastamos 'c[i]'.
        - Seja 's' o conjunto de tarefas que começam do segundo dia de 'i' ao último dia de 'i'.
        - Seja 'g' o quanto se ganha por dia.
        - Para uma tarefa 'sᵢ' de 's', conseguimos:
            1. O melhor que conseguiríamos se pegássemos 's', +
            2. a quantidade de dias do início de 'i' até o início de 's' multiplicado por 'g'.
        - O valor de 1 já temos; estamos interessados no valor de 2.
        - Note que se calcularmos o valor de 2 para uma tarefa 'sᵢ' como:
            inicio de 'sᵢ' * 'g'
        isso equivale a:
            inicio de 'i' * 'g' + (inicio de 'sᵢ' - inicio de 'i') * 'g'
        
        - Portanto, para duas tarefas 'sᵢ' e 'sⱼ' de 's', a diferença:
            (inicio de 'sᵢ' * 'g') - (inicio de 'sⱼ' * 'g')
        equivale a
            (inicio de 'i' * 'g' + (inicio de 'sᵢ' - inicio de 'i') * 'g') menos
            (inicio de 'i' * 'g' + (inicio de 'sⱼ' - inicio de 'i') * 'g')
        que equivale a
            (inicio de 'sᵢ' - inicio de 'i') * 'g') - (inicio de 'sⱼ' - inicio de 'i') * 'g')
        que por fim equivale a
            (inicio de 'sᵢ' * 'g') - (inicio de 'sⱼ' * 'g')
        que representa quantos dias a mais passaríamos trabalhando em 'i' se trocássemos
        pra 'sᵢ' ao invés de 'sⱼ' e vice-versa.

        Assim, para escolhermos entre as tarefas de 's', olhamos para aquela que tenha o maior
        valor seguindo a equação:
            - dia de inicio da tarefa * 'g' + o melhor que conseguimos fazendo essa tarefa

    Para a tarefa 'i' analisada, cada caso é um valor candidato ao melhor que conseguimos
    ao olhar para aquela tarefa.

    Como em todos os casos só dependemos de tarefas que começaram depois de 'i', e como
    estamos calculando da direita para a esquerda, já temos os valores dessas tarefas
    quando vamos calcular 'i'.

    Para conseguirmos esses "melhores", usamos árvores de segmentos (BIT também deve funcionar).
    Indexamos as árvores por dia de início.
    Como os dias de início vão até 10^9, e como só temos 2 * 10^6 dias distintos no máximo,
    comprimimos os dias para podermos indexá-los na árvore.

    Complexidade: O(n log(n)).
*/

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

using ll = long long;

struct Trabalho
{
    int l, r, c, l_mapeado, r_mapeado;
};

struct Troca
{
    ll x;
    int i_tarefa;

    bool operator<(const Troca& t) const
    {
        return x < t.x;
    };
};

int main()
{
    int n;
    ll s;
    cin >> n >> s;

    set<int> dias_encontrados;

    Trabalho t[n];
    for_(i, 0, n)
    {
        cin >> t[i].l >> t[i].r >> t[i].c;

        dias_encontrados.insert(t[i].l);
        dias_encontrados.insert(t[i].r);
    }

    sort(t, t+n, [](const Trabalho& t1, const Trabalho& t2)
    {
        return t1.l < t2.l;
    });

    // Compressão de dados.
    map<int, int> m;
    int cont = 0;
    for (auto dia : dias_encontrados) m[dia] = cont++;

    for_(i, 0, n)
    {
        t[i].l_mapeado = m[t[i].l];
        t[i].r_mapeado = m[t[i].r];
    }
    
    int ultimo_dia = cont - 1;
    
    ll melhor[2*cont];
    Troca melhor_p_trocar[2*cont];
    for_(i, 0, 2*cont) 
    {
        melhor[i] = 0;
        melhor_p_trocar[i] = {0, 0};
    }

    auto atualizar_melhor = [cont](ll seg[], int pos, ll x) -> void
    {
        pos += cont;

        seg[pos] = x;

        for (pos /= 2; pos >= 1; pos /= 2)
        {
            seg[pos] = max(seg[2*pos], seg[2*pos+1]);
        }
    };

    auto buscar_melhor = [cont](ll seg[], int l, int r) -> ll
    {
        if (l >= cont) return 0;

        l += cont;
        r += cont;

        ll resp = 0;
        while (l <= r)
        {
            if (l & 1) resp = max(resp, seg[l++]);
            if ((r & 1) == 0) resp = max(resp, seg[r--]);

            l /= 2;
            r /= 2; 
        }

        return resp;
    };

    auto acessar_melhor = [cont](ll seg[], int pos) -> ll
    {
        return seg[pos+cont];
    };

    auto atualizar_melhor_p_trocar = [cont](Troca seg[], int pos, ll x, int i_tarefa) -> void
    {
        pos += cont;

        seg[pos] = {x, i_tarefa};

        for (pos /= 2; pos >= 1; pos /= 2)
        {
            seg[pos] = max(seg[2*pos], seg[2*pos+1]);
        }
    };

    auto buscar_melhor_p_trocar = [cont](Troca seg[], int l, int r) -> int
    {
        if (l >= cont) return -1;

        l += cont;
        r += cont;

        ll mx = 0;
        int i_tarefa_resp = -1;
        while (l <= r)
        {
            if (l & 1) 
            {
                if (seg[l].x > mx)
                {
                    mx = seg[l].x;
                    i_tarefa_resp = seg[l].i_tarefa;
                }

                ++l;
            }

            if ((r & 1) == 0) 
            {
                if (seg[r].x > mx)
                {
                    mx = seg[r].x;
                    i_tarefa_resp = seg[r].i_tarefa;
                }

                --r;
            }

            l /= 2;
            r /= 2;
        }

        return i_tarefa_resp;
    };

    auto acessar_x_melhor_p_trocar = [cont](Troca seg[], int pos) -> ll
    {
        return seg[cont+pos].x;
    };

    for (int i = n-1; i >= 0; --i)
    {
        ll producao_tarefa = s * (t[i].r - t[i].l + 1) - t[i].c;
        
        // Fazer a tarefa 'i' por inteiro.
        ll cand1 = producao_tarefa
                   + buscar_melhor(melhor, t[i].r_mapeado+1, ultimo_dia);
        
        // Não fazer a tarefa 'i'.
        ll cand2 = melhor[1]; // Equivale a: buscar_melhor(melhor, t[i].l_mapeado, ultimo_dia);

        // Fazer a tarefa 'i' e trocar para outra tarefa.
        ll cand3 = 0;

        // Não faria mal, mas não precisamos checar as tarefas que começam no mesmo dia que 'i'.
        int i_tarefa_a_trocar = 
            buscar_melhor_p_trocar(melhor_p_trocar, t[i].l_mapeado+1, t[i].r_mapeado);
        
        if (i_tarefa_a_trocar != -1)
        {
            cand3 = s * (t[i_tarefa_a_trocar].l - t[i].l)
                    - t[i].c
                    + acessar_melhor(melhor, t[i_tarefa_a_trocar].l_mapeado);
        }

        ll melhor_cand = max(cand1, max(cand2, cand3));

        if (acessar_melhor(melhor, t[i].l_mapeado) < melhor_cand)
        {
            atualizar_melhor(melhor, t[i].l_mapeado, melhor_cand);
        }

        ll valor_cand = melhor_cand + s * t[i].l;

        if (acessar_x_melhor_p_trocar(melhor_p_trocar, t[i].l_mapeado) < valor_cand)
        {
            atualizar_melhor_p_trocar(melhor_p_trocar, t[i].l_mapeado, valor_cand, i);
        }
    }

    cout << melhor[1] << '\n';

    return 0;
}