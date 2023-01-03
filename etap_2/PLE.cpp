/*
result: 100

Piotr Bieńkowski
Akademickie Liceum Ogólnokształcące Politechniki Wrocławskiej

Podczas tworzenia rozwiązania zawartego w tym pliku korzystałem z materiałów:
* https://drive.google.com/drive/folders/13A1kJgb6F0dzPucUVlmgbC-5Y56I39xg?usp=sharing (moja biblioteczka przygotowana przed zawodami)

*/

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define pii pair<int, int>
#define debug(x); cerr << #x << " = " << x << "\n";
#define sz(x) (int)(x).size()

#define int long long

const int MAX = 1 << 20;
const int INF = 1e17;
pii tree[2 * MAX];
int lazy[2 * MAX];

void propagate(int node, int l, int r)
{
    if(lazy[node] == 0)
        return;
    tree[node].first += lazy[node];
    if(l != r)
    {
        lazy[2 * node] += lazy[node];
        lazy[2 * node + 1] += lazy[node];
    }
    lazy[node] = 0;
}

void update(int a, int b, ll val, int node = 1, int l = 0, int r = MAX - 1)
{
    propagate(node, l, r);
    if(b < l || r < a)
        return;
    if(a <= l && r <= b)
    {
        lazy[node] += val;
        propagate(node, l, r);
    }
    else
    {
        update(a, b, val, 2 * node, l, (l + r) / 2);
        update(a, b, val, 2 * node + 1, (l + r) / 2 + 1, r);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }
}

int xd;

pii query(int a, int b, int node = 1, int l = 0, int r = MAX - 1)
{
    propagate(node, l, r);
    if(b < l || r < a)
        return {-INF, -INF};
    if(a <= l && r <= b)
    {
        return tree[node];
    }
    else
    {
        return max(
            query(a, b, 2 * node, l, (l + r) / 2),
            query(a, b, 2 * node + 1, (l + r) / 2 + 1, r)
        );
    }
}

const int N = 5e5 + 7;
int tab[N];
int suf[N];
int n, sum;

vector<int> ret;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> tab[i];
        sum += tab[i];
    }

    for(int i = n; i > 0; i--)
    {
        suf[i] = suf[i + 1] + tab[i];
    }
    
    ret.pb(sum);
    for(int i = n; i > 0; i--)
    {
        tree[i + MAX].second = i;
    }

    for(int i = 1; i <= n; i++)
    {
        int temp = tab[i] - suf[i + 1];
        update(i, i, temp);
    }

    priority_queue<pii> Q;

    for(int i = 0; i < n; i++)
    {
        pii temp = query(1, n + 1);
        while(temp.first > 0)
        {
            Q.push({tab[temp.second] , temp.second});
            update(temp.second, temp.second, -INF);
            temp = query(1, n + 1);
        }
        sum -= Q.top().first;
        update(1, Q.top().second - 1, Q.top().first);
        Q.pop();
        ret.pb(sum);
    }

    for(int i = sz(ret) - 2; i >= 0; i--)
    {
        cout << ret[i] << " ";
    }
    cout << "\n";
}