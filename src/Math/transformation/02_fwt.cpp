inline void FWTOR(int *a, int type) {
    for(int mid = 1; mid < lim; mid <<= 1)
        for(int i = 0; i < lim; i += (mid << 1))
            for(int j = 0; j < mid; j++)
                a[i + mid + j] += a[i + j] * type;
}

inline void FWTAND(int *a, int type) {
    for(int mid = 1; mid < lim; mid <<= 1)
        for(int i = 0; i < lim; i += (mid << 1))
            for(int j = 0; j < mid; j++) {
                int x = a[i + j], y = a[i + mid + j];
                a[i + j] = x + y;
                a[i + mid + j] = x - y;
                if(type == -1) a[i + j] /= 2, a[i + mid + j] /= 2;
            }
}

inline void FWTXOR(int *a, int type) {
    for(int mid = 1; mid < lim; mid <<= 1)
        for(int i = 0; i < lim; i += (mid << 1))
            for(int j = 0; j < mid; j++) {
                int x = a[i + j], y = a[i + mid + j];
                a[i + j] = x + y;
                a[i + mid + j] = x - y;
                if(type == -1) a[i + j] /= 2, a[i + mid + j] /= 2;
            }
}


// example of c[k]=\sum_{i|j=k}[|i|+|j|=|k|]*a[i]*b[j]
inline void work() {
    for(int i = 0; i <= 20; i++) FWTOR(C[i], 1);
    for(int i = 0; i <= 20; i++)//枚举位数 
    {
        memset(D, 0, sizeof(D));
        for(int j = 0; j <= i; j++)
            for(int s = 0; s < (1 << 20); s++)
                D[s] = ADD(D[s], 1ll * C[j][s] * C[i - j][s] % mod);
        FWTOR(D, -1);
        for(int s = 0; s < (1 << 20); s++)
            if(bc[s] == i) ans[s] = ADD(ans[s], D[s]);
    }
}