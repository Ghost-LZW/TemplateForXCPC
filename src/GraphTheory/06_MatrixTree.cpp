int Gauss(int n) {
    int ans=1;
    for(int i=1;i<=n;++i) {
        for(int k=i+1;k<=n;++k) {
            while(a[k][i]) {
                int d=a[i][i]/a[k][i];
                for(int j=i;j<=n;++j) a[i][j]=(a[i][j]-1LL*d*a[k][j]%mod+mod)%mod;
                std::swap(a[i],a[k]),ans=-ans;
            }
        }
        ans=1LL*ans*a[i][i]%mod,ans=(ans+mod)%mod;
    }
    return ans;
}

// usage O(n^3 log n)
int main() {
    scanf("%d%d",&n,&m);
    while(m--) {
        int u,v;
        scanf("%d%d",&u,&v);
        --a[u][v],--a[v][u],++a[u][u],++a[v][v];
    }
    printf("%d\n",Gauss(n-1));
    return 0;
}