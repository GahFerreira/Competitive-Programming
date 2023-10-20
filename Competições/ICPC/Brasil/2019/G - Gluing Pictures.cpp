#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define watch(x) cerr << (#x) << " is " << (x) << endl;
#else
#define watch(x)
#endif

#define for_(_i, _de, _ate) for(ll _i = _de; _i < (ll) _ate; ++_i)

#define ff first
#define ss second

#define all(x) x.begin(), x.end()

#define str_to_lower(s) transform(s.begin(), s.end(), s.begin(), ::tolower)
#define str_to_upper(s) transform(s.begin(), s.end(), s.begin(), ::toupper)

#define INF 1'000'000'000 // Max int: 2'147'483'647 & Max long long: 9'223'372'036'854'775'807

typedef long long ll;
typedef long double ld;

// const int dx[8] = {+1, +0, -1, +0, +1, +1, -1, -1}, 
//           dy[8] = {+0, +1, +0, -1, -1, +1, -1, +1};

#define fpos adla
const int inf = 1e9;
const int maxn = 1e4;
char s[maxn];
map<int, int> to[maxn];
int len[maxn], fpos[maxn], link[maxn];
int node, pos;
int sz = 1, n = 0;
 
int make_node(int _pos, int _len)
{
    fpos[sz] = _pos;
    len [sz] = _len;
    return sz++;
}
 
void go_edge()
{
    while(pos > len[to[node][s[n - pos]]])
    {
        node = to[node][s[n - pos]];
        pos -= len[node];
    }
}
 
void add_letter(int c)
{
    s[n++] = c;
    pos++;
    int last = 0;
    while(pos > 0)
    {
        go_edge();
        int edge = s[n - pos];
        int &v = to[node][edge];
        int t = s[fpos[v] + pos - 1];
        if(v == 0)
        {
            v = make_node(n - pos, inf);
            link[last] = node;
            last = 0;
        }
        else if(t == c)
        {
            link[last] = node;
            return;
        }
        else
        {
            int u = make_node(fpos[v], pos - 1);
            to[u][c] = make_node(n - 1, inf);
            to[u][t] = v;
            fpos[v] += pos - 1;
            len [v] -= pos - 1;
            v = u;
            link[last] = u;
            last = u;
        }
        if(node == 0)
            pos--;
        else
            node = link[node];
    }
}
 
int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    
    len[0] = inf;
    string ent;
    cin >> ent;
    int ans = 0;
    for(int i = 0; i < (int) ent.size(); i++)
        add_letter(ent[i]);

    cout << ans << "\n";

    return 0;
}