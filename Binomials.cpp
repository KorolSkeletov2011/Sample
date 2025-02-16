const int MOD = ...;
vector<int> fact(ld + 1, 1), invfact(ld + 1, 1);

int sum(int a, int b) {
    if (a + b >= MOD) return a + b - MOD;
    return a + b;
}

int bp(int a, int n) {
    if (n == 0) return 1;
    if (n % 2) return a * 1ll * bp(a, n - 1) % MOD;
    int x = bp(a, n / 2);
    return x * 1ll * x % MOD;
}

int binm(int n, int k) {
    if (k > n || k < 0) return 0;
    return fact[n] * 1ll * invfact[k] % MOD * 1ll * invfact[n - k] % MOD;
}

for (int i = 1; i <= ld; ++i) {
    fact[i] = fact[i - 1] * 1ll * i % MOD;
}
invfact[ld] = bp(fact[ld], MOD - 2);
for (int i = ld - 1; i >= 1; --i) {
    invfact[i] = invfact[i + 1] * 1ll * (i + 1) % MOD;
}
