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
#define all(x) (x).begin(), (x).end()
#define int long long

const int N = 5e5 + 7;
const int INF = 9e18;

int n, d;
vector<int> tab[N];

int licz(vector<int> const &a, vector<int> const &b, int k)
{
    if(k < 0)
        return INF;
    int ret = 0;
    for(int i = 0; i < k; i++)
    {
        ret += a[i];
    }
    int cnt = 0;
    for(int i = k; i < sz(a); i++, cnt++)
    {
        int temp = a[i] - b[cnt];
        if(temp < 0)
            temp *= -1;
        ret += temp;
    }

    for(int i = cnt; i < sz(b); i++)
    {
        ret += abs(d - b[i]);
    }

    return ret;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> d;
    for(int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a;
        for(int j = 0; j < a; j++)
        {
            cin >> b;
            tab[i].pb(b);
        }
    }

    for(int i = 1; i < n; i++)
    {
        int maks = max(sz(tab[i]), sz(tab[i - 1]));
        vector<int> a;
        vector<int> b;
        a.pb(0);
        b.pb(0);
        if(maks != sz(tab[i - 1]))
        {
            for(int j = 0; j < maks - sz(tab[i - 1]); j++)
            {
                a.pb(0);
            }
        }
        for(auto u: tab[i - 1])
        {
            a.pb(u);
        }

        if(maks != sz(tab[i]))
        {
            for(int j = 0; j < maks - sz(tab[i]); j++)
            {
                b.pb(0);
            }
        }
        for(auto u: tab[i])
        {
            b.pb(u);
        }

        int ans = INF;

        int l = -1, r = maks + 1;
        while(l + 1 < r)
        {
            int m = (l + r) / 2;
            if(licz(a, b, m) > licz(a, b, m + 1))
                l = m;
            else
                r = m;
        }
        ans = min(ans , licz(a, b, l + 1));

        l = -1, r = maks + 1;
        while(l + 1 < r)
        {
            int m = (l + r) / 2;
            if(licz(b, a, m) > licz(b, a, m + 1))
                l = m;
            else
                r = m;
        }
        ans = min(ans , licz(b, a, l + 1) );
        cout << ans << "\n";
    }
}