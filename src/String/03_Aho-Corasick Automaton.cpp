struct AC {
	int tr[Ma][26], fail[Ma];
	int e[Ma], tot;
	void init(){
		memset(tr, 0, sizeof(tr));
		memset(fail, 0, sizeof(fail));
		memset(e, 0, sizeof(e));
		tot = 0;
	}

	void insert(char* t){
		int u = 0;
		for(; *t; t++){
			if(!tr[u][*t - 'a'])tr[u][*t - 'a'] = ++tot;
			u = tr[u][*t - 'a'];
		}
		e[u]++;
	}

	void build(){
		queue<int> q;
		for(int i = 0; i < 26; i++)
			if (tr[0][i]) q.push(tr[0][i]);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int i = 0; i < 26; i++)
				if (tr[u][i])
					fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]);
				else tr[u][i] = tr[fail[u]][i];
		}
	}

	int querry(char* s){
		int ans = 0;
		for(int u = 0; *s; s++){
			u = tr[u][*s - 'a'];
			for(int j = u; j && ~e[j]; j = fail[j])
				ans += e[j], e[j] = -1;
		}
		return ans;
	}
} ac;