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
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            bool is_port = false;
            string s;
            vec pos;

            if (grid[i][j] >= 'A' && grid[i][j] <= 'Z' && (i == 0 || grid[i-1][j] == '.' || grid[i-1][j] == ' ')
                    && i+1 < m && grid[i+1][j] >= 'A' && grid[i+1][j] <= 'Z') {
                s = string { grid[i][j], grid[i+1][j] };
                pos = vec((i == 0 || grid[i-1][j] == ' ') ? i + 2 : i - 1, j);
                is_port = true;
            }

            if (grid[i][j] >= 'A' && grid[i][j] <= 'Z' && (j == 0 || grid[i][j-1] == '.' || grid[i][j-1] == ' ')
                    && j+1 < n && grid[i][j+1] >= 'A' && grid[i][j+1] <= 'Z') {
                s = string { grid[i][j], grid[i][j+1] };
                pos = vec(i, (j == 0 || grid[i][j-1] == ' ') ? j + 2 : j - 1);
                is_port = true;
            }

            if (is_port) {
                if (s == "AA")
                    start = pos;
                else if (s == "ZZ")
                    finish = pos;
                else {
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

    unordered_map<vec, int, VHash> visit;
    queue<vec> q;

    q.push(start);
    visit[start] = 0;
    while (!q.empty()) {
        vec pos = q.front();
        q.pop();

        int dist = visit[pos];
        if (pos == finish) {
            cout << dist << endl;
            break;
        }

        for (vec d : delta) {
            vec np = pos + d;
            if (grid[np[0]][np[1]] == '.' && visit.find(np) == visit.end()) {
                visit[np] = dist + 1;
                q.push(np);
            }
        }

        auto it = jump.find(pos);
        if (it != jump.end()) {
            vec np = it->second;
            if (visit.find(np) == visit.end()) {
                visit[np] = dist + 1;
                q.push(np);
            }
        }
    }

    return 0;
}

