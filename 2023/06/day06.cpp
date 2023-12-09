#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct Race {
    int time;
    int distance;
};

vector<string> input;
vector<Race> races;

void parseInput() {
    int time = 0;
    int distance = 0;
    for (int i=9; i<input[0].length(); i++) {
        while (!isdigit(input[0][i]) && !isdigit(input[1][i])) i++;
        while (true) {
            if (isdigit(input[0][i])) time = time*10 + int(input[0][i])-48;
            if (isdigit(input[1][i])) distance = distance*10 + int(input[1][i])-48;
            if (!isdigit(input[0][i]) && !isdigit(input[1][i])) {
                races.push_back({time, distance});
                time = distance = 0;
                break;
            }
            i++;
        }
    }
}

int partOne() {
    int result = 1;
    for (Race race : races) {
        float descriminant = sqrt(pow(race.time, 2) - 4*race.distance);
        result *= ceil((race.time+descriminant)/2) - floor((race.time-descriminant)/2) - 1;
    }

    return result;
}

int main() {
    //ifstream file("./input.example.txt");
    ifstream file("../../inputs/2023/06.txt");

    if (file.is_open()) {
        string line;
        while (getline(file, line)) input.push_back(line);
        parseInput();

        cout << "Part 1: " << partOne() << endl;
    } else {
        cout << "Unable to read input" << endl;
    }

    return 0;
}