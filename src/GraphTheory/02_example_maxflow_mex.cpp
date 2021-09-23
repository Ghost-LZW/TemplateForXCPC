/*
* problem: 一颗树，每个节点有一个颜色c_i，在节点上装钻石，选择钻石颜色d_i，得到值为c_i * d_i, 求mex
* solution: 获得每个节点的可能值线段树优化建图连边，二分求mex，残留网络上跑dinic
*/
template<typename T>
struct Dinic { // O(n^2m)
    static const int Ma = 5e5;
    struct Node {
        int u, v, nex; T w;
    } node[Ma * 2], bnd[Ma * 2];
    int head[Ma], cnt, n, cur[Ma], d[Ma], bcn, bhd[Ma];
 
    void backup() {
        bcn = cnt;
        memcpy(bnd, node, sizeof node);
        memcpy(bhd, head, sizeof head);
    }
    void reback() {
        cnt = bcn;
        memcpy(node, bnd, sizeof node);
        memcpy(head, bhd, sizeof head);
    }
    Dinic(int n=Ma) : n(n) {
        cnt = 0;
        memset(head, -1, sizeof(int) * n);
    }
    void add_edge(int u, int v, T w) {
        node[cnt].u = u, node[cnt].v = v, node[cnt].w = w;
        node[cnt].nex = head[u], head[u] = cnt++;
    }
    void add(int u, int v, T w) {
        add_edge(u, v, w);
        add_edge(v, u, 0);
    }
    bool bfs(const int& s, const int& t) {
        memset(d, 0, sizeof(int) * n);
        queue<int> q; q.emplace(s); d[s] = 1;
        while (!q.empty()) {
            int tp = q.front(); q.pop();
            qxx (i, tp) if (node[i].w and !d[node[i].v]) {
                d[node[i].v] = d[tp] + 1;
                q.emplace(node[i].v);
            }
        }
        return d[t];
    }
    T dfs(int u, const int& t, T mn) {
        if (u == t or mn == 0) return mn;
        T flow = 0;
        for (int& i = cur[u]; ~i; i = node[i].nex) if (d[node[i].v] == d[u] + 1 and node[i].w) {
            int af = dfs(node[i].v, t, min(mn, node[i].w));
            if (af > 0) {
                flow += af;
                mn -= af;
                node[i].w -= af;
                node[i ^ 1].w += af;
                if (mn <= 0) break;
            }
        }
        return flow;
    }
    T maxflow(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            memcpy(cur, head, sizeof(int) * n);
            ans += dfs(s, t, numeric_limits<T>::max());
        }
        return ans;
    }
    /*set<int> ct;
    void print(int u, int fa=-1, bool can=false) {
        vector<int> m; cerr << fa << "->" <<  u << " 's son : ";
        qxx (i, u) {
            int v = node[i].v;
            cerr << v << ' ';
            if (v == fa or ct.count(v)) continue;
            m.ep(v);
            ct.emplace(v);
        }
        cerr << endl;
        if(can) rap (i, m) print(i, u, true);
    }*/
};
 
Dinic<int> dinic;
 
template<typename T>
struct HLD {
    static const int Ma = 6e4;
    int fa[Ma], dep[Ma], siz[Ma], son[Ma], st[Ma];
    int top[Ma], dfn[Ma], rnk[Ma]; int cnt;
    typedef std::vector<std::vector<T>> Tree;
    const std::vector<std::vector<T> >& g;
    Tree vt;
    void dfs1(int u) {
        son[u] = -1; siz[u] = 1;
        for (const auto& i : g[u]) if (!dep[i]) {
            dep[i] = dep[u] + 1;
            fa[i] = u;
            dfs1(i);
            siz[u] += siz[i];
            if (son[u] == -1 or siz[i] > siz[son[u]]) son[u] = i;
        }
    }
    void dfs2(int u, int f) {
        top[u] = f; dfn[u] = ++cnt; rnk[cnt] = u;
        if (!~son[u]) return ;
        dfs2(son[u], f);
        for (const auto& i : g[u]) if (i != son[u] and i != fa[u])
            dfs2(i, i);
    }
    HLD(std::vector<std::vector<T> >& gg) : g(gg) {
        memset(dep, 0, sizeof dep);
        dep[0] = 1; cnt = 0;
        dfs1(0); dfs2(0, 0);
        vt.resize(gg.size());
    }
    int LCA(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) u = fa[top[u]];
            else v = fa[top[v]];
        }
        return dep[u] > dep[v] ? v : u;
    }
    void vtree(std::vector<int>& key) {
        int top = 0; st[top] = 0; vt[0].clear();
        std::sort(key.begin(), key.end(), [&](int a, int b) {return dfn[a] < dfn[b];});
        static std::function<void(int, int)> add = [&] (const int& u, const int& v) {
            vt[u].emplace_back(v);
        };
        static std::function<void(int)> insert = [&] (int x) {
            vt[x].clear();
            if (top == 0) {x != 0 ? st[++top] = x : 0; return ;}
            int lca = LCA(x, st[top]);
            if (lca == st[top]) st[++top] = x;
            else {
                while (top > 0 and dfn[st[top - 1]] >= dfn[lca])
                    add(st[top - 1], st[top]), --top;
                if (lca != st[top]) vt[lca].clear(), add(lca, st[top]), st[top] = lca;
                st[++top] = x;
            }
        };
        for (const auto& i : key) insert(i);
        while (top > 0) add(st[top - 1], st[top]), --top;
    }
};
 
