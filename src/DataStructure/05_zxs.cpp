struct Prtree{
    int root[Ma]; ll sum[Ma * 40]; int L[Ma * 40], R[Ma * 40], cnt;
    void update(int last, int& now, int l, int r, int pos, int val){
        if (!now) now = ++cnt;
        sum[now] = sum[last] + val;
        if(l == r) return ;
        int mid = (l + r) >> 1;
        if(mid >= pos)R[now] = R[last], update(L[last], L[now], l, mid, pos, val);
        else L[now] = L[last], update(R[last], R[now], mid + 1, r, pos, val);
    }
    ll querry(int last, int now, int l, int r, int k) {
        if(l >= r)return (l == r && r <= k) ? sum[now] - sum[last] : 0;
        if(r <= k)return sum[now] - sum[last];
        int mid = (l + r) >> 1;
        if(k <= mid) return querry(L[last], L[now], l, mid, k);
        else return sum[L[now]] - sum[L[last]] + querry(R[last], R[now], mid + 1, r, k);
    }
} pt;