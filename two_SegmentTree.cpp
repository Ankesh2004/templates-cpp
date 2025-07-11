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

ll n;
vector<vector<ll>>segTree;
vector<vector<char>>grid;

void build_y(ll ix,ll lx,ll rx,ll iy, ll ly,ll ry){
    if(ly==ry){
        if(lx==rx){
            segTree[ix][iy]=(grid[lx][ly]=='*');
        }
        else{
            segTree[ix][iy]=segTree[2*ix+1][iy] + segTree[2*ix+2][iy];
        }
        return;
    }
    ll mid=(ry-ly)/2+ly;
    build_y(ix,lx,rx,2*iy+1,ly,mid);
    build_y(ix,lx,rx,2*iy+2,mid+1,ry);

    segTree[ix][iy]=segTree[ix][2*iy+1]+segTree[ix][2*iy+2];
}
void build_x(ll i,ll lx,ll rx){
    if(lx!=rx){
        ll mid=(rx-lx)/2+lx;
        build_x(2*i+1,lx,mid);
        build_x(2*i+2,mid+1,rx);
    }
    build_y(i,lx,rx,0,0,n-1);
}
ll query_y(ll ix,ll iy,ll ly,ll ry,ll qly,ll qry){
    if(qry < ly || qly > ry)
        return 0;
    if(qly <= ly && ry <= qry)
        return segTree[ix][iy];
    
    ll mid=(ry-ly)/2+ly;
    return query_y(ix,2*iy+1,ly,mid,qly,qry)+query_y(ix,2*iy+2,mid+1,ry,qly,qry);
}

ll query_x(ll ix,ll lx,ll rx,ll qlx,ll qrx,ll qly,ll qry){
    if(qrx<lx || qlx>rx){
        return 0;
    }
    if(qlx<=lx && rx<=qrx){
        return query_y(ix,0,0,n-1,qly,qry);
    }
    ll mid=(rx-lx)/2+lx;

    return query_x(2*ix+1,lx,mid,qlx,qrx,qly,qry)+query_x(2*ix+2,mid+1,rx,qlx,qrx,qly,qry);
}

void solve(){
    ll q;cin>>n>>q;
    grid.resize(n,vector<char>(n));
    fri(n){
        for(int j=0;j<n;j++){
            cin>>grid[i][j];
        }
    }
    ll y1,x1,y2,x2;
    segTree.resize(4*n,vector<ll>(4*n));
    build_x(0,0,n-1);
    while(q--){
        cin>>y1>>x1>>y2>>x2;
        y1--;y2--;x1--;x2--;
        cout<<query_x(0,0,n-1,y1,y2,x1,x2)<<'\n';
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