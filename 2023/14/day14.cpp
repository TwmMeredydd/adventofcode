#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>

std::vector<std::string> commands = {""};

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
    } else {
        std::cout << "Unable to read input" << "\n";
    }

    return 0;
}