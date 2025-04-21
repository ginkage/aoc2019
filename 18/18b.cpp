#include "../lib.hpp"

static vector<vec> delta = {
    { -1, 0 },
    { 0, -1 },
    { 0, 1 },
    { 1, 0 }
};

vector<string> grid;
int m, n;

inline uint64_t pack_state(vector<vec> &robots) {
    uint64_t state = 0;
    for (int k = 0; k < 4; k++)
        state |= ((((uint64_t)robots[k][1] << 7) | robots[k][0]) << (14 * k));
    return state;
}

void unpack_state(uint64_t state, vector<vec> &robots) {
    uint64_t mask = (1llu << 7) - 1;
    for (int k = 0; k < 4; k++) {
        robots[k][0] = (state & mask);
        state >>= 7;
        robots[k][1] = (state & mask);
        state >>= 7;
    }
}

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

    for (int k = -1; k <= 1; k++) {
        grid[pos[0]+k][pos[1]] = '#';
        grid[pos[0]][pos[1]+k] = '#';
    }

    vector<vec> robots = {
        { pos[0] - 1, pos[1] - 1 },
        { pos[0] - 1, pos[1] + 1 },
        { pos[0] + 1, pos[1] - 1 },
        { pos[0] + 1, pos[1] + 1 }
    };

    unordered_map<uint32_t, unordered_map<uint64_t, int>> visit;
    queue<pair<uint32_t, uint64_t>> q;
    uint64_t state = pack_state(robots);
    q.emplace(0, state);
    visit[0][state] = 0;

    while (!q.empty()) {
        auto &p = q.front();
        uint32_t keys = p.first;
        state = p.second;
        unpack_state(state, robots);
        q.pop();

        int dist = visit[keys][state];
        if (keys == all_keys) {
            cout << dist << endl;
            break;
        }

        for (int k = 0; k < 4; k++) {
            pos = robots[k];

            queue<pair<uint32_t, vec>> qr;
            unordered_map<vec, int, VHash> vr;
            unordered_set<uint32_t> pkeys;
            pkeys.insert(keys);
            qr.emplace(keys, pos);
            vr[pos] = dist;

            while (!qr.empty()) {
                auto &r = qr.front();
                uint32_t kr = r.first;
                pos = r.second;
                qr.pop();

                int way = vr[pos];
                if (pkeys.find(kr) == pkeys.end()) { // Found a new key
                    vector<vec> nr = robots;
                    nr[k] = pos;
                    uint64_t ns = pack_state(nr);
                    auto it = visit[kr].find(ns);
                    if (it == visit[kr].end() || it->second > way) {
                        visit[kr][ns] = way;
                        q.emplace(kr, ns);
                    }
                    pkeys.insert(kr);
                }

                for (int t = 0; t < 4; t++) {
                    uint32_t nk = keys;
                    vec np = pos + delta[t];
                    char c = grid[np[0]][np[1]];
                    if (c == '#') continue;
                    if (c >= 'A' && c <= 'Z') {
                        uint32_t door = (1lu << (c - 'A'));
                        if ((kr & door) == 0) continue;
                    }
                    if (c >= 'a' && c <= 'z')
                        nk |= (1lu << (c - 'a'));

                    if (vr.find(np) == vr.end()) {
                        vr[np] = way + 1;
                        qr.emplace(nk, np);
                    }
                }
            }
        }
    }

    return 0;
}

