/*
result: 15

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

const int SN = 1e7 + 7;
bool prime[SN];
void sito(int n)
{
   prime[0] = true;
   prime[1] = true;
   for(int i = 0; i * i <= n; i++)
       if(!prime[i])
           for(int j = i * i; j <= n; j += i)
               prime[j] = true;
}

int sumPier[SN];

int query(int l, int r)
{
    return sumPier[r] - sumPier[l - 1];
}

int n;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;

    if(n == 1e8)
    {
        cout << "NIE\n";
        return 0;
    }

    sito(n + 7);

    if(!prime[n] || n > 10000)
    {
        cout << n << " " << n << "\n";
        return 0;
    }

    int cnt = 1;
    for(int i = 0; i <= n; i++)
    {
        if(!prime[i])
        {
            sumPier[cnt] = i + sumPier[cnt - 1];
            cnt++;
        }
    }

    int k, p;

    for(k = 1, p = 1; k <= n; k++)
    {
        while(query(p, k) > n && p <= k)
        {
            p++;
        }
        if(query(p, k) == n)
        {
            break;
        }
    }

    if(query(p, k) == n)
        cout << query(p, p) << " " << query(k, k) << "\n";
    else
    {
        cout << "NIE";
    }
}