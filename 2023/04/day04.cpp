#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> input;

int partOne() {
    int total_points = 0;
    int num_start_x = 0;
    while (input[0][num_start_x] != ':') num_start_x++;
    num_start_x += 2;

    for (string row : input) {
        vector<int> winning_nums;
        float points = 0.5;

        int col = num_start_x;
        
        for (; row[col] != '|'; col++) {
            while (!isdigit(row[col])) col++;
            if (row[col] == '|') break;
            winning_nums.push_back(0);
            while (isdigit(row[col])) {
                winning_nums.back() *= 10;
                winning_nums.back() += int(row[col]) - 48;
                col++;
            }
        }

        for (; col < row.length(); col++) {
            int num = 0;
            while(!isdigit(row[col])) col++;
            while(isdigit(row[col])) {
                num = num*10 + int(row[col])-48;
                col++;
            }
            for (int winning_num : winning_nums) {
                if (winning_num == num) {
                    points *= 2;
                    break;
                }
            }
        }

        total_points += int(points);
    }

    return total_points;
}

int main() {
    //ifstream file("./input.example.txt");
    ifstream file("../../inputs/2023/04.txt");

    string line;
    if (file.is_open()) {
        while (getline(file, line)) input.push_back(line);

        cout << "Part 1: " << partOne() << endl;
    } else {
        cout << "Unable to read input file" << endl;
    }

    return 0;
}
