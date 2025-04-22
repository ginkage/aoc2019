#include "../lib.hpp"

static int di[] = { -1, 0, 1, 0 };
static int dj[] = { 0, -1, 0, 1 };

typedef Eigen::Vector3i v3;

uint32_t bit(int i, int j) {
    return (1lu << (i * 5 + j));
}

int main() {
    vector<string> grid;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        grid.push_back(s);
    }

    unordered_map<int, uint32_t> level;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (grid[i][j] == '#')
                level[0] |= bit(i, j);

    unordered_map<vec, vector<v3>, VHash> edge;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (i != 2 || j != 2)
                for (int k = 0; k < 4; k++) {
                    int ni = i + di[k], nj = j + dj[k];
                    if (ni != 2 || nj != 2) {
                        v3 adj(ni, nj, 0);
                        if (ni < 0)
                            adj = v3(1, 2, -1);
                        else if (ni > 4)
                            adj = v3(3, 2, -1);
                        else if (nj < 0)
                            adj = v3(2, 1, -1);
                        else if (nj > 4)
                            adj = v3(2, 3, -1);

                        edge[vec(i, j)].push_back(adj);
                        if (adj[2] < 0)
                            edge[vec(adj[0], adj[1])].push_back(v3(i, j, 1));
                    }
                }

    int mn = 0, mx = 0;
    for (int t = 0; t < 200; t++) {
        unordered_map<int, uint32_t> next;
        for (int k = mn - 1; k <= mx + 1; k++)
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++) {
                    int adj = 0;
                    for (v3 e : edge[vec(i, j)])
                        if (level[k + e[2]] & bit(e[0], e[1]))
                            adj++;
                    if (adj == 1 || (adj == 2 && !(level[k] & bit(i, j)))) {
                        next[k] |= bit(i, j);
                        mn = min(mn, k);
                        mx = max(mx, k);
                    }
                }
        swap(level, next);
    }

    int result = 0;
    for (int k = mn; k <= mx; k++)
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (level[k] & bit(i, j))
                    result++;
    cout << result << endl;

    return 0;
}

