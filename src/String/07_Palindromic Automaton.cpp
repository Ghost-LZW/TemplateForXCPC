struct PAM {
    static const int CHARSET = 26;
    int s[Ma]; int tail;
    struct Node {
        int len, cnt, diff, end;
        Node *link, *go[CHARSET], *tr;
        Node(int len=0) : len(len), cnt(0), diff(0), end(0) {
            memset(go, 0, sizeof go);
            tr = nullptr;
            link = nullptr;
        }
    } pool[Ma + 100], *cur;
    Node *start, *last;
    void init() {
        cur = pool; tail = 0;
        s[tail++] = -inf;
        start = new (cur++) Node(0);
        last = new (cur++) Node(-1);
        start->link = last->link = 
		start->tr = last->tr = last;
    }
    Node* GoFail(Node* u, int d) {
        while (s[d] != s[d - u->len - 1]) {
            if (s[d] == s[d - u->link->len - 1]) {
                u = u->link; break;
            } else {
                u = u->tr;
            }
        }
        return u;
    }
    void Extend(int ch, int dex) {
        s[tail++] = ch;
        Node* u = last;
        u = GoFail(u, dex);
        if(!u->go[ch]) {
            Node *nw = new (cur++) Node(u->len + 2),
                 *v = u->link;
            v = GoFail(v, dex);
            nw->link = v->go[ch] ? v->go[ch] : start;
            u->go[ch] = nw;
            nw->diff = nw->len - nw->link->len;
			nw->end = nw->link->end + 1;
            if (nw->diff == nw->link->diff) {
                nw->tr = nw->link->tr;
            } else nw->tr = nw->link;
        }
        last = u->go[ch];
        ++last->cnt;
    }
    void Build(char *str) {
		init();
        int len = strlen(str);
        for(int i = 0; i < len; i++) {
            Extend(str[i] - 'a', i + 1);
		}
    }
	ll calc() {
		ll ans = 0;
		for (int i = cur - start - 1; i >= 2; i--)
			pool[i].link->cnt += pool[i].cnt,
			ans = max(ans, (ll)pool[i].cnt * pool[i].len);
		return ans;
	}
} pam;