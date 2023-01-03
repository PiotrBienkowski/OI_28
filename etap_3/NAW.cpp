/*
result: 10

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

const int N = 30;
bool is[N];

vector<int> g;

bool check(int n)
{
    int ot = 0;
    int zam = 0;
    for(int i = 0; i < n; i++)
    {
        if(is[i] == 1)
        {
            ot++;
        }
        else
        {
            zam++;
        }
        if(ot < zam)
        {
            return false;
        }
    }
    if(ot == zam)
        return true;
    else
        return false;
}

bool check2(int n)
{
    int ot = 0;
    int zam = 0;
    for(int i = 0; i < n; i++)
    {
        if(is[g[i]] == 1)
        {
            ot++;
        }
        else
        {
            zam++;
        }
        if(ot < zam)
        {
            return false;
        }
    }
    if(ot == zam)
        return true;
    else
        return false;
}

void podzadanie1(int n)
{
    for(int m = 0; m < (1 << n); m++)
    {
        int temp = m;
        for(int i = 0; i < n; i++)
        {
            is[i] = temp % 2;
            temp /= 2;
        }
        if(check(n))
        {
            if(check2(n))
            {
                for(int i = 0; i < n; i++)
                {
                    if(is[i] == 1)
                        cout << "(";
                    else
                        cout << ")";
                }
                cout << "\n";
                return;
            }
        }
    }
    cout << "NIE";
}

void podzadanie2(int n)
{
    for(int i = 0; i < n; i++)
    {
        if(i %  2 == 0)
            cout << "(";
        else
            cout << ")";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n = 6;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        g.pb(a - 1);
    }

    if(n <= 20)
    {
        podzadanie1(n);
    }
    else
    {
        podzadanie2(n);
    }
}