//椭圆面积 x^2/a^2+y^2/b^2=1

using db = double;

db a, b;

db f(db x) {
	return sqrt((1 - x * x / a / a) * b * b);
}

db simpson(db l, db r) {
	db mid = l + (r - l) / 2;
	return (f(l) + f(r) + 4 * f(mid)) * (r - l) / 6;
}

db asr(db l, db r, db eps, db M) {
	db mid = l + (r - l) / 2;
	db L = simpson(l, mid), R = simpson(mid, r);
	if (fabs(L + R - M) <= 15 * eps) return L + R + (L + R - M) / 15.0;
	return asr(l, mid, eps / 2, L) + asr(mid, r, eps / 2, R);
}

db asr(db l, db r, db eps) {
	return asr(l, r, eps, simpson(l, r));
}