struct SAM {
	static const int CHARSET = 26;
	struct Node {
		int len; int right;
		Node *link, *go[CHARSET];
		Node(int _len=0, int newone=0) : len(_len), right(newone), link(0) {
			memset(go, 0, sizeof go);
		}
	} pool[Ma * 2], *cur;
	Node *start, *last;
	std::vector<Node*> topo;
	SAM() : cur(pool) {start = last = new (cur++) Node;}
	void extend(int w) {
		Node *v = last, *nw = new (cur++) Node(v->len + 1, 1);
		for (; v and v->go[w] == 0; v = v->link)
			v->go[w] = nw;
		if (v == nullptr) nw->link = start;
		else {
			Node *p = v->go[w];
			if (p->len == v->len + 1)
				nw->link = p;
			else {
				Node *np = new (cur++) Node(v->len + 1);
				memcpy(np->go, p->go, sizeof p->go);
				np->link = p->link; p->link = np;
				nw->link = np;
				for (; v and v->go[w] == p; v = v->link)
					v->go[w] = np;
			}
		}
		last = nw;
	}
	void topoSort() {
		static int buf[Ma * 2];
		int tot = last->len;
		for (Node* i = pool; i != cur; ++i) ++buf[i->len];
		for (int i = 1; i <= tot; ++i) buf[i] += buf[i - 1];
		topo.resize(cur - pool);
		for (Node* i = pool; i != cur; ++i) topo[--buf[i->len]] = i;
		memset(buf, 0, sizeof(int) * (tot + 1));
	}
	void cal() {
		topoSort(); int len = topo.size();
		for (int i = len - 1; i > 0; i--)
			topo[i]->link->right += topo[i]->right;
	}
	int Hash(char t) {return t - 'a';}
	void build(char* t) {for(; *t; ++t) extend(Hash(*t));}
	int querrymx(char* s) {
		int ans = 0, len = 0; Node* now = start;
		for (; *s; ++s) {
			int t = Hash(*s);
			while (now and now->go[t] == 0) now = now->link, now ? len = now->len : 0;
			if (now) ++len, now = now->go[t];
			else len = 0, now = start;
			ans = std::max(len, ans);
		}

		return ans;
	}
	long long count() {
		long long ans = 0;
		for (auto i = pool + 1;;i != cur; ++i)
			ans += i->len - i->link->len;
		return ans;
	}
} sam;