#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> format1;
vector<vector<int>> format2;

struct Line {
    string diagram;
    vector<int> numbers;
};

vector<Line> lines;

vector<int> countDamaged(string blocks) {
    vector<int> blockLengths;
    int length = 0;
    for (char c : blocks) {
        if (c == '#') length++;
        else if (length > 0) {
            blockLengths.push_back(length);
            length = 0;
        }
    }
    return blockLengths;
}

int dfs (string blocks, int i, vector<int> criteria) {
    int solutions = 0;

    bool valid = true;
    vector<int> currentBlocks = countDamaged(blocks.substr(0,i));
    //Putting the size calculation inside the loop condition doesn't work for some reason.
    int currentBlocksLength = currentBlocks.size()-1;
    for (int i=0; i<currentBlocksLength; i++) {
        if (currentBlocks[i] != criteria[i]) valid = false;
    }
    if (!valid) return 0;

    if (i < blocks.length()) {
        if (blocks[i] == '?') {
            for (char c : {'.', '#'}) {
                solutions += dfs(blocks.substr(0,i) + c + blocks.substr(i+1), i+1, criteria);
            }
            return solutions;
        }
        return dfs(blocks, i+1, criteria);
    }
    if (countDamaged(blocks) == criteria) return 1;
    return 0;
}

int partOne() {
    int solutions = 0;
    for (Line line : lines) {
        solutions += dfs(line.diagram, 0, line.numbers);
    }
    return solutions;
}

int main() {
    //ifstream file("./input.example.txt");
    ifstream file("../../inputs/2023/12.txt");

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            string diagram;
            string numberStr;
            for (int i=0;;i++) if (line[i] == ' ') {
                diagram = line.substr(0, i);
                numberStr = line.substr(i+1, line.length()-i+1) + ',';
                break;
            }
            vector<int> numVec;
            int num = 0;
            for (char c : numberStr) {
                if (c == ',') {
                    numVec.push_back(num);
                    num=0;
                } else 
                    num = num * 10 + int(c) - 48;
            }
            lines.push_back({diagram + '.', numVec});
        }

        cout << partOne() << endl;
    } else {
        cout << "Unable to read inputs." << endl;
    }

    return 0;
}
