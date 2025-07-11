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

vector<ll>segTree,lazyTree;

void buildTree(ll i,ll l,ll r,vector<ll>&v){
    if(l==r){
        segTree[i]=v[l];
        return;
    }
    ll mid=(r-l)/2+l;
    buildTree(2*i+1,l,mid,v);
    buildTree(2*i+2,mid+1,r,v);

    segTree[i]=segTree[2*i+1]+segTree[2*i+2];
    return;
}

ll query(ll i,ll start,ll end,ll l,ll r){
    if(end<l || start>r){
        return 0;
    }
    if(start<=l && end>=r){
        return segTree[i];
    }
    ll mid = (r-l)/2 + l;
    return query(2*i+1,start,end,l,mid)+query(2*i+2,start,end,mid+1,r);
}

void updateTree(ll i,ll idx,ll l,ll r,ll newval){
    if(l==r){
        segTree[i]=newval;
        return;
    }
    ll mid=(r-l)/2+l;

    if(idx<=mid){
        updateTree(2*i+1,idx,l,mid,newval);
    }
    else{
        updateTree(2*i+2,idx,mid+1,r,newval);
    }
    segTree[i]=segTree[2*i +1]+segTree[2*i +2];
}

void updateRange(ll i, ll start, ll end, ll l ,ll r,ll val){
    if(lazyTree[i]!=0){
        segTree[i]+=(r-l+1)*lazyTree[i];
        if(l!=r){
            lazyTree[2*i+1]+=lazyTree[i];
            lazyTree[2*i+2]+=lazyTree[i];
        }
        lazyTree[i]=0;
    }
    if(l>end || r<start || l>r){
        return;
    }
    if(l>=start && r<=end){
        segTree[i]+=(r-l+1)*val;
        if(l!=r){
            lazyTree[2*i+1]+=val;
            lazyTree[2*i+2]+=val;
        }
        return;
    }
    ll mid =(r-l)/2+l;
    updateRange(2*i+1,start,end,l,mid,val);
    updateRange(2*i+2,start,end,mid+1,r,val);
}

void solve(){
    ll n,q;cin>>n>>q;
    vector<ll>v(n);
    fri(n){
        cin>>v[i];
    }
    ll l,r;
    segTree.resize(4*n);
    lazyTree.resize(4*n);
    buildTree(0,0,n-1,v);
    // ll type,idx,newval;
    while(q--){
        cin>>l>>r;
        l--;r--;
        cout<<query(0,l,r,0,n-1)<<'\n';
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