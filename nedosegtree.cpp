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
vector<ll> t;
vector<ll> a;
int n;
vector<ll> ta;
vector<ll> tb;
vector<ll> tmn;
void build(int v, int vl, int vr)
{
    if(vl == vr)
    {
        t[v] = a[vl];
        tmn[v] = a[vl];
        return;
    }
    int vm = (vl + vr) >> 1;
    build(2 * v, vl, vm);
    build(2 * v + 1, vm + 1, vr);
    t[v] = t[2 * v] + t[2 * v + 1];
    tmn[v] = min(tmn[2 * v], tmn[2 * v + 1]);
}
void push(int v, int vl, int vr)
{
    if(ta[v] != -1 && vl != vr)
    {
        int md = (l + r) >> 1;
        ta[2 * v] = ta[2 * v + 1] = ta[v];
        t[v] = ta[v] * (vr - vl + 1);
        t[2 * v] = ta[v] * (vm - vl + 1);
        t[2 * v + 1] = ta[v] * (vr - vm);
        tmn[2 * v] = tmn[2 * v + 1] = ta[v];
        tmn[v] = ta[v];
    }
    ta[v] = -1;
    if(tb[v] != 0 && vl != vr)
    {
        tb[2 * v] += tb[v];
        tb[2 * v + 1] += tb[v];

    }
    t[v] += tb[v] * (vr - vl + 1);
    tmn[v] += tb[v];
    tb[v] = 0;
}
ll find_x(int v, int vl, int vr, int x)
{
    push(v, vl, vr);
    if(vl == vr)
    {
        return t[v] + tb[v];
    }
    int vm = (vl + vr) >> 1;
    if(x <= vm)
        return find_x(2 * v, vl, vm, x);
    else return find_x(2 * v + 1, vm + 1, vr, x);
}
ll sum(int v, int vl, int vr, int l, int r)
{
    //cout << v << " " << vl << " " << vr << " " << l << " " << r << " " << t[v] << " " << ta[v] << " " << tb[v] << "\n";
    push(v, vl, vr);
    if(l == vl && vr == r)
        return t[v];
    if(l > r)
        return 0;
    int vm = (vl + vr) >> 1;
    return sum(2 * v, vl, vm, l, min(vm, r)) + sum(2 * v + 1, vm + 1, vr, max(l, vm + 1), r);
}
void update(int v, int vl, int vr, int l, int r, ll x)
{

    //cout << v << " " << vl << " " << vr << " " << l << " " << r << "\n";
    push(v, vl, vr);
    if(l == vl && vr == r)
    {
        ta[v] = x;
        push(v, vl, vr);
        //t[v] = x * (r - l + 1);
        //tmn[v] = x;
        //cout << v << " " << l << " " << r << " " << ta[v] << "\n";
        return;
    }
    if(l > r)
        return;
    int vm = (vl + vr) >> 1;
    update(2 * v, vl, vm, l, min(vm, r), x);
    update(2 * v + 1, vm + 1, vr, max(vm + 1, l), r, x);
    t[v] = t[2 * v] + t[2 * v + 1];
    tmn[v] = min(tmn[2 * v], tmn[2 * v + 1]);
}
void add(int v, int vl, int vr, int l, int r, ll x)
{
    //cout << v << " " << vl << " " << vr << " " << l << " " << r << "\n";
    push(v, vl, vr);
    if(l == vl && vr == r)
    {
        tb[v] += x;
        push(v, vl, vr);
//        cout << v << " " << l << " " << r << " " << ta[v] << " " << t[v] << "\n";
        return;
    }
    if(l > r)
        return;
    int vm = (vl + vr) >> 1;
    add(2 * v, vl, vm, l, min(vm, r), x);
    add(2 * v + 1, vm + 1, vr, max(vm + 1, l), r, x);
    t[v] = t[2 * v] + t[2 * v + 1];
    tmn[v] = min(tmn[2 * v], tmn[2 * v + 1]);
    //cout << v << " " << vl << " " << vr << " " << l << " " << r << " " << t[v] << " a\n";
}
ll mn(int v, int vl, int vr, int l, int r)
{
    push(v, vl, vr);
    if(l == vl && vr == r)
        return tmn[v];
    if(l > r)
        return INF64;
    int vm = (vl + vr) >> 1;
    return min(mn(2 * v, vl, vm, l, min(vm, r)),
               mn(2 * v + 1, vm + 1, vr, max(l, vm + 1), r));
}
int main()
{
//    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef __WIN32
    ifstream cin("input.txt");
    ofstream cout("output.txt");
#endif // __WIN32


    cin >> n;
    a.resize(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    vector<ll> b = a;
    t.resize(4 * n);
    ta.resize(4 * n, -1);
    tb.resize(4 * n, 0);
    tmn.resize(4 * n);
    build(1, 0, n - 1);
    int m;
    cin >> m;
    while(m--)
    {
        string t;
        cin >> t;
        if(t[0] == 'g')
        {
            int x;
            cin >> x;
            x--;
            cout << find_x(1, 0, n - 1, x) << "\n";

            cout << " = " << b[x] << "\n";
        }
        else if(t[0] == 'u')
        {
            int l, r, x;
            cin >> l >> r >> x;
            l--; r--;
            update(1, 0, n - 1, l, r, x);

            for(int i = l; i <= r; i++)
                b[i] = x;
        }
        else if(t == "rsq")
        {
            int l, r;
            cin >> l >> r;
            l--; r--;
            cout << sum(1, 0, n - 1, l, r) << "\n";

            ll sm = 0;
            for(int i = l; i <= r; i++)
                sm += b[i];
            cout << " = " << sm << "\n";
        }
        else if(t[0] == 'a')
        {
            int l, r, x;
            cin >> l >> r >> x;
            l--; r--;
            add(1, 0, n - 1, l, r, x);

            for(int i = l; i <= r; i++)
                b[i] += x;
        }
        else if(t == "rmq")
        {
            int l, r;
            cin >> l >> r;
            l--; r--;
            cout << mn(1, 0, n - 1, l, r) << "\n";

            ll mn = b[l];
            for(int i = l; i <= r; i++)
                mn = min(b[i], mn);
            cout << " = " << mn << "\n";
        }
        for(int i = 0; i < n; i++)
            cout << b[i] << " ";
        cout << "\n";
    }
    return 0;
}
