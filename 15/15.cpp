#include "../lib.hpp"

struct state_t {
    unordered_map<long, long> program;
    queue<long> input;
    queue<long> output;
    long ip { 0 };
    long base { 0 };
    bool halt { false };

    long get(long arg, int mode) {
        if (mode == 1)
            return arg;
        return program[(mode == 0) ? arg : (base + arg)];
    }

    void put(long arg, int mode, long value) {
        program[(mode == 0) ? arg : (base + arg)] = value;
    }
};

void run(state_t &st) {
    unordered_map<long, long> &program = st.program;
    int i = st.ip;
    while (!st.halt) {
        long op = program[i++];
        int m1 = (op / 100) % 10;
        int m2 = (op / 1000) % 10;
        int m3 = (op / 10000) % 10;
        op %= 100;

        if (op == 1) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            long arg3 = program[i++];
            st.put(arg3, m3, st.get(arg1, m1) + st.get(arg2, m2));
        }
        else if (op == 2) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            long arg3 = program[i++];
            st.put(arg3, m3, st.get(arg1, m1) * st.get(arg2, m2));
        }
        else if (op == 3) {
            long arg1 = program[i++];
            if (st.input.empty()) break;
            st.put(arg1, m1, st.input.front());
            st.input.pop();
        }
        else if (op == 4) {
            long arg1 = program[i++];
            st.output.push(st.get(arg1, m1));
        }
        else if (op == 5) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            if (st.get(arg1, m1))
                i = st.get(arg2, m2);
        }
        else if (op == 6) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            if (!st.get(arg1, m1))
                i = st.get(arg2, m2);
        }
        else if (op == 7) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            long arg3 = program[i++];
            st.put(arg3, m3, st.get(arg1, m1) < st.get(arg2, m2));
        }
        else if (op == 8) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            long arg3 = program[i++];
            st.put(arg3, m3, st.get(arg1, m1) == st.get(arg2, m2));
        }
        else if (op == 9) {
            long arg1 = program[i++];
            st.base += st.get(arg1, m1);
        }
        else {
            st.halt = true;
            break;
        }
        st.ip = i;
    }
}

unordered_map<int, vec> delta = {
    { 1, { -1, 0 } },
    { 2, { 1, 0 } },
    { 3, { 0, -1 } },
    { 4, { 0, 1 } }
};

int main() {
    string s;
    getline(cin, s);
    state_t state;
    auto program = split_l(s, ",");

    for (int i = 0; i < program.size(); i++)
        state.program[i] = program[i];

    bool hit = false;
    int dir = 1;
    vec pos(0, 0), mn(0, 0), mx(0, 0), oxy(0, 0);
    unordered_map<vec, int, VHash> space;
    space[pos] = 1;

    while (!state.halt) {
        state.input.push(dir);
        run(state);

        while (!state.output.empty()) {
            int out = state.output.front();
            state.output.pop();

            vec np = pos + delta[dir];
            if (out == 0) {
                space[np] = 2;

                hit = true;
                switch (dir) { // turn left
                    case 1: dir = 3; break;
                    case 2: dir = 4; break;
                    case 3: dir = 2; break;
                    case 4: dir = 1; break;
                }
            }
            else {
                pos = np;

                if (out == 1)
                    space[pos] = 1;
                else {
                    oxy = pos;
                    space[pos] = 3;
                }

                if (hit) {
                    // otherwise we're still looking for a wall
                    switch (dir) { // turn right
                        case 1: dir = 4; break;
                        case 2: dir = 3; break;
                        case 3: dir = 1; break;
                        case 4: dir = 2; break;
                    }
                }
            }
            mn = vec(min(mn[0], np[0]), min(mn[1], np[1]));
            mx = vec(max(mx[0], np[0]), max(mx[1], np[1]));
        }

        usleep(10000);
        cout << "\033[2J\033[1;1H";
        for (int i = mn[0]; i <= mx[0]; i++) {
            for (int j = mn[1]; j <= mx[1]; j++)
                switch (space[vec(i, j)]) {
                    case 0: cout << '?'; break;
                    case 1: cout << ' '; break;
                    case 2: cout << '#'; break;
                    case 3: cout << 'X'; break;
                }
            cout << endl;
        }

        if ((oxy[0] != 0 || oxy[1] != 0) && pos[0] == 0 && pos[1] == 0)
            break;
    }

    queue<vec> q;
    q.push(vec(0, 0));
    unordered_map<vec, int, VHash> visit;
    visit[vec(0, 0)] = 0;
    while (!q.empty()) {
        pos = q.front();
        q.pop();
        int d = visit[pos];
        if (pos == oxy) {
            cout << d << endl;
            break;
        }

        for (auto &p : delta) {
            vec next = pos + p.second;
            if (space[next] != 2 && visit.find(next) == visit.end()) {
                q.push(next);
                visit[next] = d + 1;
            }
        }
    }

    int result = 0;
    q = queue<vec>();
    q.push(oxy);
    visit.clear();
    visit[oxy] = 0;
    while (!q.empty()) {
        pos = q.front();
        q.pop();
        result = visit[pos];

        for (auto &p : delta) {
            vec next = pos + p.second;
            if (space[next] != 2 && visit.find(next) == visit.end()) {
                q.push(next);
                visit[next] = result + 1;
            }
        }
    }
    cout << result << endl;

    return 0;
}

