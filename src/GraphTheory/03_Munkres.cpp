int mat[Ma];
bool mz[Ma];

bool find(int u) {
	qxx (i, u) {
		if (mz[node[i].v]) continue;
		mz[node[i].v] = true; debug(mat[node[i].v]);
		if (!~mat[node[i].v] or find(mat[node[i].v]))
			return mat[node[i].v] = u, true;
	}
	return false;
}