#include "../lib.hpp"

typedef Eigen::Vector3i v3;

static inline int sign(int a) {
    return (a < 0 ? -1 : (a > 0 ? 1 : 0));
}

static inline v3 sign(v3 v) {
    return v3(sign(v[0]), sign(v[1]), sign(v[2]));
}

struct state_t {
    vector<v3> pos, vel;
};

int main() {
    vector<v3> pos, vel;
    const regex linerex("<x=(.*), y=(.*), z=(.*)>");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 4) {
            pos.emplace_back(stoi(linematch[1].str()), stoi(linematch[2].str()), stoi(linematch[3].str()));
            vel.emplace_back(0, 0, 0);
        }
    }

    vector<state_t> state;
    for (int t = 0; t < 1000000; t++) {
        state.push_back(state_t { pos, vel });

        for (int i = 0; i < pos.size(); i++)
            for (int j = 0; j < pos.size(); j++)
                if (i != j)
                    vel[i] += sign(pos[j] - pos[i]);

        for (int i = 0; i < pos.size(); i++)
            pos[i] += vel[i];
    }

    long period[3];
    for (int k = 0; k < 3; k++) {
        for (int w = 100; w < 500000; w++) {
            int n = state.size() - 1, np = n - w;
            bool good = true;
            for (int t = 0; t < w && good; t++)
                for (int i = 0; i < pos.size() && good; i++)
                    if (state[n - t].pos[i][k] != state[np - t].pos[i][k]
                            || state[n - t].vel[i][k] != state[np - t].vel[i][k])
                        good = false;
            if (good) {
                period[k] = w;
                cout << w << endl;
                break;
            }
        }
    }

    cout << lcm(period[0], lcm(period[1], period[2])) << endl;

    return 0;
}

