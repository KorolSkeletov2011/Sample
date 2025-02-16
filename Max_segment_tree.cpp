struct segtree{
    int sz;
    vector<int> t;

    void init(int n) {
        sz = 1;
        while (sz < n) sz *= 2;
        t.assign(2 * sz, -1e9);
    }

    void set(int i, int v) {
        i += sz;
        t[i] = v;
        i /= 2;
        while (i > 0) {
            t[i] = max(t[2 * i], t[2 * i + 1]);
            i /= 2;
        }
    }

    int mx(int l, int r) {
        l += sz, r += sz;
        int res = -1e9;
        while (l < r) {
            if (l & 1) {
                res = max(res, t[l++]);
            }
            if (r & 1) {
                res = max(res, t[--r]);
            }
            l /= 2;
            r /= 2;
        }
        return res;
    }
};
