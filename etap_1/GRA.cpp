/*
result: 42

Piotr Bieńkowski
Akademickie Liceum Ogólnokształcące Politechniki Wrocławskiej
*/

#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 7;
const int MAX_GRAPH = 5e6 + 7;
const int INF = 1e9;

struct dziura{
    int poz;
    int start;
    int end;
    dziura(int _poz, int _start, int _end) : poz(_poz), start(_start), end(_end) {}
};

struct edge{
    int cost;
    int end;
    edge(int _cost, int _end) : cost(_cost), end(_end) {}
};

struct vertex{
    int cost = INF;
    vector<edge> neighbors;
    bool visited = false;
};

int n, xD, z;

vertex graph[MAX_GRAPH];
vector<dziura> dziury[N];

void dji(int x)
{
    priority_queue<pair<int, int>> q;
    q.push({0, x});
    while(!q.empty())
    {
        int v = q.top().second;
        q.pop();
        if(graph[v].visited)
        {
            continue;
        }
        graph[v].visited = true;

        for(auto e: graph[v].neighbors)
        {
            int index_sasiada = e.end;
            int koszt_sasiada = graph[index_sasiada].cost;
            int koszt_krawedzi = e.cost;
            if(koszt_sasiada > koszt_krawedzi + graph[v].cost)
            {
                graph[index_sasiada].cost = koszt_krawedzi + graph[v].cost;
                q.push({-graph[index_sasiada].cost, index_sasiada});
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> xD >> z;
    int indexDziura = 2 * n + 2;
    for(int i = 1; i <= n; i++)
    {
        int temp;
        cin >> temp;
        for(int j = 0; j < temp; j++)
        {
            int poz;
            cin >> poz;
            dziury[i].emplace_back(poz, indexDziura, indexDziura + 1);
            indexDziura += 2;
        }
    }

    for(int i = 1; i <= n; i++)
    {
        int last = i;
        for(int j = 0; j < dziury[i].size(); j++)
        {
            // początek dziury łączymy z last kosztem 0
            graph[dziury[i][j].start].neighbors.emplace_back(0, last);
            graph[last].neighbors.emplace_back(0, dziury[i][j].start);

            // koniec łączymy z początkiem kosztem 1
            graph[dziury[i][j].end].neighbors.emplace_back(1, dziury[i][j].start);

            // koniec ustawiamy jako last
            last = dziury[i][j].end;
        }
        graph[n + i].neighbors.emplace_back(0, last);
        graph[last].neighbors.emplace_back(0, n + i);
    }

    // budujemy kreski przechylone w lewo (wskoki na platformy)
    for(int i = 1; i < n; i++)
    {
        int k = 0;
        for(int j = 0; j < dziury[i].size(); j++)
        {
            if(dziury[i + 1].size() == 0 || dziury[i + 1][0].poz > dziury[i][j].poz)
            {
                graph[dziury[i][j].end].neighbors.emplace_back(1, i + 1);
            }
            else
            {
                while(k + 1 < dziury[i + 1].size() && dziury[i + 1][k + 1].poz < dziury[i][j].poz)
                    k++;
                graph[dziury[i][j].end].neighbors.emplace_back(1, dziury[i + 1][k].end);
                // łączymy z dziurą na pozycji k
            }
        }
    }

    // budujemy kreski przechylone w prawo (zeskoki)
    for(int i = 1; i < n; i++)
    {
        int k = dziury[i + 1].size() - 1;
        for(int j = dziury[i].size() - 1; j >= 0; j--)
        {
            if(dziury[i + 1].size() == 0 || dziury[i + 1][dziury[i + 1].size() - 1].poz < dziury[i][j].poz)
            {
                // łącznymy koniec
                graph[n + i + 1].neighbors.emplace_back(0, dziury[i][j].start);
            }
            else
            {
                while(k - 1 >= 0 && dziury[i + 1][k - 1].poz > dziury[i][j].poz)
                    k--;
                if(dziury[i + 1][k].poz > dziury[i][j].poz)
                    graph[dziury[i + 1][k].start].neighbors.emplace_back(0, dziury[i][j].start);
            }
        }
    }

    // łączymy z giga wierzchołkiem
    for(int i = 1; i <= n; i++)
    {
        graph[2 * n + 1].neighbors.emplace_back(0, n + i);
    }

    int start = 2 * n + 1;
    graph[start].cost = 0;
    dji(start);

    while(z--)
    {
        int q;
        cin >> q;
        cout << graph[q].cost << "\n";
    }
}