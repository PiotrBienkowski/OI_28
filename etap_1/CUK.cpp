/*
result: 100

Piotr Bieńkowski
Akademickie Liceum Ogólnokształcące Politechniki Wrocławskiej
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int long long

const int N = 3e5+7;
const int INF = 9e15 + 7; 

int tab[N][5], w[N];
int n;
bool is[4];

ll calc(int a, int b, int c)
{
    if(a == b || a == c || b == c)
        return INF;
    if(is[1])
        w[a] = 1; 
    if(is[2])
        w[b] = 2; 
    if(is[3])
        w[c] = 3;

    ll ans = 0;
    for(int i = 0; i < n; i++)
    {
        if(w[i] == 0)
        {
            pair<int, int> d, p, r;
            d.first = tab[i][1];
            d.second = 1;
            p.first = tab[i][2];
            p.second = 2;
            r.first = tab[i][3];
            r.second = 3;
            w[i] = max(d, max(p, r)).second;
        }
        for(int j = 1; j < 4; j++)
            if(j == w[i])
                continue;
            else
                ans += tab[i][j];
        w[i] = 0;
    }
    w[a] = 0; w[b] = 0; w[c] = 0;   
    return ans;
}

vector<pair<int, int>> maxD, maxP, maxR;

void updateD(int v, int index)
{
    int act = INF;
    int actIndex = -1;
    for(int i = 0; i < maxD.size(); i++)
    {
        if(maxD[i].first < act)
        {
            act = maxD[i].first;
            actIndex = i;
        }
    }
    if(maxD[actIndex].first < v)
        maxD[actIndex] = {v, index};
}

void updateP(int v, int index)
{
    int act = INF;
    int actIndex = -1;
    for(int i = 0; i < maxP.size(); i++)
    {
        if(maxP[i].first < act)
        {
            act = maxP[i].first;
            actIndex = i;
        }
    }
    if(maxP[actIndex].first < v)
        maxP[actIndex] = {v, index};
}

void updateR(int v, int index)
{
    int act = INF;
    int actIndex = -1;
    for(int i = 0; i < maxR.size(); i++)
    {
        if(maxR[i].first < act)
        {
            act = maxR[i].first;
            actIndex = i;
        }
    }
    if(maxR[actIndex].first < v)
        maxR[actIndex] = {v, index};
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    

    for(int i = 0; i < 3; i++)
    {
        maxD.push_back({-INF, -1});
        maxP.push_back({-INF, -1});
        maxR.push_back({-INF, -1});
    }

    cin >> n;
    for(int i = 0; i < n; i++)
    {
        int d, p, r;
        cin >> d >> p >> r;
        tab[i][1] = d;
        tab[i][2] = p;
        tab[i][3] = r;
        
        int tempMax = max(d, max(p, r));

        if(tab[i][1] != 0)
            is[1] = true;
        if(tab[i][2] != 0)
            is[2] = true;
        if(tab[i][3] != 0)
            is[3] = true;

        updateD(-(tempMax - d), i);
        updateP(-(tempMax - p), i);
        updateR(-(tempMax - r), i);
    }

    int ans = INF;
    for(int i = 0; i < maxD.size(); i++)
        for(int j = 0; j < maxP.size(); j++)
            for(int k = 0; k < maxR.size(); k++)
                ans = min(ans, calc(maxD[i].second, maxP[j].second, maxR[k].second));

    cout << ans << "\n";
}