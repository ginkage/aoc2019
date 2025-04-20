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

int main() {
    string s;
    getline(cin, s);
    state_t state;
    auto program = split_l(s, ",");

    for (int i = 0; i < program.size(); i++)
        state.program[i] = program[i];

    vec ball, padd;
    vec mn(0, 0), mx(0, 0);
    unordered_map<vec, int, VHash> space;
    while (!state.halt) {
        run(state);
        while (!state.output.empty()) {
            int x = state.output.front();
            state.output.pop();
            int y = state.output.front();
            state.output.pop();
            int id = state.output.front();
            state.output.pop();
            vec pos(y, x);
            space[pos] = id;
            mn = vec(min(mn[0], pos[0]), min(mn[1], pos[1]));
            mx = vec(max(mx[0], pos[0]), max(mx[1], pos[1]));
        }
    }

    state = state_t();
    for (int i = 0; i < program.size(); i++)
        state.program[i] = program[i];
    state.program[0] = 2;

    long score = 0;
    space.clear();
    while (!state.halt) {
        run(state);
        while (!state.output.empty()) {
            int x = state.output.front();
            state.output.pop();
            int y = state.output.front();
            state.output.pop();
            int id = state.output.front();
            state.output.pop();
            if (x < 0 && y == 0) {
                score = id;
            }
            else {
                vec pos(y, x);
                space[pos] = id;
                mn = vec(min(mn[0], pos[0]), min(mn[1], pos[1]));
                mx = vec(max(mx[0], pos[0]), max(mx[1], pos[1]));

                if (id == 3)
                    padd = pos;
                if (id == 4)
                    ball = pos;
            }
        }

        if (ball[1] > padd[1])
            state.input.push(1);
        else if (ball[1] < padd[1])
            state.input.push(-1);
        else
            state.input.push(0);

        usleep(10000);
        cout << "\033[2J\033[1;1H";
        for (int i = mn[0]; i <= mx[0]; i++) {
            for (int j = mn[1]; j <= mx[1]; j++)
                switch (space[vec(i, j)]) {
                    case 0: cout << ' '; break;
                    case 1: cout << '#'; break;
                    case 2: cout << 'H'; break;
                    case 3: cout << '='; break;
                    case 4: cout << 'o'; break;
                }
            cout << endl;
        }
        cout << score << endl;
    }

    return 0;
}

