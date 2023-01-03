/*
result: 42

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
#define all(x) (x).begin(), (x).end()
#define int long long

const int N = 1e6 + 7;

int n;

int A[N];
int B[N];
int dp = 0;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    int temp1 = 0;
    int maks = -1;

    __int128_t chuj = 1;

    for(int i = 0; i < n; i++)
    {
        cin >> A[i] >> B[i];
        temp1 = __gcd(temp1, B[i]);
        chuj *= A[i] * B[i];
        maks = max(maks, A[i]);
        dp = max(__gcd(A[i], dp), __gcd(B[i], dp));
    }

    for(int i = maks; i >= 0; i--)
    {
        if(chuj % i != 0)
            continue;

        bool error = false;
        for(int j = 0; j < n; j++)
        {
            if(!(A[j] % i == 0 || B[j] % i == 0))
            {
                error = true;
                break;
            }
        }
        if(!error)
        {
            cout << max(i, temp1) << "\n";
            // cerr << max(i, temp1) << "\n";
            break;
        }
    }
}