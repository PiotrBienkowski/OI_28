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

const int N = 35;
__int128_t dp[N + 7][N + 7];
bool is[N + 7][N + 7];
ll tempK;
__int128_t k;
int ex, ey;

bool check(int i)
{
    if(i - 1 < 0)
        return false;
    return true;
}

void print(__int128_t x)
{
    vector<int> temp;
    if(x == 0)
    {
        temp = {0};
    }
    while(x > 0)
    {
        temp.pb(x % 10);
        x /= 10;
    }
    reverse(temp.begin(), temp.end());
    for(auto c: temp)
        cout << c;
    cout << " ";
}

void gen()
{
    for(int i = 0; i <= N; i++)
    {
        for(int j = 0; j <= N; j++)
        {
            if(i  == 0 && j == 0)
            {
                dp[i][j] = 1;
                continue;
            }
            __int128_t temp = 0;
            if(is[i][j])
                continue;
            if(check(i))
                temp += dp[i - 1][j];
            if(check(j))
                temp += dp[i][j - 1];
            dp[i][j] = temp;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> tempK;
    k = tempK;
    ll n = 1;
    dp[0][0] = 1;

    for(int i = N; i >= 0; i--)
    {
        if(k == 0)
            break;
        for(int j = N; j >= 0; j--)
        {
            if(i == 0 && j == 0)
                continue;
            if(i == N && j == N)
                continue;
            __int128_t temp;
            temp = dp[i][j];
            dp[i][j] = 0;
            is[i][j] = 1;
            gen();
            if(dp[N][N] == k)
                break;
            if(dp[N][N] < k)
            {
                is[i][j] = 0;
                dp[i][j] = temp;
                gen();
            }
        }
        if(dp[N][N] == k)
            break;
    }

    if(k == 0)
    {
        is[0][0] = 1;
    }
    
    cout << N + 1 << "\n";
    for(int i = 0; i <= N; i++)
    {
        for(int j = 0; j <= N; j++)
        {
            if(is[i][j])
            {
                cout << "#";
            }
            else
            {
                cout << ".";
            }
        }
        cout << "\n";
    }
}
