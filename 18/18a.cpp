#include "../lib.hpp"

static vector<vec> delta = {
    { -1, 0 },
    { 0, -1 },
    { 0, 1 },
    { 1, 0 }
};

vector<string> grid;
int m, n;

int main() {
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        grid.push_back(s);
    }

    m = grid.size();
    n = grid[0].size();

    uint32_t all_keys = 0;
    vec pos(0, 0);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            char c = grid[i][j];
            if (c =='@')
                pos = vec(i, j);
            else if (c >= 'a' && c <= 'z')
                all_keys |= (1lu << (c - 'a'));
        }

    unordered_map<uint32_t, unordered_map<vec, int, VHash>> visit;
    queue<pair<uint32_t, vec>> q;
    q.emplace(0, pos);
    visit[0][pos] = 0;

    while (!q.empty()) {
        auto &p = q.front();
        uint32_t keys = p.first;
        pos = p.second;
        q.pop();

        int dist = visit[keys][pos];
        if (keys == all_keys) {
            cout << dist << endl;
            break;
        }

        for (int k = 0; k < 4; k++) {
            uint32_t nk = keys;
            vec np = pos + delta[k];
            char c = grid[np[0]][np[1]];
            if (c == '#') continue;
            if (c >= 'A' && c <= 'Z') {
                uint32_t door = (1lu << (c - 'A'));
                if ((keys & door) == 0) continue;
            }
            if (c >= 'a' && c <= 'z')
                nk |= (1lu << (c - 'a'));
            if (visit[nk].find(np) == visit[nk].end()) {
                visit[nk][np] = dist + 1;
                q.emplace(nk, np);
            }
        }
    }

    return 0;
}

