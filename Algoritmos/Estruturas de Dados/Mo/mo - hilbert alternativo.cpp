#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Restrição: escolher 'pow' tal que: 2^pow >= n.
ll hilbert(int x, int y, int pow, int rotate) 
{
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	ll subSquareSize = ll(1) << (2*pow - 2);
	ll ans = seg * subSquareSize;
	ll add = hilbert(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

struct query
{
    int l, r, idx;
    long long ord;

    void calcular_ordem()
    {
        ord = hilbert(l, r, 20, 0);
    }
};