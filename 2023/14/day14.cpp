#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string> rows;

long partOne() {
    long strain = 0;

    for (int i=0; i<rows[0].length(); i++) {
        int above_rows = 0;
        for (int j=0; j<rows.size(); j++) {
            switch (rows[j][i]) {
                case 'O':
                    strain += rows.size()-above_rows;
                    above_rows++;
                    break;
                case '#':
                    above_rows = j+1;
                    break;
            }
        }
    }

    return strain;
}

int main() {
    //std::ifstream file("./input.example.txt");
    std::ifstream file("../../inputs/2023/14.txt");

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            rows.push_back(line);
        }

        std::cout << "Part One: " << partOne() << "\n";

        file.close();
    } else {
        std::cout << "Unable to read input." << "\n";
    }


    return 0;
}