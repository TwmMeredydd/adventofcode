#include <iostream>
#include <fstream>
#include <list>
#include <map>

using namespace std;

map<char, int> max_quantities;

int partOne(list<string> lines) {
    int id_total = 0;
    for (string line : lines) {
        int id=0;
        int i=5;

        while (line[i] != ':') {
            id = id*10 + int(line[i])-48;
            i++;
        }

        int quantity;
        bool invalid = false;
        while (true) {
            quantity = 0;
            while (int(line[i]) < 48 || int(line[i]) > 57) {
                i++;
                if (i >= line.length()) goto nextline;
            };
            while (line[i] != ' ') {
                quantity = quantity * 10 + int(line[i]) - 48;
                i++;
            }
            if (invalid = quantity > max_quantities[line[i+1]]) break;
        }
        nextline:
        if (!invalid) id_total += id;
    }

    return id_total;
}

int partTwo(list<string> lines) {
    int power_total = 0;
    for (string line : lines) {
        int i = 0;
        while (line[i] != ':') i++;

        map<char, int> greatest_num;
        while (true) {
            int quantity = 0;
            while (int(line[i]) < 48 || int(line[i]) > 57) {
                i++;
                if (i >= line.length()) goto finishline;
            };
            while (line[i] != ' ') {
                quantity = quantity * 10 + int(line[i]) - 48;
                i++;
            }

            if (greatest_num[line[i+1]] < quantity) greatest_num[line[i+1]] = quantity;
        }

        finishline:
        power_total += greatest_num['r'] * greatest_num['g'] * greatest_num['b'];
    }

    return power_total;
}

int main() {
    max_quantities['r'] = 12;
    max_quantities['g'] = 13;
    max_quantities['b'] = 14;

    //ifstream file("./input.example.txt");
    ifstream file("../../inputs/2023/02.txt");

    if (file.is_open()) {
        list<string> lines;
        string line;
        while (getline(file, line)) lines.push_back(line);
        file.close();

        cout << "Part 1: " << partOne(lines) << endl;
        cout << "Part 2: " << partTwo(lines) << endl;
    } else {
        cout << "Unable to read from input file" << endl;
    }

    return 0;
}