template<typename G>
struct STG {
    struct Node {
        int l, r, lc, rc;
    } nd[Ma * 4];
    int base;
    G& g;
    STG(G& g) : g(g) {base = 0;}
    int build(int l, int r) {
        int o = ++base;
        nd[o].l = l, nd[o].r = r;
        if (l == r) {
            //debug(o, l, r);
            g.add(0, o, 1);
        } else {
            int mid(l + (r - l) / 2);
            nd[o].lc = build(l, mid);
            nd[o].rc = build(mid + 1, r);
            g.add(nd[o].lc, o, r - mid);
            g.add(nd[o].rc, o, r - mid);
        }
        return o;
    }
    void update(int o, int L, int R, int v) {
        if (L <= nd[o].l and nd[o].r <= R)
            g.add(o, base + v + 1, 1);
        else {
            int mid(nd[o].l + (nd[o].r - nd[o].l) / 2);
            if (L <= mid) update(nd[o].lc, L, R, v);
            if (R > mid) update(nd[o].rc, L, R, v);
        }
    }
};
 
vector<vector<int> > g;
vector<int> col;
vector<int> cc[Ma];
int eco[Ma];
STG<Dinic<int> > stg(dinic);
int sz[Ma], n;
 
inline void ins(int u, int v, int val, HLD<int>& hld) {
    if (val > n) return ;
    while (hld.top[u] != hld.top[v]) {
        if (hld.dep[hld.top[u]] < hld.dep[hld.top[v]]) swap(u, v);
        stg.update(1, hld.dfn[hld.top[u]], hld.dfn[u], val);
        u = hld.fa[hld.top[u]];
    }
    if (u == v) return ;
    if (hld.dep[v] > hld.dep[u]) swap(u, v);
    //if (u == 3) debug(u, v, val, hld.dfn[u]);
    stg.update(1, hld.dfn[hld.son[v]], hld.dfn[u], val);
}
 
template<typename Gra>
inline void dfs(const int& c, int u, int fa, Gra& vg, HLD<int>& hld) {
    sz[u] = c == col[u];
    for (const auto& i : vg[u]) if (i != fa)
        dfs(c, i, u, vg, hld), sz[u] += sz[i], sz[i] = 0;
    if (c * sz[u] <= n) u == fa ?
        stg.update(1, hld.dfn[u], hld.dfn[u], c * sz[u]) :
        ins(u, fa, c * sz[u], hld);
}
 
bool check(int m, int pre) {
    for (int i = pre; i < m; i++)
        dinic.add(stg.base + i + 1, stg.base + n + 2, 1);
    int val = dinic.maxflow(0, stg.base + n + 2);
        //debug(val, m, pre);
    return val == m - pre;
}
 
signed main() {
    #if SYNC==0
    ios::sync_with_stdio(false);
    cin.tie(0);
    #endif
    cin >> n;
    g.resize(n);
    rep (i, n - 1) {int t; cin >> t; --t; g[t].ep(i + 1);}
    static HLD<int> hld(g);
//#ifdef DEBUG
//  cerr << endl;
//  rep (i, n) cerr << "id: " << i + 1 << " -> " << hld.dfn[i] << endl;
//  cerr << endl;
//#endif
    rep (i, n) {int t; cin >> t; col.ep(t); cc[t].ep(i); eco[i] = t;}
    sort(eco, eco + n);
    int m = unique(eco, eco + n) - eco;
    stg.build(1, n);
    //dinic.ct.clear();
    //dinic.print(0, 0, true);
    rep (i, m) {
        hld.vtree(cc[eco[i]]);
        dfs(eco[i], 0, 0, hld.vt, hld);
        sz[0] = 0;
    }
    dinic.add(1, stg.base + 1, 1);
    dinic.backup();
    //cerr << "----------------" << endl;
    //dinic.ct.clear();
    //dinic.print(0, 0, true);
    int l = 0, r = n + 1;
    while (r - l > 1) {
        int mid(l + (r - l) / 2);
        if (check(mid, l)) {
            l = mid;
            dinic.backup();
        } else r = mid, dinic.reback();
    }
    cout << l << endl;
     
    return 0;
}
