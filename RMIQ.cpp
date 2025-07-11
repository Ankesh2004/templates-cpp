#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define ff first
#define ss second
#define fri(n) for (int i = 0; i < n; i++)
#define sortv(v) sort((v).begin(), (v).end())
#define printv(v, start_idx)                   \
    for (int i = start_idx; i < v.size(); i++) \
        cout << v[i] << " ";

ll mod = 1e9 + 7;
const ll MAXN = 1002;

// RANGE MAXIMUM INDEX QUERY
vector<ll>segTree,lazyTree;

void buildTree(ll i,ll l,ll r,vector<ll>&v){
    if(l==r){
        segTree[i]=l;
        return;
    }
    ll mid=(r-l)/2+l;
    buildTree(2*i+1,l,mid,v);
    buildTree(2*i+2,mid+1,r,v);

    ll idx1=segTree[2*i+1],idx2=segTree[2*i+2];
    segTree[i]=(v[idx1]>=v[idx2])?idx1:idx2;
    return;
}

ll query(ll i,ll start,ll end,ll l,ll r,vector<ll>&v){
    if(end<l || start>r){
        return -1;
    }
    if(start<=l && end>=r){
        return segTree[i];
    }
    ll mid = (r-l)/2 + l;
    ll leftIdx  = query(2*i + 1, start, end,l,mid, v);
    ll rightIdx = query(2*i + 2, start, end,  mid + 1, r,   v);

    if (leftIdx == -1) return rightIdx;
    if (rightIdx == -1) return leftIdx;
    return (v[leftIdx] >= v[rightIdx]) ? leftIdx : rightIdx;
}

void updateTree(ll i,ll idx,ll l,ll r,ll newval,vector<ll>&v){
    if(l==r){
        segTree[i]=idx;
        v[idx]=newval;
        return;
    }
    ll mid=(r-l)/2+l;

    if(idx<=mid){
        updateTree(2*i+1,idx,l,mid,newval,v);
    }
    else{
        updateTree(2*i+2,idx,mid+1,r,newval,v);
    }
    ll idx1=segTree[2*i+1],idx2=segTree[2*i+2];
    segTree[i]=(v[idx1]>=v[idx2])?idx1:idx2;
}

// void updateRange(ll i, ll start, ll end, ll l ,ll r,ll val){
//     if(lazyTree[i]!=0){
//         segTree[i]+=(r-l+1)*lazyTree[i];
//         if(l!=r){
//             lazyTree[2*i+1]+=lazyTree[i];
//             lazyTree[2*i+2]+=lazyTree[i];
//         }
//         lazyTree[i]=0;
//     }
//     if(l>end || r<start || l>r){
//         return;
//     }
//     if(l>=start && r<=end){
//         segTree[i]+=(r-l+1)*val;
//         if(l!=r){
//             lazyTree[2*i+1]+=val;
//             lazyTree[2*i+2]+=val;
//         }
//         return;
//     }
//     ll mid =(r-l)/2+l;
//     updateRange(2*i+1,start,end,l,mid,val);
//     updateRange(2*i+2,start,end,mid+1,r,val);
// }

ll queryLeftmost(ll i, ll l, ll r, ll x, vector<ll>& v) {
    if (l == r) {
        return (v[l] >= x) ? l : -1;
    }
    
    ll mid = (r - l) / 2 + l;
    
    ll leftMaxIdx = segTree[2 * i + 1];
    if (v[leftMaxIdx] >= x) {
        ll leftResult = queryLeftmost(2 * i + 1, l, mid, x, v);
        if (leftResult != -1) {
            return leftResult;
        }
    }
    
    return queryLeftmost(2 * i + 2, mid + 1, r, x, v);
}

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> v(n);
    fri(n) cin >> v[i];

    segTree.resize(4 * n);
    buildTree(0, 0, n - 1, v);

    while (q--) {
        ll x;
        cin >> x;
        ll ans = queryLeftmost(0, 0, n - 1, x, v);
        
        if (ans == -1) {
            cout << 0 << ' ';
        } else {
            cout << (ans + 1) << ' '; 
            ll newVal = v[ans] - x;
            updateTree(0, ans, 0, n - 1, newVal, v);
        }
    }
}



int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // ll t;
    // cin >> t;
    // fri(t)
        solve();

    return 0;
}