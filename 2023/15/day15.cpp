#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <numeric>
#include <array>
#include <algorithm>

std::vector<std::string> commands = {""};

struct Lens {
    std::string label;
    int focalLength;
};

int hash(std::string raw) {
    int hashVal=0;
    for (char c : raw) {
        hashVal += int(c);
        hashVal *= 17;
        hashVal %= 256;
    }
    return hashVal;
}

int partOne() {
    return std::accumulate(commands.begin(), commands.end(), 0, [](int acc, std::string com){return acc+hash(com);});
}

long partTwo() {
    std::array<std::vector<Lens>, 256> boxes;

    for (auto command : commands) {
        if (command.back() == '-') {
            const std::string label = command.substr(0, command.length()-1);
            for (int box=0; box<boxes.size(); box++) {
                for (int i=0; i<boxes[box].size(); i++) if (boxes[box][i].label == label) {
                    boxes[box].erase(boxes[box].begin() + i);
                    goto end_command;
                }
            }
        } else {
            const std::string label = command.substr(0, command.length()-2);
            const int focalLength = int(command.back())-48;
            const int boxNum = hash(label);
            for (int i=0; i<boxes[boxNum].size(); i++) {
                if (boxes[boxNum][i].label == label) {
                    boxes[boxNum][i].focalLength = focalLength;
                    goto end_command;
                }
            }
            boxes[boxNum].push_back({label, focalLength});
        }
        end_command:;
    }

    long focusPower = 0;
    for (int i=0; i<boxes.size(); i++) {
        auto box = boxes[i];
        for (int j=0; j<box.size(); j++) {
            Lens lens = box[j];
            focusPower += (i+1) * (j+1) * box[j].focalLength;
        }
    }

    return focusPower;
 }

int main() {
    //std::ifstream file("./input.example.txt");
    std::ifstream file("../../inputs/2023/14.txt");

    if (file.is_open()) {
        std::string line;
        getline(file, line);

        for (char c : line) {
            if (c == ',') {
                commands.push_back("");
                continue;
            }
            commands.back() += c;
        }

        file.close();

        std::cout << partOne() << "\n";
        std::cout << partTwo() << "\n";
    } else {
        std::cout << "Unable to read input" << "\n";
    }

    return 0;
}