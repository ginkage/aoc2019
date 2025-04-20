#include "../lib.hpp"

unordered_map<string, vector<pair<long, string>>> deps;
unordered_map<string, long> amount;
unordered_map<string, long> rem;

long produce(long quant, string mat) {
    if (mat == "ORE")
        return quant;

    if (rem[mat] >= quant) {
        // we have enough of that material to satisfy our needs
        rem[mat] -= quant;
        return 0;
    }

    long div = amount[mat];             // produce per invocation
    long need = quant - rem[mat];       // required extra, after using up all that remains
    long prod = (need + div - 1) / div; // times to invoke to produce extra
    rem[mat] = prod * div - need;      // leftover after using what we need

    long result = 0;
    for (auto &p : deps[mat])
        result += produce(prod * p.first, p.second);
    return result;
}

int main() {
    const regex linerex("(.*) => (.*)");
    const regex reactrex("(.*) (.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            string right = linematch[2].str();

            vector<pair<long, string>> dep;
            for (string ss : split_s(linematch[1].str(), ", "))
                if (regex_match(ss, linematch, reactrex) && linematch.size() == 3)
                    dep.emplace_back(stoi(linematch[1].str()), linematch[2].str());

            if (regex_match(right, linematch, reactrex) && linematch.size() == 3) {
                string target = linematch[2].str();
                deps[target] = dep;
                amount[target] = stoi(linematch[1].str());
            }
        }
    }

    cout << produce(1, "FUEL") << endl;
    long result = -1, lower = 1, upper = 10000000;
    while (lower <= upper) {
        rem.clear();
        long mid = (lower + upper) / 2;
        long ore = produce(mid, "FUEL");
        if (ore > 1000000000000l)
            upper = mid - 1;
        else {
            result = mid;
            if (ore < 1000000000000l)
                lower = mid + 1;
            else
                break;
        }
    }
    cout << result << endl;

    return 0;
}

