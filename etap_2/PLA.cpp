/*
result: 9

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

struct h{
    pii dlugosc;
    int ile = 0;
    int s;
    int k;
    int numer;
};

pii uproszczenie(ll a, ll b)
{
    return {a / __gcd(a, b), b / __gcd(a, b)};
}

int n, X, z;

struct CustomCompare
{
    bool operator()(const h& a, const h& b)
    {
        ll tempA = a.dlugosc.first * b.dlugosc.second * 1LL;
        ll tempB = b.dlugosc.first * a.dlugosc.second * 1LL;
        if(tempA != tempB)
            return tempA < tempB;
        else
        {
            return a.numer > b.numer;
        }
    }
};

priority_queue<h,vector<h>, CustomCompare > Q;

const int Z = 1e5 + 7;

vector<pii> zap;
pii odp[Z];

int Gile = 0;

pii dodawanie(pii a, pii b)
{
    ll gora = a.first * b.second;
    ll dol = b.first * a.second;
    ll ans = gora + dol;
    ll ansDol = a.second * b.second;
    return uproszczenie(ans, ansDol);
}

void odpowiedz(int a, int b, int ki)
{
    pii ulamek = uproszczenie(a, b);
    odp[ki] = ulamek;
}

void uzupelnij(int num, int ostatnie, int ki)
{
    h temp = Q.top();
    pii s = {temp.k - temp.dlugosc.first, 1};
    pii orgDlugosc = temp.dlugosc;
    pii tempDlugosc = orgDlugosc;
    tempDlugosc.second *= 2;
    tempDlugosc.first *= 2;
    int gora = s.first * tempDlugosc.second;
    int tempV = tempDlugosc.first * num;
    gora += tempV;
    tempV = Gile * tempDlugosc.first;
    gora -= tempV;
    odpowiedz(gora - orgDlugosc.first, tempDlugosc.second, ki);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> X >> z;
    int last = 0;
    for(int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        if(a != last)
        {
            h temp;
            temp.dlugosc = {a - last, 1};
            temp.s = last;
            temp.k = a;
            last = a;
            temp.numer = i;
            Q.push(temp);
        }
    }
    if(last != X)
    {
        int a = X;
        h temp;
        temp.dlugosc = {a - last, 1};
        temp.s = last;
        temp.k = a;
        last = a;
        temp.numer = n;
        Q.push(temp);
    }
    for(int i = 0; i < z; i++)
    {
        int a;
        cin >> a;
        zap.pb({a, i});
    }

    sort(zap.begin(), zap.end());

    int ostatnie = 0;
    for(int i = 0; i < sz(zap); i++)
    {
        for(;;)
        {
            h temp = Q.top();
            ostatnie = temp.numer;
            int tempIle = (1 << temp.ile);
            if(tempIle + Gile >= zap[i].first)
            {
                break;
            }
            Gile += tempIle;
            Q.pop();
            temp.ile++;
            temp.dlugosc.second *= 2;
            Q.push(temp);
        }
        uzupelnij(zap[i].first, ostatnie, zap[i].second);
    }
    for(int i = 0; i < z; i++)
    {
        cout << odp[i].first << "/" << odp[i].second << "\n";
    }
}