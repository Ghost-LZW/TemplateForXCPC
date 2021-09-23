struct Node {
	unsigned long long x, y, z;
	int* cnt;
	bool operator == (const Node& b) {
		return x == b.x and y == b.y and z == b.z;
	}
} nd[Ma], temp[Ma];

void cdq(int l, int r) {
	if (r - l <= 1) return ;
	int mid(l + (r - l) / 2);
	cdq(l, mid);
	for (int i = l; i < r; i++) temp[i] = nd[i];
	static auto cmp = [](Node a, Node b) {if (a.y != b.y) return a.y < b.y; else return a.z < b.z;};
	sort(temp + l, temp + mid, cmp);
	sort(temp + mid, temp + r, cmp);
	int p = l, q = mid;
	while (p < mid or q < r) {
		if (q >= r or (p < mid and temp[p].y <= temp[q].y)) {
			bt.add(temp[p].z, *temp[p].cnt + 1); ++p;
		} else {
			cmax(*temp[q].cnt, bt.sum(temp[q].z)); ++q;
		}
	}
	bt.clear();
	cdq(mid, r);
}