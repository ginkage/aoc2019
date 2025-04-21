#include "../lib.hpp"

vector<string> grid;
int m, n;

vector<vec> delta = {
    { -1, 0 },
    { 0, -1 },
    { 0, 1 },
    { 1, 0 }
};

int main() {
    const regex linerex("([%&]?)(.*) -> (.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        grid.push_back(s);
    }

    m = grid.size();
    n = grid[0].size();

    vec start, finish;
    unordered_map<string, vec> port;
    unordered_map<vec, vec, VHash> jump;
    unordered_map<vec, bool, VHash> inner;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            bool is_port = false;
            bool in;
            string s;
            vec pos;

            if (grid[i][j] >= 'A' && grid[i][j] <= 'Z' && (i == 0 || grid[i-1][j] == '.' || grid[i-1][j] == ' ')
                    && i+1 < m && grid[i+1][j] >= 'A' && grid[i+1][j] <= 'Z') {
                s = string { grid[i][j], grid[i+1][j] };
                if (i == 0 || grid[i-1][j] == ' ') {
                    pos = vec(i + 2, j);
                    in = (i > m / 2);
                }
                else {
                    pos = vec(i - 1, j);
                    in = (i < m / 2);
                }
                is_port = true;
            }

            if (grid[i][j] >= 'A' && grid[i][j] <= 'Z' && (j == 0 || grid[i][j-1] == '.' || grid[i][j-1] == ' ')
                    && j+1 < n && grid[i][j+1] >= 'A' && grid[i][j+1] <= 'Z') {
                s = string { grid[i][j], grid[i][j+1] };
                if (j == 0 || grid[i][j-1] == ' ') {
                    pos = vec(i, j + 2);
                    in = (j > n / 2);
                }
                else {
                    pos = vec(i, j - 1);
                    in = (j < n / 2);
                }
                is_port = true;
            }

            if (is_port) {
                if (s == "AA")
                    start = pos;
                else if (s == "ZZ")
                    finish = pos;
                else {
                    inner[pos] = in;
                    auto it = port.find(s);
                    if (it == port.end())
                        port[s] = pos;
                    else {
                        jump[pos] = it->second;
                        jump[it->second] = pos;
                    }
                }
            }
        }

    unordered_map<int, unordered_map<vec, int, VHash>> visit;
    queue<pair<int, vec>> q;

    q.emplace(0, start);
    visit[0][start] = 0;
    while (!q.empty()) {
        auto &p = q.front();
        int level = p.first;
        vec pos = p.second;
        q.pop();

        int dist = visit[level][pos];
        if (level == 0 && pos == finish) {
            cout << dist << endl;
            break;
        }

        for (vec d : delta) {
            vec np = pos + d;
            if (grid[np[0]][np[1]] == '.' && visit[level].find(np) == visit[level].end()) {
                visit[level][np] = dist + 1;
                q.emplace(level, np);
            }
        }

        auto it = jump.find(pos);
        if (it != jump.end()) {
            vec np = it->second;
            int nl = inner[pos] ? level + 1 : level - 1;
            if (nl >= 0 && visit[nl].find(np) == visit[nl].end()) {
                visit[nl][np] = dist + 1;
                q.emplace(nl, np);
            }
        }
    }

    return 0;
}

