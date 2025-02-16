struct dsu {
    vector<int> rang, pred;
    vector<pair<int*, int>> updates;
 
 
    dsu(int n) {
        rang.resize(n, 1);
        pred.resize(n);
        std::iota(pred.begin(), pred.end(), 0);
    }
 
    int get(int v) {
        if (v == pred[v]) return v;
        return get(pred[v]);
    }
 
    void merge(int v, int u) {
        int x = get(u);
        int y = get(v);
        if (x == y) return;
        if (rang[x] < rang[y]) swap(x, y);
        updates.emplace_back(&rang[x], rang[x]);
        rang[x] += rang[y];
        updates.emplace_back(&pred[y], y);
        pred[y] = x;
    }
};

while (d.updates.size() > cnt) {
  *d.updates.back().first = d.updates.back().second;
  d.updates.pop_back();
}
