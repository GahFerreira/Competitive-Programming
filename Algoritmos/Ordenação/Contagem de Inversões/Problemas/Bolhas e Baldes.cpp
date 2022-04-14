// Link Problema: https://neps.academy/br/course/estruturas-de-dados-(codcad)/lesson/bolhas-e-baldes

#include <bits/stdc++.h>

using namespace std;

#define for_i(_from, _to) for(int i = _from; i < _to; i++)

int merge_sort(int a[], int l, int r)
{
    if (l == r) return 0;

    int qtd_inversoes = 0;

    int mid = (l+r)/2;
    qtd_inversoes+= merge_sort(a, l, mid);
    qtd_inversoes+= merge_sort(a, mid+1, r);

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

    while(l1 <= mid)
    {
        temp[k] = a[l1];
        l1++;
        k++;
    }

    while (l2 <= r)
    {
        temp[k] = a[l2];
        l2++;
        k++;
    }

    for(int i = l, k = 0; i < r+1; i++, k++) a[i] = temp[k]; 

    return qtd_inversoes;
}

int main()
{
    int n;
    cin >> n;
    while(n != 0)
    {
        int a[n];
        for_i(0, n) cin >> a[i];
        int qtd_inversoes = merge_sort(a, 0, n-1);
        if (qtd_inversoes % 2 == 0) cout << "Carlos\n";
        else cout << "Marcelo\n";
        
        cin >> n;
    }

    return 0;
}