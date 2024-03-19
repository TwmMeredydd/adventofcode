#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>

std::vector<std::vector<std::string>> patterns = {{}};

int partOne() {
    int summary = 0;

    for (std::vector<std::string> pattern : patterns) {
        for (int line=1; line<pattern.size(); line++) {    
            bool v_reflection = true;
            for (int i=0; i<=pattern.size()-line-1 && i<line; i++) {
                if (pattern[line-i-1] != pattern[line+i]) {
                    v_reflection=false;
                    break;
                }
            }

            if (v_reflection)
                summary += 100 * line;
        }

        for (int h_symmetry=1; h_symmetry<pattern[0].length(); h_symmetry++) {
            bool h_reflection = true;
            for (int i=0; i<=pattern[0].length()-h_symmetry-1 && i<h_symmetry; i++) {
                for (int j=0; j<pattern.size(); j++) 
                    if (pattern[j][h_symmetry-i-1] != pattern[j][h_symmetry+i]) {
                        h_reflection = false;
                        goto finish_h_check;
                    }
            }
            finish_h_check:;

            if (h_reflection)
                summary += h_symmetry;
        }
    }

    return summary;
}

int partTwo() {
    int summary = 0;

    for (std::vector<std::string> pattern : patterns) {
        bool smudge_fixed = false;
        for (int v_symmetry=1; v_symmetry<pattern.size(); v_symmetry++) {
            int differences = 0;
            char* diff_point;
            for (int i=0; i<=pattern.size()-v_symmetry-1 && i<v_symmetry; i++) {
                for (int j=0; j<pattern[0].length(); j++) 
                    if (pattern[v_symmetry-i-1][j] != pattern[v_symmetry+i][j]) {
                        if (differences) goto finish_v_check;
                        differences++;
                        diff_point = &pattern[v_symmetry-i-1][j];
                    }
            }

            if (differences) {
                (*diff_point) = ((*diff_point) == '.') ? '#' : '.';
                smudge_fixed = true;
                v_symmetry--;
                continue;
            } else if (smudge_fixed) {
                summary += 100 * v_symmetry;
                goto next_pattern;
            }

            finish_v_check:;
        }

        for (int h_symmetry=1; h_symmetry<pattern[0].length(); h_symmetry++) {
            int differences = 0;
            char* diff_point;
            for (int i=0; i<=pattern[0].length()-h_symmetry-1 && i<h_symmetry; i++) {
                for (int j=0; j<pattern.size(); j++) 
                    if (pattern[j][h_symmetry-i-1] != pattern[j][h_symmetry+i]) {
                        if (differences) goto finish_h_check;
                        differences++;
                        diff_point = &pattern[j][h_symmetry-i-1];
                    }
            }

            if (differences) {
                (*diff_point) = ((*diff_point) == '.') ? '#' : '.';
                smudge_fixed = true;
                h_symmetry--;
                continue;
            } else if (smudge_fixed) {
                summary += h_symmetry;
                goto next_pattern;
            }

            finish_h_check:;
        }
        next_pattern:;
    }

    return summary;
}

int main() {
    //std::ifstream file("./input.example.txt");
    std::ifstream file("../../inputs/2023/13.txt");

    if (file.is_open()) {
        std::string line;
        while(std::getline(file, line)) {
            if (line.empty()) {
                patterns.push_back({});
                continue;
            }
            patterns.back().push_back(line);
        }

        std::cout << "Part One: " << partOne() << "\n";
        std::cout << "Part Two: " << partTwo() << "\n";
    } else {
        std::cout << "Unable to read input\n";
    }
    return 0;
}
