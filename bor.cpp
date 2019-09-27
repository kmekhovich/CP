#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define fst first
#define snd second
#define all(c) (c).begin(), (c).end()
typedef long long ll;
typedef long double ld;
const ll INF64 = 1e18 + 228;
const int INF32 = 1e9 + 1337;
const int MOD = 1e9 + 7;
struct Node
{
    int x;
    Node* nxt[2];
    int cnt;
    Node(int xx)
    {
        x = xx;
        nxt[0] = nullptr;
        nxt[1] = nullptr;
        cnt = 0;
    }
};
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef __WIN32
    ifstream cin("input.txt");
    ofstream cout("output.txt");
#endif // __WIN32

    int n;
    cin >> n;
    vector<int> a(n);
    for(auto& it : a)
        cin >> it;
    vector<int> b(n);
    Node *root = new Node(-1);
    int nmb_bit = 31;
    for(auto& it : b)
    {
        cin >> it;
        Node *now = root;
        for(int i = 0; i <= nmb_bit; i++)
        {
            now->cnt++;
            int bit = ((it >> (nmb_bit - i)) & 1);
            if(now->nxt[bit] == nullptr)
            {
                Node *nw = new Node(bit);
                now->nxt[bit] = nw;
                now = nw;
            }
            else
            {
                now = now->nxt[bit];
            }
        }
        now->cnt++;
    }
    for(int i = 0; i < n; i++)
    {
        int ans = a[i];
        int cur = 0;
        Node *now = root;
        for(int j = 0; j <= nmb_bit; j++)
        {
            int bit = ((a[i] >> (nmb_bit - j) & 1));
            now->cnt--;
            if(now->nxt[bit] == nullptr || now->nxt[bit]->cnt == 0)
            {
                now = now->nxt[1^bit];
                if(bit == 0)
                    cur |= (1 << (nmb_bit - j));
            }
            else
            {
                now = now->nxt[bit];
                if(bit == 1)
                    cur |= (1 << (nmb_bit - j));
            }
        }
        now->cnt--;
        cout << (ans ^ cur) << "\n";
    }

    return 0;
}
