#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

struct Line {
    string diagram;
    list<int> numbers;
};

vector<Line> lines;

list<int> countDamaged(string blocks) {
    list<int> blockLengths = {0};
    for (char c : blocks) {
        if (c == '#') blockLengths.back()++;
        else if (blockLengths.back()) blockLengths.push_back(0);
    }
    return blockLengths;
}

string getKey(string blocks, int damagedStreak, list<int> criteria) {
    string key = blocks + '_' + to_string(damagedStreak) + "_";
    for (int i : criteria) key += to_string(i) + ',';
    return key;
}

long dfs (string blocks, int damagedStreak, list<int> criteria, unordered_map<string, long> &cache) {
    const string key = getKey(blocks, damagedStreak, criteria);
    if (cache.find(key) != cache.end()) return cache[key];
    if (damagedStreak > criteria.front()) return 0;
    if (blocks.empty()) return criteria.empty();

    long solutions = 0;
    list<int> remainingCriteria;

    switch (blocks[0]) {
        case '?':
            for (char c : {'.', '#'}) solutions += dfs(c + blocks.substr(1), damagedStreak, criteria, cache);
            break;
        case '.':
            copy(criteria.begin(), criteria.end(), back_inserter(remainingCriteria));
            if (!criteria.empty()) {
                if (damagedStreak < criteria.front() && damagedStreak > 0) return 0;
                if (damagedStreak == criteria.front()) remainingCriteria.pop_front();
            }
            solutions += dfs(blocks.substr(1), 0, remainingCriteria, cache);
            break;
        case '#':
            if (criteria.empty()) return 0;
            solutions += dfs(blocks.substr(1), damagedStreak+1, criteria, cache);
            break;
    }

    cache[getKey(blocks, damagedStreak, criteria)] = solutions;
    return solutions;
}

int partOne() {
    int solutions = 0;
    for (Line line : lines) {
        unordered_map<string, long> cache;
        solutions += dfs(line.diagram + '.', 0, line.numbers, cache);
    }
    return solutions;
}

long partTwo() {
    long solutions = 0;
    for (Line line : lines) {
        unordered_map<string, long> cache;
        list<int> numbers;
        string diagram = line.diagram;
        for (int i=0; i<5; i++) copy(line.numbers.begin(), line.numbers.end(), back_inserter(numbers));
        for (int i=0; i<4; i++) diagram += '?' + line.diagram;
        solutions += dfs(diagram + '.', 0, numbers, cache);
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
            list<int> numVec;
            int num = 0;
            for (char c : numberStr) {
                if (c == ',') {
                    numVec.push_back(num);
                    num=0;
                } else 
                    num = num * 10 + int(c) - 48;
            }
            lines.push_back({diagram, numVec});
        }

        cout << partOne() << endl;
        cout << partTwo() << endl;
    } else {
        cout << "Unable to read inputs." << endl;
    }

    return 0;
}
