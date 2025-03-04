#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <set>
#include <iomanip>
#include <string>
using namespace std;

double distance(pair<double, double> p1, pair<double, double> p2) {
    return sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}

void traceback(int i, int s, const vector<vector<int>>& S, set<pair<int, int>>& R, int cnt) {
    int k = S[i][s];
    if (k == -1 || s < 3) return;
    int i1 = i;
    int i2 = (i + k) % cnt;
    int i3 = (i + s - 1) % cnt;

    auto add_diagonal = [&](int a, int b) {
        if (abs(a - b) != 1 && abs(a - b) != cnt - 1) {
            int x = min(a, b);
            int y = max(a, b);
            R.insert({ x, y });
        }
        };

    add_diagonal(i1, i2);
    add_diagonal(i2, i3);
    add_diagonal(i3, i1);

    traceback(i, k + 1, S, R, cnt);
    traceback((i + k) % cnt, s - k, S, R, cnt);
}

int main() {
    ifstream file, in;
    ofstream result;
    string S_input, input, output;

    result << fixed << setprecision(3);
    file.open("./MT_command.txt"); 

    if (!file.is_open()) {
        cout << "Error opening file: MT_command.txt\n";
        return 0;
    }

    file >> S_input;
    int command_cnt = stoi(S_input);
    while (command_cnt--) {
        vector<pair<double, double> > P;

        file >> input >> output;

        in.open("./" + input); 
        result.open("./" + output);

        if (!in.is_open()) {
            cout << "Error opening file: " << input << "\n";
            return 0;
        }

        in >> S_input;
        int cnt = stoi(S_input);
        vector<vector<double> > C(cnt + 1, vector<double>(cnt + 1, 0));
        vector<vector<int>> S(cnt + 1, vector<int>(cnt + 1, -1));
        set<pair<int, int> > R;
        double x, y;

        for (int i = 0; i < cnt; i++) {
            in >> x >> y; 
            P.push_back({ x,y });
        }

        for (int s = 4; s <= cnt; s++) {
            for (int i = 0; i < cnt; i++) {
                C[i][s] = numeric_limits<double>::max();

                for (int k = 1; k <= s - 2; k++) {
                    double cost = C[i][k + 1] + C[(i + k) % cnt][s - k];
                    if (k > 1) cost += distance(P[i], P[(i + k) % cnt]);
                    if (abs(k - s + 1) > 1) cost += distance(P[(i + k) % cnt], P[(i + s - 1) % cnt]);

                    if (cost < C[i][s]) {
                        C[i][s] = cost;
                        S[i][s] = k;
                    }
                }
            }
        }

        result << C[0][cnt] << "\n";

        traceback(0, cnt, S, R, cnt);

        for (const auto& edge : R) {
            result << edge.first << " " << edge.second << "\n";
        }

        in.close();
        result.close();
    }

    file.close();

    return 0;
}