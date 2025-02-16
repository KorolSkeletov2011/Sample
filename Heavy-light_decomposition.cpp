#include <bits/stdc++.h>
//# define int long long

using namespace std;

struct segtree2{
    int sz;
    vector<pair<int, int>> t;

    void init(int n) {
        sz = 1;
        while (sz < n) {
            sz *= 2;
        }
        t.assign(2 * sz - 1, {1e9, 1e9});
    }

    void set(int i, pair<int, int> p, int l, int r, int x) {
        if (r - l == 1) {
            t[x] = p;
            return;
        }
        int m = (l + r) / 2;
        if (i < m) {
            set(i, p, l, m, 2 * x + 1);
        } else {
            set(i, p, m, r, 2 * x + 2);
        }
        t[x] = min(t[2 * x + 1], t[2 * x + 2]);
    }

    void set(int i, pair<int, int> p) {
        set(i, p, 0, sz, 0);
    }

    pair<int, int> mn(int ql, int qr, int l, int r, int x) {
        if (ql <= l && r <= qr) {
            return t[x];
        }
        if (l >= qr || r <= ql) {
            return {1e9, 1e9};
        }
        int m = (l + r) / 2;
        pair<int, int> mn1 = mn(ql, qr, l, m, 2 * x + 1);
        pair<int, int> mn2 = mn(ql, qr, m, r, 2 * x + 2);
        return min(mn1, mn2);
    }

    pair<int, int> mn(int l, int r) {
        return mn(l, r, 0, sz, 0);
    }
};

struct segtree{
    int sz;
    vector<int> t;

    void init(int n) {
        sz = 1;
        while (sz < n) {
            sz *= 2;
        }
        t.assign(2 * sz - 1, 0);
    }

    void set(int i, int v, int l, int r, int x) {
        if (r - l == 1) {
            t[x] = v;
            return;
        }
        int m = (l + r) / 2;
        if (i < m) {
            set(i, v, l, m, 2 * x + 1);
        } else {
            set(i, v, m, r, 2 * x + 2);
        }
        t[x] = max(t[2 * x + 1], t[2 * x + 2]);
    }

    void set(int i, int v) {
        set(i, v, 0, sz, 0);
    }

    int mx(int ql, int qr, int l, int r, int x) {
        if (ql <= l && r <= qr) {
            return t[x];
        }
        if (l >= qr || r <= ql) {
            return 0;
        }
        int m = (l + r) / 2;
        return max(mx(ql, qr, l, m, 2 * x + 1), mx(ql, qr, m, r, 2 * x + 2));
    }

    int mx(int l, int r) {
        return mx(l, r, 0, sz, 0);
    }
};

vector<vector<int>> g;
vector<int> cc;

void dfs(int u, vector<int>& sz, vector<int>& par, int p) {
    sz[u] = 1;
    par[u] = p;
    int mxi = -1, mx = 0;
    for (int i = 0; i < (int)g[u].size(); ++i) {
        int v = g[u][i];
        if (v == p) continue;
        dfs(v, sz, par, u);
        if (sz[v] > mx) {
            mxi = i;
            mx = sz[v];
        }
        sz[u] += sz[v];
    }
    if (mxi != -1) {
        int v = g[u][mxi];
        g[u].erase(g[u].begin() + mxi);
        reverse(g[u].begin(), g[u].end());
        g[u].push_back(v);
        reverse(g[u].begin(), g[u].end());
    }
}

void dfs1(int u, vector<int>& tourrr, vector<int>& tour, vector<int>& tin, vector<int>& tout,
          vector<int>& hig, int p, bool nado) {
    tin[u] = tour.size();
    if (nado) {
        cc[u] = cc[p];
    } else {
        cc[u] = u;
    }
    tour.push_back(u);
    tourrr.push_back(u);
    nado = true;
    for (auto& v : g[u]) {
        if (v == p) continue;
        hig[v] = hig[u] + 1;
        dfs1(v, tourrr, tour, tin, tout, hig, u, nado);
        nado = false;
        tour.push_back(u);
    }
    tout[u] = (int)tour.size() - 1;
}

int lca(int u, int v, vector<int>& tin, vector<int>& tout, segtree2& sg) {
    if (tin[u] > tout[v]) swap(u, v);
    return sg.mn(tin[u], tout[v] + 1).second;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }
    g.assign(n, vector<int>());
    cc.assign(n, 0);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> sz(n);
    vector<int> p(n);
    dfs(0, sz, p, 0);
    vector<int> tourhld, tour, tin(n), tout(n), hig(n);
    dfs1(0, tourhld, tour, tin, tout, hig, 0, false);
    int s = tour.size();
    segtree2 sg;
    sg.init(s);
    for (int i = 0; i < s; ++i) {
        sg.set(i, {tin[tour[i]], tour[i]});
    }
    vector<int> pos(n);
    segtree sghld;
    sghld.init((int)tourhld.size());
    for (int i = 0; i < (int)tourhld.size(); ++i) {
        pos[tourhld[i]] = i;
        sghld.set(i, h[tourhld[i]]);
    }
    int k;
    cin >> k;
    while (k--) {
        char c;
        cin >> c;
        if (c == '!') {
            int u, ht;
            cin >> u >> ht;
            --u;
            sghld.set(pos[u], ht);
        } else {
            int i, j;
            cin >> i >> j;
            --i, --j;
            int res = sghld.mx(pos[i], pos[i] + 1);
            int lc = lca(i, j, tin, tout, sg);
            int cur = i;
            while (hig[cur] > hig[lc]) {
                int pp = p[cur];
                if (hig[cc[pp]] <= hig[lc]) {
                    int psl = pos[lc], psr = pos[pp];
                    if (psl > psr) swap(psl, psr);
                    res = max(res, sghld.mx(psl, psr + 1));
                    cur = lc;
                } else {
                    int psl = pos[cc[pp]], psr = pos[pp];
                    if (psl > psr) swap(psl, psr);
                    res = max(res, sghld.mx(psl, psr + 1));
                    cur = cc[pp];
                }
            }
            cur = j;
            res = max(res, sghld.mx(pos[j], pos[j] + 1));
            while (hig[cur] > hig[lc]) {
                int pp = p[cur];
                if (hig[cc[pp]] <= hig[lc]) {
                    int psl = pos[lc], psr = pos[pp];
                    if (psl > psr) swap(psl, psr);
                    res = max(res, sghld.mx(psl, psr + 1));
                    cur = lc;
                } else {
                    int psl = pos[cc[pp]], psr = pos[pp];
                    if (psl > psr) swap(psl, psr);
                    res = max(res, sghld.mx(psl, psr + 1));
                    cur = cc[pp];
                }
            }
            cout << res << "\n";
        }
    }
}
