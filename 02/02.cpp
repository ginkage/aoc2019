#include "../lib.hpp"

vector<uint64_t> input;

uint64_t run(int noun, int verb) {
    vector<uint64_t> program = input;
    program[1] = noun;
    program[2] = verb;
    for (int i = 0; i < program.size(); i += 4) {
        if (program[i] == 1) {
            if (program[i+1] >= program.size() || program[i+2] >= program.size()) return -1;
            program[program[i+3]] = program[program[i+1]] + program[program[i+2]];
        }
        else if (program[i] == 2) {
            if (program[i+1] >= program.size() || program[i+2] >= program.size()) return -1;
            program[program[i+3]] = program[program[i+1]] * program[program[i+2]];
        }
        else if (program[i] == 99)
            break;
        else
            return -1;
    }
    return program[0];
}

int main() {
    string s;
    getline(cin, s);
    input = split_u64(s, ",");
    cout << run(12, 2) << endl;
    for (int i = 0; i <= 99; i++)
        for (int j = 0; j <= 99; j++)
            if (run(i, j) == 19690720) {
                cout << (100 * i + j) << endl;
                return 0;
            }
    return 0;
}

