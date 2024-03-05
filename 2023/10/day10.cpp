#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

vector<vector<char>> pipes;

class Point {
    public:
        Point(int row, int col) {
            if (row < 0 || col < 0 || row > pipes.size() || col > pipes[0].size()) {
                return;
            }
            this->row = row;
            this->col = col;
            this->type = pipes[row][col];
        }

        Point north() {
            return Point(row-1, col);
        }

        Point east() {
            return Point(row, col+1);
        }

        Point south() {
            return Point(row+1, col);
        }

        Point west() {
            return Point(row, col-1);
        }

        vector<Point> getConnections() {
            switch (type) {
                case '|': return {north(), south()};
                case '-': return {east(), west()};
                case 'L': return {north(), east()};
                case 'J': return {north(), west()};
                case '7': return {south(), west()};
                case 'F': return {south(), east()};
                case '.': return {};
                default: return {north(), east(), south(), west()};
            }
        }

        bool operator==(Point point) {
            return col == point.col && row == point.row;
        }

        bool operator!=(Point point) {
            return !operator==(point);
        }
    
    private:
        int row, col;
        char type;
};

int partOne(Point start) {
    Point cursor = start;
    Point previous_point = start;
    int steps = 1; //Account for step we're about to take here.
    for (Point point : start.getConnections()) {
        vector<Point> connections = point.getConnections();
        if (count(connections.begin(), connections.end(), start)) {
            cursor = point;
            break;
        }
    }

    while (cursor != start) {
        for (Point point : cursor.getConnections()) {
            if (point != previous_point) {
                steps++;
                previous_point = cursor;
                cursor = point;
                break;
            } 
        }
    }

    return steps/2;
}

int main() {
    //ifstream file("./input.example.txt");
    ifstream file("../../inputs/2023/10.txt");
    
    if (file.is_open()) {
        string line;
        int row = 0;
        int start_point_raw[2] = {-1, -1};
        while (getline(file, line)) {
            vector<char> row_pipes;
            for (int col = 0; col<line.length(); col++) {
                if (line[col] == 'S') {
                    start_point_raw[0] = row;
                    start_point_raw[1] = col;
                }
                row_pipes.push_back(line[col]);
            }
            pipes.push_back(row_pipes);
            row++;
        }
        Point start = Point(start_point_raw[0], start_point_raw[1]);

        cout << "Part 1: " << partOne(start) << endl;

        file.close();
    } else {
        cout << "Unable to read input." << endl;
    }

    return 0;
}