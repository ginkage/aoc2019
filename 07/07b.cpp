#include "../lib.hpp"

struct state_t {
    vector<long> program;
    queue<long> input;
    queue<long> *output;
    int ip;
    bool halt;
};

void run(state_t &st) {
    vector<long> &program = st.program;
    int i = st.ip;
    while (i < program.size()) {
        long op = program[i++];
        int m1 = (op / 100) % 10;
        int m2 = (op / 1000) % 10;
        op %= 100;

        if (op == 1) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            long arg3 = program[i++];
            program[arg3] = (m1 ? arg1 : program[arg1]) + (m2 ? arg2 : program[arg2]);
        }
        else if (op == 2) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            long arg3 = program[i++];
            program[arg3] = (m1 ? arg1 : program[arg1]) * (m2 ? arg2 : program[arg2]);
        }
        else if (op == 3) {
            long arg = program[i++];
            if (st.input.empty()) break;
            program[arg] = st.input.front();
            st.input.pop();
        }
        else if (op == 4) {
            long arg = program[i++];
            st.output->push(program[arg]);
        }
        else if (op == 5) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            if (m1 ? arg1 : program[arg1])
                i = (m2 ? arg2 : program[arg2]);
        }
        else if (op == 6) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            if (!(m1 ? arg1 : program[arg1]))
                i = (m2 ? arg2 : program[arg2]);
        }
        else if (op == 7) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            long arg3 = program[i++];
            program[arg3] = (m1 ? arg1 : program[arg1]) < (m2 ? arg2 : program[arg2]);
        }
        else if (op == 8) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            long arg3 = program[i++];
            program[arg3] = (m1 ? arg1 : program[arg1]) == (m2 ? arg2 : program[arg2]);
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
    vector<long> program = split_l(s, ",");

    long result = 0;
    vector<state_t> state(5);
    vector<long> set = { 5, 6, 7, 8, 9 };
    do {
        for (int i = 0; i < 5; i++) {
            state[i].program = program;
            state[i].input = queue<long>();
            state[i].input.push(set[i]);
            state[i].output = &(state[(i + 1) % 5]).input;
            state[i].ip = 0;
            state[i].halt = false;
        }

        bool all_halt = false;
        state[0].input.push(0);
        while (!all_halt) {
            all_halt = true;
            for (int i = 0; i < 5; i++)
                if (!state[i].halt) {
                    run(state[i]);
                    all_halt = false;
                }
        }

        long out = state[0].input.back();
        if (result < out)
            result = out;
    }
    while (next_permutation(set.begin(), set.end()));
    cout << result << endl;
    return 0;
}

