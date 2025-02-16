const int ld = 1e6, MOD = ...;
vector<int> fact(ld + 1, 1), invfact(ld + 1, 1);

int sum(int a, int b) {
    if (a + b >= MOD) return a + b - MOD;
    return a + b;
}

int sub(int a, int b) {
    if (a >= b) return a - b;
    return a - b + MOD;
}

int mult(int a, int b) {
    return a * 1ll * b % MOD;
}

int bp(int a, int n) {
    if (n == 0) return 1;
    if (n % 2) return mult(a, bp(a, n - 1));
    int x = bp(a, n / 2);
    return mult(x, x);
}

int binm(int n, int k) {
    if (k > n || k < 0) return 0;
    return mult(fact[n], mult(invfact[k], invfact[n - k]));
}

for (int i = 1; i <= ld; ++i) {
    fact[i] = fact[i - 1] * 1ll * i % MOD;
}
invfact[ld] = bp(fact[ld], MOD - 2);
for (int i = ld - 1; i >= 1; --i) {
    invfact[i] = invfact[i + 1] * 1ll * (i + 1) % MOD;
}
