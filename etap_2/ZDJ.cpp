/*
result: 15

Piotr Bieńkowski
Akademickie Liceum Ogólnokształcące Politechniki Wrocławskiej

Podczas tworzenia rozwiązania zawartego w tym pliku korzystałem z materiałów:
* https://drive.google.com/drive/folders/13A1kJgb6F0dzPucUVlmgbC-5Y56I39xg?usp=sharing (moja biblioteczka przygotowana przed zawodami)
* https://www.geeksforgeeks.org/all-permutations-of-an-array-using-stl-in-c/

*/

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define pii pair<int, int>
#define debug(x); cerr << #x << " = " << x << "\n";
#define sz(x) (int)(x).size()

const int N = 300;
int a[N], n, m;
vector<int> G[N];

bool check(int cnt1)
{
    int glob = 0;
    for(int i = 0; i < n; i++)
    {
        int cnt = 0;
        for(auto u: G[i])
        {
            if(a[u] < a[i])
                cnt++;
        }
        if(i == 1 || i == 0)
        {
            glob++;
            continue;
        }
        else if(cnt == sz(G[i]) / 2)
        {
            glob++;
            continue;
        }
    }
    if(glob == n)
        return true;
    return false;
}

int cnt = 0;

void findPermutations() 
{ 
    sort(a, a + n); 
    do { 
        ++cnt;
        if(check(cnt))
        {
            cout << "TAK\n";
            for(int i = 0; i < n; i++)
            {
                cout << a[i] + 1 << " ";
            }
            cout << "\n";
            return;
        } 
    } while (next_permutation(a, a + n)); 
    cout << "NIE\n";
} 
  
int main() 
{ 
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++)
    {
        int A, B;
        cin >> A >> B;
        A--;
        B--;
        G[A].pb(B);
        G[B].pb(A);
    }
    for(int i = 0; i < n; i++)
    {
        a[i] = i;
    }
    
    findPermutations(); 
}