/*
result: 20

Piotr Bieńkowski
Akademickie Liceum Ogólnokształcące Politechniki Wrocławskiej

Podczas tworzenia rozwiązania zawartego w tym pliku korzystałem z materiałów:
* https://drive.google.com/drive/folders/13A1kJgb6F0dzPucUVlmgbC-5Y56I39xg?usp=sharing (moja biblioteczka przygotowana przed zawodami)

*/

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define pii pair<long double, long double>
#define debug(x); cerr << #x << " = " << x << "\n";
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define LD long double
#define int long long

const int N = 1e5 + 7;
LD ret[N];
LD odp[N];

int n;
vector<pair<pair<long double, long double>, int>> S;

void podzadanie1()
{
    for(int i = 0; i < n; i++)
    {
        LD temp = 0;
        for(int j = 0; j < n; j++)
        {
            if(i == j)
                continue;
            temp += sqrt((S[i].first.first - S[j].first.first) * (S[i].first.first - S[j].first.first) + (S[i].first.second - S[j].first.second) * (S[i].first.second - S[j].first.second));
        }
        cout << fixed << setprecision(4) << temp << "\n";
    }
}

void podzadanie2()
{
    sort(all(S));
    vector<LD> odl;

    for(int i = 1; i < sz(S); i++)
    {
        int j = i - 1;
        LD temp = sqrt((S[i].first.first - S[j].first.first) * (S[i].first.first - S[j].first.first) + (S[i].first.second - S[j].first.second) * (S[i].first.second - S[j].first.second));
        odl.pb(temp);
    }

    for(int i = 0; i < sz(odl); i++)
    {
        int temp = n - i - 1;
        ret[0] += temp * odl[i];
    }

    odp[S[0].second] = ret[0];

    for(int i = 1; i < sz(S); i++)
    {
        LD lewo = i * odl[i - 1];
        LD prawo = n - i;
        prawo *= odl[i - 1];
        ret[i] = ret[i - 1];
        ret[i] += lewo;
        ret[i] -= prawo;
        odp[S[i].second] = ret[i];
    }
    for(int i = 0; i < n; i++)
    {
        cout << fixed << setprecision(4) << odp[i] << "\n";
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        S.pb({{a, b}, i});
    }

    if(n <= 1e4)
    {
        podzadanie1();
    }
    else
    {
        podzadanie2();
    }
}