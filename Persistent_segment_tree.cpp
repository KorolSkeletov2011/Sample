const int lg = 19;
const int inf = 2e9;
 
struct node{
    int mn, l, r;
};
 
struct segtree{
    vector<node> tr;
 
    int mn(int x) {
        if (x == -1) return inf;
        return tr[x].mn;
    }
 
    void set(int i, int v, int l, int r, int x) {
        if (r - l == 1) {
            tr[x].mn = min(tr[x].mn, v);
            return;
        }
        int m = (l + r) / 2;
        if (i < m) {
            if (tr[x].l == -1) {
                tr.push_back({inf, -1, -1});
                tr[x].l = (int)tr.size() - 1;
            }
            set(i, v, l, m, tr[x].l);
        } else {
            if (tr[x].r == -1) {
                tr.push_back({inf, -1, -1});
                tr[x].r = (int)tr.size() - 1;
            }
            set(i, v, m, r, tr[x].r);
        }
        tr[x].mn = min(mn(tr[x].l), mn(tr[x].r));
    }
 
    void set(int i, int v) {
        if (tr.empty()) {
            tr.push_back({inf, -1, -1});
        }
        set(i, v, 0, 2e5 + 1, 0);
    }
 
    int get(int t, int l, int r, int x) {
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int mnr = mn(tr[x].r);
        if (mnr <= t) {
            return get(t, m, r, tr[x].r);
        }
        return get(t, l, m, tr[x].l);
    }
 
    int get(int t) {
        return get(t, 0, 2e5 + 1, 0);
    }
};
