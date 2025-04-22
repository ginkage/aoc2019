#include "../lib.hpp"

static int di[] = { -1, 0, 1, 0 };
static int dj[] = { 0, -1, 0, 1 };

vector<string> grid;
int m, n;

int main() {
    vector<string> next;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        grid.push_back(s);
        next.push_back(s);
    }

    m = grid.size();
    n = grid[0].size();

    uint32_t index = 0, bit = 1;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '#')
                index += bit;
            bit <<= 1;
        }

    unordered_set<uint32_t> met;
    met.insert(index);

    for (int t = 0; t < 30000; t++) {
        uint32_t index = 0, bit = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int adj = 0;
                for (int k = 0; k < 4; k++) {
                    int ni = i + di[k], nj = j + dj[k];
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] == '#')
                        adj++;
                }
                next[i][j] = ((grid[i][j] == '#' && adj == 1) || (grid[i][j] == '.' && (adj == 1 || adj == 2))) ? '#' : '.';
                if (next[i][j] == '#')
                    index += bit;
                bit <<= 1;
            }
        }
        if (met.find(index) != met.end()) {
            cout << index << endl;
            break;
        }
        met.insert(index);
        swap(grid, next);
    }

    return 0;
}

