struct sparse{
    const int lgc = 20;
    vector<vector<pi>> sp;

    void init(const vector<int>& a) {
        int n = a.size();
        sp.assign(lgc, vector<pi>(n));
        for (int i = 0; i < n; ++i) {
            sp[0][i] = {a[i], i};
        }
        for (int i = 1; i < lgc; ++i) {
            for (int j = 0; j < n; ++j) {
                sp[i][j] = max(sp[i - 1][j], sp[i - 1][min(n - 1, j + (1 << (i - 1)))]);
            }
        }
    }

    pi get(int l, int r) {
        int lg = __lg(r - l);
        return max(sp[lg][l], sp[lg][r - (1 << lg)]);
    }
};
