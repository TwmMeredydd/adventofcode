#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <map>

using namespace std;

static vector<string> input;

vector<long long> parseNumbers(string raw) {
    vector<long long> numbers;
    for (int i=0; i<raw.length(); i++) {
        numbers.push_back(0);
        while (!isdigit(raw[i])) i++;
        while (isdigit(raw[i])) {
            numbers.back() = numbers.back()*10 + int(raw[i])-48;
            i++;
        } 
    }

    return numbers;
}

int partOne() {
    vector<long long> cursors = parseNumbers(input[0]);
    int row = 3;
    array<vector<vector<long long>>, 7> maps;
    maps.fill({});
    
    for (int map=0; map<7; map++) {
        while(input[row] != "" && row < input.size()) {
            maps[map].push_back(parseNumbers(input[row]));
            row++;
        }
        row+=2;
    }

    for (int cursor_i=0; cursor_i<cursors.size(); cursor_i++) {
        for (vector<vector<long long>> map : maps) {
            long long cursor = cursors[cursor_i];
            for (vector<long long> node : map) {
                if (cursor >= node[1] && cursor < node[1] + node[2]) {
                    cursors[cursor_i] = node[0] + cursor - node[1];
                    break;
                }
            }
        }
    }

    long long lowest = cursors[0];
    for (long long cursor : cursors) if (cursor < lowest) lowest = cursor;

    return lowest;
}

int main() {
    //ifstream file("./input.example.txt");
    ifstream file("../../inputs/2023/05.txt");

    string line;
    if (file.is_open()) {
        while (getline(file, line)) input.push_back(line); 

        cout << partOne() << endl;
    }
}