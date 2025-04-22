#include "../lib.hpp"

int main() {
    vector<int> deck(10007);
    for (int i = 0; i < deck.size(); i++)
        deck[i] = i;

    const regex cutrex("cut (.*)");
    const regex dealrex("deal with increment (.*)");
    const string deal = "deal into new stack";
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, cutrex) && linematch.size() == 2) {
            int cut = stoi(linematch[1].str());
            vector<int> next;
            if (cut < 0) cut += deck.size();
            next.insert(next.end(), deck.begin() + cut, deck.end());
            next.insert(next.end(), deck.begin(), deck.begin() + cut);
            swap(deck, next);
        }
        else if (regex_match(s, linematch, dealrex) && linematch.size() == 2) {
            int inc = stoi(linematch[1].str());
            vector<int> next(deck.size());
            for (int i = 0; i < deck.size(); i++)
                next[(i * inc) % deck.size()] = deck[i];
            swap(deck, next);
        }
        else if (s == deal)
            reverse(deck.begin(), deck.end());
    }
    for (int i = 0; i < deck.size(); i++)
        if (deck[i] == 2019)
            cout << i << endl;
    return 0;
}

