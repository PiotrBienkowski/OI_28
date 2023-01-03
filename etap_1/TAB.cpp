/*
result: 100

Piotr Bieńkowski
Akademickie Liceum Ogólnokształcące Politechniki Wrocławskiej
*/

#include<bits/stdc++.h>
using namespace std;

const int N = 1e3 + 7;

bool tab[N][N];
int n, m, q;
int klik = 0;

bool check(int i, int j)
{
    if(i <= 0)
        return false;
    if(j <= 0)
        return false;
    return true;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> q;

    while(q--)
    {
        int i1, j1, i2, j2;
        cin >> i1 >> j1 >> i2 >> j2;
        if(check(i2, j2))
        {
            if(tab[i2][j2] == 1)
                klik--;
            else
                klik++;
            tab[i2][j2] = !tab[i2][j2];
        }
        if(check(i1 - 1, j2))
        {
            if(tab[i1 - 1][j2] == 1)
                klik--;
            else
                klik++;
            tab[i1 - 1][j2] = !tab[i1 - 1][j2];
        }
        if(check(i1 - 1, j1 - 1))
        {
            if(tab[i1 - 1][j1 - 1])
                klik--;
            else
                klik++;
            tab[i1 - 1][j1 - 1] = !tab[i1 - 1][j1 - 1];
        }
        if(check(i2, j1 - 1))
        {
            if(tab[i2][j1 - 1])
                klik--;
            else
                klik++;
            tab[i2][j1 - 1] = !tab[i2][j1 - 1];
        }
        cout << klik << "\n";
    }
}