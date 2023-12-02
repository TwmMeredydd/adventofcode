#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

int part_one(list<string> lines) {
    int total = 0;

    for (string line : lines) {
        int first = -1;
        int last;

        for (string::iterator it=line.begin(); it!=line.end(); ++it) {
            if (int(*it) >= 48 && int(*it) <= 57) {
                if (first == -1) first = int(*it) - 48;
                last = int(*it) - 48;
            }
        }
        total += first * 10 + last;
    }

    return total;
}

int part_two(list<string> lines) {
    int total = 0;
    const string digits[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    
    for (string line : lines) {
        int first = -1;
        int last;
        string search = "";

        for (string::iterator it=line.begin(); it!=line.end(); ++it) {
            search += *it;
            if (int(*it) >= 48 && int(*it) <= 57) {
                if (first == -1) first = int(*it) - 48;
                last = int(*it) - 48;
            } else {
                for (int i=0; i<9; i++) {
                    if (search.find(digits[i]) != string::npos) {
                        if (first == -1) first = i+1;
                        last = i+1;
                        search = *it;
                    }
                }
            }
        }

        total += first * 10 + last;
    }

    return total;
}

int main(int argc, char* argv[]) {
    ifstream file("../../inputs/2023/01.txt");

    if (file.is_open()) {
        list<string> lines;
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }

        file.close();

        cout << "Part 1: " << part_one(lines) << endl;
        cout << "Part 2: " << part_two(lines) << endl;
    } else {
        cout << "Unable to read in input file" << endl;
    }

    return 0;
}
