#include<bits/stdc++.h>
using namespace std;

class DSU{
    public:
    vector<int>parent,size;

    DSU(int n){
        parent.resize(n);
        size.resize(n,1);

        for(int i=0;i<n;i++){
            parent[i]=i;
        }
    }
    int find(int x){
        if(parent[x]==x){
            return x;
        }
        return parent[x]=find(parent[x]);
    }
    void unite(int x,int y){
        int ux=find(x);
        int uy=find(y);

        if(ux==uy){
            return;
        }
        if(size[ux]<=size[uy]){
            size[uy]+=size[ux];
            parent[ux]=uy;
        }
        else{
            size[ux]+=size[uy];
            parent[uy]=ux;
        }
    }
};