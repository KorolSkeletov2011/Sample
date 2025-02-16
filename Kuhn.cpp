vector<vector<int>> g, gr;
vector<int> was, lp;
int T = 0;
 
bool dfs(int u) {
    if (was[u] == T) return false;
    was[u] = T;
    for (auto& v : g[u]) {
        if (lp[v] == -1) {
            lp[v] = u;
            return true;
        }
    }
    for (auto& v : g[u]) {
        if (dfs(lp[v])) {
            lp[v] = u;
            return true;
        }
    }
    return false;
}

{
 for (int i = 0; i < n; ++i) {
        if (dfs(i)) {
            ++T;
        }
    }
}
