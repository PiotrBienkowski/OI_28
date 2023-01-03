/*
result: 51

Piotr Bieńkowski
Akademickie Liceum Ogólnokształcące Politechniki Wrocławskiej
*/

#include<bits/stdc++.h>
using namespace std;

const int N = 6e5 + 7;
const int M = 15e4 + 7;

const int M4 = 16;
int step = 1;
vector<pair<pair<int, int>, pair<int, int>>> graph[N];

int visited[N], ret[N];
pair<pair<int, int>, pair<int, int>> opis[N];

int act[M], rozne = 0;

bool podzad5 = true;
vector<int> opisPod5;
vector<int> opisPod5V;
set<pair<int, int>> S;
vector<int> pod5;
vector<int> pod4, pod4Syn, pod4Scie;
vector<int> pod4val;

const int MAX = 1 << 18;

int tree[2 * MAX];
int treePP[2 * MAX][M4 + 2];

void update(int indeks, int val)
{
    indeks += MAX;
    tree[indeks] = val;
    for(int i = indeks / 2; i; i /= 2)
        tree[i] = tree[2 * i] + tree[2 * i + 1];
}

int query(int l, int r)
{
    if(l > r)
        return 0;
    l += MAX;
    r += MAX;
    int ans = 0;
    ans += tree[l];
    if(l != r) ans += tree[r];
    while(l / 2 != r / 2)
    {
        if(l % 2 == 0) ans += tree[l + 1];
        if(r % 2 == 1) ans += tree[r - 1];
        l /= 2;
        r /= 2;
    }

    return ans;
}

void updatePP(int l, int r, int val, int t)
{
    if (l > r)
        return;
    l += MAX;
    r += MAX;
    treePP[l][t] += val;
    if(l != r) 
        treePP[r][t] += val;
    while(l / 2 != r / 2)
    {
        if(l % 2 == 0) treePP[l + 1][t] += val;
        if(r % 2 == 1) treePP[r - 1][t] += val;
        l /= 2;
        r /= 2;
    }
}

int queryPP(int indexB, int t)
{
    int ans = 0;
    indexB += MAX;
    for(int i = indexB; i >= 1; i /= 2)
        ans += treePP[i][t];
    return ans;
}

pair<int, int> po_lewej(int v, int i)
{
    auto it = S.lower_bound({v, i});
    if(it == S.begin())
        return {-1, -1};
    it--;
    if((*it).first != v)
        return {-1, -1};
    return (*it);
}

pair<int, int> po_prawej(int v, int i)
{
    auto it = S.upper_bound({v, i});
    if(it == S.end())
        return {-1, -1};
    if((*it).first != v)
        return {-1, -1};
    return (*it);
}

void pre(int v, int poziom)
{
    visited[v] = step;
    opisPod5V[v] = poziom;
    for(auto u: graph[v])
        if(visited[u.first.first] != step)
        {
            opisPod5[u.second.second] = poziom;
            int val = u.second.first;

            pod5.push_back(val);
            S.insert({val, poziom});

            if(po_lewej(val, poziom).second == -1)
            {
                update(poziom, 1);
            }
            pre(u.first.first, poziom + 1);
        }
}

void dfs(int v)
{
    visited[v] = step;
    ret[v] = rozne;
    for(auto u: graph[v])
        if(visited[u.first.first] != step)
        {
            if(act[u.second.first] == 0)
                rozne++;
            act[u.second.first]++;
            dfs(u.first.first);
            act[u.second.first]--;
            if(act[u.second.first] == 0)
                rozne--;
        }
}

int poziom4;

int pre4(int v)
{
    pod4[v] = poziom4;
    poziom4 ++;
    visited[v] = step;

    if(graph[v].size() == 1 && v != 1)
        return 1;

    int sum = 0;
    for(auto u:graph[v])
    {
        if(visited[u.first.first] != step)
        {
            pod4Scie[u.first.second] = u.first.first;
            pod4val[u.first.first] = u.second.first;
            sum += pre4(u.first.first);
        }
    }
    pod4Syn[v] = sum;
    return sum + 1;
}

