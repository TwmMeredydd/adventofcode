#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct Race {
    long long time;
    long long distance;
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

long long partOne() {
    long long result = 1;
    for (Race race : races) {
        double descriminant = sqrt(pow(race.time, 2) - 4*race.distance);
        result *= ceil((race.time+descriminant)/2) - floor((race.time-descriminant)/2) - 1;
    }

    return result;
}

long long partTwo() {
    long long time = 0;
    long long distance = 0;

    for (Race race : races) {
        time = time * pow(10, int(log10(race.time))+1) + race.time;
        distance = distance * pow(10, int(log10(race.distance))+1) + race.distance;
    }

    races = {{time, distance}};
    return partOne();
}

int main() {
    //ifstream file("./input.example.txt");
    ifstream file("../../inputs/2023/06.txt");

    if (file.is_open()) {
        string line;
        while (getline(file, line)) input.push_back(line);
        parseInput();

        cout << "Part 1: " << partOne() << endl;

        cout << "Part 2: " << partTwo() << endl;
    } else {
        cout << "Unable to read input" << endl;
    }

    return 0;
}