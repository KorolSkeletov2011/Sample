vector<int> res, fst;
vector<vector<int>> g;
 
void dfs(int u) {
    int i = fst[u];
    while (i < (int)g[u].size()) {
        auto v = g[u][i];
        ++fst[u];
        dfs(v);
        i = fst[u];
    }
    res.push_back(u);
}
