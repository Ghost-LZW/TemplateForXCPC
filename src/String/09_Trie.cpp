
/**********
test: https://ac.nowcoder.com/acm/contest/5670/B
test: https://codeforces.com/problemset/problem/888/G
异或字典树
***********/
struct Trie {
    const static int base = 29;
    int tr[Ma * base][2];
    vector<int> e[Ma * base]; int tot;
    void insert(int x) {
        int u = 0;
        for (int i = base; i >= 0; i--) {
            int t = (x >> i) & 1;
            if (!tr[u][t]) tr[u][t] = ++tot;
            u = tr[u][t];
            e[u].ep(x);
        }
    }
    int ask(int id, int d, int x) {
        if (d < 0) return 0;
        int t = (x >> d) & 1;
        if (tr[id][t]) return ask(tr[id][t], d - 1, x);
        return ask(tr[id][t ^ 1], d - 1, x) + (1 << d);
    }
    ll solve(int id, int d) {
        int l = tr[id][0], r = tr[id][1];
        ll ans = 0;
        if (l and r) {
            if (e[l].size() > e[r].size()) swap(l, r);
            int mi = numeric_limits<int>::max();
            for (size_t i = 0; i < e[l].size(); ++i)
                cmin(mi, ask(r, d - 1, e[l][i]));
            ans += mi + (1 << d);
        }
        if (l) ans += solve(l, d - 1);
        if (r) ans += solve(r, d - 1);
        return ans;
    }
} tri;