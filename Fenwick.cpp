class FenwickTree {
    vector<int> bit; // binary indexed tree
    int n;

public:
    FenwickTree(int size) {
        n = size;
        bit.assign(n + 1, 0);
    }

    // Add 'val' to index 'i' (0-based index)
    void update(int i, int val) {
        i++; // BIT uses 1-based indexing
        while (i <= n) {
            bit[i] += val;
            i += i & -i;
        }
    }

    // Get prefix sum from [0, i]
    int query(int i) {
        i++; // 1-based indexing
        int sum = 0;
        while (i > 0) {
            sum += bit[i];
            i -= i & -i;
        }
        return sum;
    }

    // Get sum in range [l, r]
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};
