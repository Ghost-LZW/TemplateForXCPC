template<typename T>
struct HLD {
    BitTree bt;
    static const int Ma = 1e5 + 100;
    int fa[Ma], dep[Ma], siz[Ma], son[Ma], st[Ma];
    int top[Ma], dfn[Ma], rnk[Ma]; int cnt;
    typedef std::vector<std::vector<T>> Tree;
    const std::vector<std::vector<T> >& g;
 
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
    }
    int LCA(int u, int v) const {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) u = fa[top[u]];
            else v = fa[top[v]];
        }
        return dep[u] > dep[v] ? v : u;
    }
 
    void solve(int u, int fa) {
        rap (i, ak[u]) *i.S -= bt.range(dfn[i.F], dfn[i.F] + siz[i.F]);
        rap (i, val[u]) bt.add(dfn[i], 1);
        if (~son[u]) solve(son[u], u);
        rap (i, g[u]) if (i != fa and i != son[u]) solve(i, u);
        rap (i, ak[u]) *i.S += bt.range(dfn[i.F], dfn[i.F] + siz[i.F]);
    }
 
    Tree& vtree(std::vector<int>& key) {
        static Tree vt(cnt);
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
        return vt;
    }
};