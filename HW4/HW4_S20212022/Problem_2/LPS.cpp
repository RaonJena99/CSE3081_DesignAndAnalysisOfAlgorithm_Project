#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ifstream file, in;
    ofstream result;
    string S, input, output;
    file.open("./LPS_command.txt"); 

    if (!file.is_open()) {
        cout << "Error opening file: LPS_command.txt\n";
        return 0;
    }

    file >> S;
    int command_cnt = stoi(S);
    while (command_cnt--) {
        file >> input >> output;

        in.open("./" + input); 
        result.open("./" + output); 

        if (!in.is_open()) {
            cout << "Error opening file: " << input << "\n";
            return 0;
        }

        in >> S;
        int SQ = stoi(S);
        result << SQ << "\n";
        while (SQ--) {
            string sequence;
            int len, max_len = 0;
            in >> len >> sequence;

            vector<vector<int> > V(len, vector<int>(len, 0));
            vector<vector<string> > S(len, vector<string>(len, ""));

            for (int i = 0; i < len; i++) { 
                V[i][i] = 1;
                S[i][i] = sequence[i];
            }

            for (int i = 2; i <= len; i++) {
                for (int j = 0; j < len - i + 1; j++) {
                    int k = j + i - 1;

                    if (sequence[j] == sequence[k]) {
                        if (i == 2) {
                            V[j][k] = 2;
                            S[j][k] = sequence[j] + sequence[k];
                        }
                        else {
                            V[j][k] = V[j + 1][k - 1] + 2;
                            S[j][k] = sequence[j] + S[j + 1][k - 1] + sequence[k];
                        }
                    }

                    else {
                        V[j][k] = max(V[j][k - 1], V[j + 1][k]);
                        if (S[j][k - 1].size() > S[j + 1][k].size()) {
                            S[j][k] = S[j][k - 1];
                        }
                        else S[j][k] = S[j + 1][k];
                    }
                }
            }

            max_len = V[0][len - 1];
            result << max_len << "\n";;
            result << S[0][len - 1] << "\n";;
        }
        in.close();
        result.close();
    }

    file.close();

    return 0;
}