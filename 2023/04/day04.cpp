#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> input;
vector<int> matches_per_card;

void calculateMatches() {
    int num_start_x = 0;
    while (input[0][num_start_x] != ':') num_start_x++;
    num_start_x += 2;
    
    for (string row : input) {
        vector<int> winning_nums;
        int col = num_start_x;
        matches_per_card.push_back(0);
        
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
                    matches_per_card.back() += 1;
                    break;
                }
            }
        }
    }
}

int partOne() {
    int points = 0;

    for (int card : matches_per_card) {
        if (card == 0) continue;
        points += 1<<(card-1);
    }

    return points;
}

int graphCardMatches(int card = 0) {
    int total_cards = 0;
    for (int i=card+1; i<=card+matches_per_card[card] && i<matches_per_card.size(); i++) {
        total_cards += graphCardMatches(i);
    }
    return 1 + total_cards;
}

int partTwo() {
    int total_cards = 0;
    for (int i=0; i<matches_per_card.size(); i++) {
        total_cards += graphCardMatches(i);
    }
    return total_cards;
}

int main() {
    //ifstream file("./input.example.txt");
    ifstream file("../../inputs/2023/04.txt");

    string line;
    if (file.is_open()) {
        while (getline(file, line)) input.push_back(line);
        calculateMatches();

        cout << "Part 1: " << partOne() << endl;
        cout << "Part 2: " << partTwo() << endl;
    } else {
        cout << "Unable to read input file" << endl;
    }

    return 0;
}
