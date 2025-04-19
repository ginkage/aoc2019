#include "../lib.hpp"

vector<long> original;

void run(long input) {
    vector<long> program = original;
    for (int i = 0; i < program.size();) {
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
            program[arg] = input;
        }
        else if (op == 4) {
            long arg = program[i++];
            cout << program[arg] << endl;
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
        else break;
    }
}

int main() {
    string s;
    getline(cin, s);
    original = split_l(s, ",");
    run(1);
    run(5);
    return 0;
}
