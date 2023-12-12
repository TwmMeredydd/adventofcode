#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> sequences;

int progressSequence(vector<int> sequence) {
    bool allZero = true;
    for (int i : sequence) if (i != 0) {
        allZero = false;
        break;
    }
    if (allZero) return 0;

    vector<int> differences;
    for (int i=1; i<sequence.size(); i++) differences.push_back(sequence[i]-sequence[i-1]);
    return sequence.back()+progressSequence(differences);
}

int partOne() {
    int total = 0;
    for (vector<int> sequence : sequences) total += progressSequence(sequence);

    return total;
}

int regressSequence(vector<int> sequence) {
    bool allZero = true;
    for (int i : sequence) if (i != 0) {
        allZero = false;
        break;
    }
    if (allZero) return 0;

    vector<int> differences;
    for (int i=1; i<sequence.size(); i++) differences.push_back(sequence[i]-sequence[i-1]);
    return sequence.front() - regressSequence(differences);
}

int partTwo() {
    int total = 0;
    for (vector<int> sequence : sequences) total += regressSequence(sequence);

    return total;
}

int main() {
    //ifstream file("./input.example.txt");
    ifstream file("../../inputs/2023/09.txt");

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            sequences.push_back({});
            for (int i=0; i<line.length(); i++) {
                sequences.back().push_back(0);
                bool negative = false;
                if (line[i] == '-') {
                    negative = true;
                    i++;
                }
                while (isdigit(line[i])) {
                    sequences.back().back() = sequences.back().back()*10 + int(line[i]) - 48;
                    i++;
                }
                if (negative) sequences.back().back() *= -1;
            }
        }

        cout << "Part 1: " << partOne() << endl;
        cout << "Part 2: " << partTwo() << endl;

        file.close();
    } else {
        cout << "Unable to read input" << endl;
    }
}
