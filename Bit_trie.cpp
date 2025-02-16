struct trie{
    const int lg = 29;

    struct node{
        int mn;
        int nxt[2];
 
        node(int mn0 = 1e9, int l0 = -1, int r0 = -1) {
            mn = mn0;
            nxt[0] = l0;
            nxt[1] = r0;
        }
    };
 
    vector<node> t;
 
    void init() {
        t.push_back({});
    }
 
    int getm(int i) {
        return i == -1 ? 1e9 : t[i].mn;
    }
 
    void upd(int i) {
        if (i == -1) return;
        t[i].mn = min(getm(t[i].nxt[0]), getm(t[i].nxt[1]));
    }
 
    void add(int a, int i) {
        int cur = 0;
        for (int bt = lg; bt >= 0; --bt) {
            t[cur].mn = min(t[cur].mn, i);
            bool b = a & (1ll << bt);
            if (t[cur].nxt[b] == -1) {
                t[cur].nxt[b] = (int)t.size();
                t.push_back({});
            }
            cur = t[cur].nxt[b];
 
        }
        t[cur].mn = min(i, t[cur].mn);
    }
 
    int sp(int a, int k) {
        int cur = 0, res = 1e9;
        for (int bt = lg; bt >= 0; --bt) {
            bool bk = k & (1ll << bt), ba = a & (1ll << bt);
            if (!bk) {
                cur = t[cur].nxt[ba];
            } else {
                res = min(res, getm(t[cur].nxt[ba]));
                cur = t[cur].nxt[!ba];
            }
            if (cur == -1) break;
        }
        res = min(res, getm(cur));
        return res;
    }
};
