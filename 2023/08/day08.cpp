#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

struct Node {
    string left;
    string right;
};

vector<string> input;
map<string, Node> nodeMap;

int partOne() {
    for (int i=2; i<input.size(); i++) {
        string rawNode = input[i];
        nodeMap[rawNode.substr(0,3)] = {rawNode.substr(7, 3), rawNode.substr(12, 3)};
    }

    int steps = 0;
    int instruction = 0;
    string currentNode = "AAA";
    while (currentNode != "ZZZ") {
        if (instruction >= input[0].length()) instruction = 0;
        if (input[0][instruction] == 'L') currentNode = nodeMap[currentNode].left;
        else currentNode = nodeMap[currentNode].right;
        steps++;
        instruction++;
    }

    return steps;
}

int main() {
    //ifstream file("./input.example.txt");
    ifstream file("../../inputs/2023/08.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) input.push_back(line);

        cout << "Part 1: " << partOne() << endl;
    } else {
        cout << "Unable to read input" << endl;
    }
}
