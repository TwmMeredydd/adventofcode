#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <map>

using namespace std;

enum HandType {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND
};

struct Hand {
    char cards[5];
    int bid = 0;
    HandType type;
};

vector<string> input;

int partOne() {
    vector<Hand> hands;
    char priority[] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
    map<char, int> priorityMap;
    for (int i=0; i<13; i++) priorityMap[priority[i]] = i;
    
    for (string strHand : input) {
        struct Hand hand;
        for (int i = 0; i<5; i++) hand.cards[i] = strHand[i];
        for (int i=6; i<strHand.length(); i++) hand.bid = hand.bid*10 + int(strHand[i])-48;

        array<int, 13> counts;
        counts.fill(0);
        for (int i=0; i<13; i++) for (char c : hand.cards) if (c == priority[i]) counts[i] += 1;
        sort(counts.begin(), counts.end());
        switch (counts[12]) {
            case 5:
                hand.type = FIVE_OF_A_KIND;
                break;
            case 4:
                hand.type = FOUR_OF_A_KIND;
                break;
            case 3:
                hand.type = counts[11] == 2 ? FULL_HOUSE : THREE_OF_A_KIND;
                break;
            case 2:
                hand.type = counts[11] == 2 ? TWO_PAIR : ONE_PAIR;
                break;
            default:
                hand.type = HIGH_CARD;
        }

        hands.push_back(hand);
    }

    int totalWinnings = 0;
    vector<Hand> sorted;

    for (Hand h : hands) {
        int i=0;
        for (; i<sorted.size(); i++) {
            Hand h2 = sorted[i];
            if (h.type < h2.type) break;
            else if (h.type == h2.type) {
                for (int j=0; j<5; j++) {
                    if (priorityMap[h.cards[j]] < priorityMap[h2.cards[j]]) goto nextHand;
                    else if (priorityMap[h.cards[j]] > priorityMap[h2.cards[j]]) break;
                }
            }
        }
        nextHand:;
        sorted.insert(sorted.begin()+i, h);
    }

    for (int i=0; i<sorted.size(); i++) {
        totalWinnings += sorted[i].bid * (i+1);
    }

    return totalWinnings;
}

int main() {
    //ifstream file("./input.example.txt");
    ifstream file("../../inputs/2023/07.txt");

    if (file.is_open()) {
        string line;
        while (getline(file, line)) input.push_back(line);

        cout << partOne() << endl;
    } else {
        cout << "Unable to read file input" << endl;
    }

    return 0;
}