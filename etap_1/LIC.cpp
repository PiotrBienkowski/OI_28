/*
result: 100

Piotr Bieńkowski
Akademickie Liceum Ogólnokształcące Politechniki Wrocławskiej
*/

#include<bits/stdc++.h>
using namespace std;

set<pair<int, int>> S;
int n;

void zamien(int i, int v2)
{
    auto it = S.upper_bound({i, 12});
    pair<int, int> pocz_r = *it;
    it--;
    pair<int, int> pocz = *it;
    it--;
    pair<int, int> pocz_l = *it;
    it++; 

    if(!(pocz.first == i || pocz_r.first == i + 1))
    {
        S.insert({i, v2});
        S.insert({i + 1, pocz.second});
    }
    else if(pocz.first == i && pocz_r.first == i + 1)
    {
        S.erase(it);
        S.insert({i, v2});
        if(pocz_r.second == v2)
            S.erase(pocz_r);
        if(pocz_l.second == v2)
            S.erase({i, v2});
    }
    else if(pocz_r.first == i + 1)
    {
        S.insert({i, v2});
        if(pocz_r.second == v2)
            S.erase(pocz_r);
    }
    else if(pocz.first == i)
    {
        S.erase(pocz);
        S.insert({i + 1, pocz.second});
        if(pocz_l.second != v2)
            S.insert({i, v2});
    }
}

void dodaj(int i, int v, int XD = 1)
{
    if(v == 0)
        return;
    auto it = S.upper_bound({i, 12});
	it--;
    pair<int, int> pocz;
    pair<int, int> pocz_r;
    pair<int, int> pocz_l;
    int temp = (*it).second;
    int v2 = (temp + v) % 10;
    int v3 = (temp + v) / 10;

    zamien(i, v2);

    if(v3 != 0)
    {
        it = S.upper_bound({i, 12});
        it--;
        pocz = *it;
        it++;
        pocz_r = *it;
        it++;
        pair<int, int> pocz_r_r = *it;
        it--;

        if(pocz_r.first == i + 1 && pocz_r.second == 9)
        {
            S.erase(it);

            if(v2 != 0)
                S.insert({pocz_r.first, 0});

            dodaj(pocz_r_r.first, 1, XD + 1);
        }
        else
        {
            dodaj(i + 1, 1, XD + 1);
        }
    }
}

void odejmij(int i, int v, int XD = 1)
{
    if(v == 0)
        return;
    auto it = S.upper_bound({i, 12});
    it--;
    pair<int, int> pocz;
    pair<int, int> pocz_r;
    pair<int, int> pocz_l;

    int temp = (*it).second;

    int v2 = temp - v; // na ten element zamieniamy obecną wartość
    int v3 = 0;
    if(v2 < 0)
    {
        v2 += 10;
        v3 = 1;
    }

    zamien(i, v2);

    if(v3 != 0)
    {
        it = S.upper_bound({i, 12});
        it--;
        pocz = *it;
        it++;
        pocz_r = *it;
        it++;
        pair<int, int> pocz_r_r = *it;
        it--;
        if(pocz_r.first == i + 1 && pocz_r.second == 0)
        {
            S.erase(it);
            if(v2 != 9)
                S.insert({pocz_r.first, 9});

            odejmij(pocz_r_r.first, 1, XD + 1);
        }
        else
        {
            odejmij(i + 1, 1, XD + 1);
        }
    }
}

int zapytaj(int i)
{
    auto it = S.upper_bound({i, 12});
    it--;
    return it->second;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int m, z;
    cin >> m >> z;
    string W, Z, A = "";
    cin >> W;
    cin >> Z;

    int buff = 0;
    for(int i = W.size() - 1; i >= 0; i--)
    {
        int temp = ((int)W[i] - (int)'0') + ((int)Z[i] - (int)'0') + buff;
        buff = temp / 10;
        int ans = temp % 10;
        A = (char)(ans + (int)'0') + A;
    }
    A = (char)(buff + (int)'0') + A;

    n = m;

    A = 'x' + A;
    int last = 1;
    for(int i = A.size() - 1, j = 1; i > 0; i--, j++)
    {
        if(A[i - 1] != A[i])
        {
            int cyfra = A[i] - '0';
            S.insert({last, cyfra});
            last = j + 1;
        }
    }
    S.insert({n + 1, 0});
    S.insert({n + 2, -2});    
    S.insert({0, -1});

    while(z--)
    {
        char c;
        cin >> c;
        if(c == 'S')
        {
            int x;
            cin >> x;
            cout << zapytaj(x) << "\n";
        }
        else if(c == 'W')
        {
            int x, y;
            cin >> x >> y;
            int pocz = (int)W[W.size() - x] - (int)'0';
            W[W.size() - x] = y + '0';
            if(pocz != y)
            {
                if(pocz > y)
                    odejmij(x, pocz - y);
                else
                    dodaj(x, y - pocz);
            }
        }
        else if(c == 'Z')
        {
            int x, y;
            cin >> x >> y;
            int pocz = (int)Z[Z.size() - x] - (int)'0';
            Z[Z.size() - x] = y + '0';
            if(pocz != y)
            {
                if(pocz > y)
                    odejmij(x, pocz - y);
                else
                    dodaj(x, y - pocz);
            }
        }
    }
}