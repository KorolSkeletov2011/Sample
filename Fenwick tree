struct fenwtree{
    int sz;
    vector<int> t;

    void init(int n) {
        sz = n;
        t.assign(n + 1, 0);
    }

    void add(int i, int v) {
        for (; i <= sz; i += i & (-i)) t[i] += v;
    }

    int sum(int r) {
        int res = 0;
        for (; r > 0; r -= r & (-r)) res += t[r];
        return res;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};
