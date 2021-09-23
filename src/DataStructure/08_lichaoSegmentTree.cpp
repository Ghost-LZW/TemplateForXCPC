/*"洛谷 4097 [HEOI2013]Segment"
    要求在平面直角坐标系下维护两个操作（强制在线）：
    
    1. 在平面上加入一条线段。记第 $i$ 条被插入的线段的标号为 $i$，该线段的两个端点分别为 $(x_0,y_0)$，$(x_1,y_1)$。
    2. 给定一个数 $k$，询问与直线 $x = k$ 相交的线段中，交点纵坐标最大的线段的编号（若有多条线段与查询直线的交点纵坐标都是最大的，则输出编号最小的线段）。特别地，若不存在线段与给定直线相交，输出 $0$。
    
    数据满足：操作总数 $1 \leq n \leq 10^5$，$1 \leq k, x_0, x_1 \leq 39989$，$1 \leq y_0, y_1 \leq 10^9$*/

#include <iostream>
#include <string>
#define MOD1 39989
#define MOD2 1000000000
#define MAXT 40000
using namespace std;
typedef pair<double, int> pdi;
struct line {
  double k, b;
} p[100005];
int s[160005];
int cnt;
double calc(int id, int d) { return p[id].b + p[id].k * d; }
void add(int x0, int y0, int x1, int y1) {
  cnt++;
  if (x0 == x1)  // 特判直线斜率不存在的情况
    p[cnt].k = 0, p[cnt].b = max(y0, y1);
  else
    p[cnt].k = 1.0 * (y1 - y0) / (x1 - x0), p[cnt].b = y0 - p[cnt].k * x0;
}
void update(int root, int cl, int cr, int l, int r, int u) {
  int v = s[root], mid = (cl + cr) >> 1;
  int ls = root << 1, rs = root << 1 | 1;
  double resu = calc(u, mid), resv = calc(v, mid);
  if (r < cl || cr < l) return;
  if (l <= cl && cr <= r) {
    if (cl == cr) {
      if (resu > resv) s[root] = u;
      return;
    }
    if (p[v].k < p[u].k) {
      if (resu > resv) {
        s[root] = u;
        update(ls, cl, mid, l, r, v);
      } else
        update(rs, mid + 1, cr, l, r, u);
    } else if (p[v].k > p[u].k) {
      if (resu > resv) {
        s[root] = u;
        update(rs, mid + 1, cr, l, r, v);
      } else
        update(ls, cl, mid, l, r, u);
    } else {
      if (p[u].b > p[v].b) s[root] = u;
    }
    return;
  }
  update(ls, cl, mid, l, r, u);
  update(rs, mid + 1, cr, l, r, u);
}
pdi pmax(pdi x, pdi y) {
  if (x.first < y.first)
    return y;
  else if (x.first > y.first)
    return x;
  else
    return x.second < y.second ? x : y;
}
pdi query(int root, int l, int r, int d) {
  if (r < d || d < l) return {0, 0};
  int mid = (l + r) >> 1;
  double res = calc(s[root], d);
  if (l == r) return {res, s[root]};
  return pmax({res, s[root]}, pmax(query(root << 1, l, mid, d),
                                   query(root << 1 | 1, mid + 1, r, d)));
}
int main() {
  ios::sync_with_stdio(false);
  int n, lastans = 0;
  cin >> n;
  while (n--) {
    int op;
    cin >> op;
    if (op == 1) {
      int x0, y0, x1, y1;
      cin >> x0 >> y0 >> x1 >> y1;
      x0 = (x0 + lastans - 1 + MOD1) % MOD1 + 1,
      x1 = (x1 + lastans - 1 + MOD1) % MOD1 + 1;
      y0 = (y0 + lastans - 1 + MOD2) % MOD2 + 1,
      y1 = (y1 + lastans - 1 + MOD2) % MOD2 + 1;
      if (x0 > x1) swap(x0, x1), swap(y0, y1);
      add(x0, y0, x1, y1);
      update(1, 1, MOD1, x0, x1, cnt);
    } else {
      int x;
      cin >> x;
      x = (x + lastans - 1 + MOD1) % MOD1 + 1;
      cout << (lastans = query(1, 1, MOD1, x).second) << endl;
    }
  }
  return 0;
}