void pod4calc(int v)
{
    visited[v] = step;
    for(auto u:graph[v])
    {
        if(visited[u.first.first] != step)
        {            
            int temp = pod4[u.first.first];
            int tempR = temp + pod4Syn[u.first.first];
            updatePP(temp, tempR, 1, u.second.first);
            pod4calc(u.first.first);
        }
    }
}

int pod4Z(int indeks)
{
    indeks = pod4[indeks];
    int ans = 0;
    for(int i = 0; i <= M4; i++)
    {
        if(queryPP(indeks ,i) >= 1)
        {
            ans++;
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, m, z;
    cin >> n >> m >> z;
    for(int i = 0; i < n - 1; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({{b, i + 1}, {c, i + 1}});
        graph[b].push_back({{a, i + 1}, {c, i + 1}});
        opis[i + 1].first.first = a;
        opis[i + 1].first.second = graph[a].size() - 1;
        opis[i + 1].second.first = b;
        opis[i + 1].second.second = graph[b].size() - 1;
        if(graph[a].size() > 2)
            podzad5 = false;
        if(graph[b].size() > 2)
            podzad5 = false;
    }

    if(graph[1].size() != 1)
        podzad5 = false;
    if(m <= 15)
    {
        pod4.resize(n + 1);
        pod4Syn.resize(n + 1);
        pod4Scie.resize(n + 1);
        pod4val.resize(n + 1);
        poziom4 = 1;
        pre4(1);
        step++;
        pod4calc(1);

        while(z--)
        {
            char c;
            int a, b;
            cin >> c;
            if(c == 'Z')
            {
                cin >> a;
                cout << pod4Z(a) << "\n";
            }
            else
            {
                cin >> b >> a;
                int staryIndex = pod4Scie[b];
                int nowyIndeks = pod4[staryIndex];

                if(pod4val[staryIndex] != a)
                {
                    int pocz = pod4val[staryIndex];
                    int tempR = nowyIndeks + pod4Syn[staryIndex];
                    updatePP(nowyIndeks, tempR, -1, pocz);
                    updatePP(nowyIndeks, tempR, 1, a);
                    pod4val[staryIndex] = a;
                }
            }
        }
    }
    else if(podzad5)
    {
        opisPod5.resize(n + 1);
        opisPod5V.resize(n + 1);
        pod5.push_back(-1);

        S.insert({-1, -1});

        pre(1, 1);

        while(z--)
        {
            char c;
            int a, b;
            cin >> c;
            if(c == 'Z')
            {
                cin >> a;
                cout << query(1, opisPod5V[a] - 1) << "\n";
            }
            else
            {
                cin >> b >> a;
                int indexB = opisPod5[b];
                int pocz = pod5[indexB];
                if(a != pocz)
                {
                    update(indexB, 0);
                    if(po_lewej(pocz, indexB).second == -1)
                    {
                        int temp = po_prawej(pocz, indexB).second;
                        if(temp != -1)
                            update(temp, 1);
                    }

                    S.erase({pocz, indexB});
                    S.insert({a, indexB});

                    if(po_lewej(a, indexB).second == -1)
                    {
                        update(indexB, 1);
                        pair<int, int> temp = po_prawej(a, indexB);
                        if(temp.second != -1)
                        {
                            update(temp.second, 0);
                        }
                    }
                    pod5[indexB] = a;
                }
            }
        }
    }
    else
    {
        dfs(1);
        while(z--)
        {
            char c;
            int a, b;
            cin >> c;
            if(c == 'Z')
            {
                cin >> a;
                cout << ret[a] << "\n";
            }
            else
            {
                step++;
                cin >> a >> b;
                graph[opis[a].first.first][opis[a].first.second].second.first = b;
                graph[opis[a].second.first][opis[a].second.second].second.first = b;
                dfs(1);
            }
        }
    }
}