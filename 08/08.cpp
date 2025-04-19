#include "../lib.hpp"

int main() {
    string s;
    getline(cin, s);

    vector<string> image(6, string(25, ' '));

    int t = 0, ms = -1, mr = -1;
    while (t < s.size()) {
        int zeros = 0, ones = 0, twos = 0;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 25; j++) {
                char digit = s[t++];
                //cout << s[t++];
                if (digit == '0')
                    zeros++;
                else if (digit == '1')
                    ones++;
                else if (digit == '2')
                    twos++;

                if (image[i][j] == ' ')
                    image[i][j] = (digit == '2' ? ' ' : (digit == '1' ? '#' : '.'));
            }
            //cout << endl;
        }
        //cout << endl;
        if (ms < 0 || ms > zeros) {
            ms = zeros;
            mr = ones * twos;
        }
    }
    cout << mr << endl;

    for (string ss : image)
        cout << ss << endl;

    return 0;
}

