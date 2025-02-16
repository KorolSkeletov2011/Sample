struct ed{
    int to, c, f, ind;
};

int s, t;

vector<int> ptr, d;
vector<vector<ed>> g;
vector<int> rev;
int n, cur;

int dfs(int u, int dl) {
    if (u == t || dl == 0) return dl;
    for (; ptr[u] < g[u].size(); ++ptr[u]) {
        auto& [v, c, f, ind] = g[u][ptr[u]];
        int cc = g[v][rev[ind]].c;
        if (d[v] == d[u] + 1 && max(cc, c) >= cur) {
            int dd = dfs(v, min(dl, c - f));
            if (dd != 0) {
                f += dd;
                g[v][rev[ind]].f -= dd;
                return dd;
            }
        }
    }
    return 0;
}

inline bool bfs() {
    vector<int> was(n);
    d.assign(n, 1e18);
    queue<int> q;
    d[s] = 0;
    q.push(s);
    was[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& [v, c, f, ind] : g[u]) {
            int cc = g[v][rev[ind]].c;
            if (was[v] || c == f || max(cc, c) < cur) continue;
            was[v] = 1;
            d[v] = d[u] + 1;
            q.push(v);
        }
    }
    return d[t] != 1e18;
}

{
    for (int i = 30; i >= 0; --i) {
        cur = 1ll << i;
        while (bfs()) {
            ptr.assign(n, 0);
            while (dfs(s, 1e18)) {}
        }
    }
}
