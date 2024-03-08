#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Galaxy {
    long x, y;
};

vector<Galaxy> rawGalaxies;
set<int> empty_rows;
set<int> empty_cols;

int partOne() {
    vector<Galaxy> galaxies;
    copy(rawGalaxies.begin(), rawGalaxies.end(), back_inserter(galaxies));

    int total_steps = 0;

    for (int i=0; i<galaxies.size(); i++) {
        Galaxy* galaxy = &galaxies[i];
        
        int xOffset = 0;
        for (int col : empty_cols) if (galaxy->x > col) xOffset++;
        galaxy->x += xOffset;
        
        int yOffset = 0;
        for (int row : empty_rows) if (galaxy->y > row) yOffset++;
        galaxy->y += yOffset;
    }

    for (int i=0; i<galaxies.size(); i++) {
        Galaxy galaxy = galaxies[i];
        for (int j=i+1; j<galaxies.size(); j++) {
            Galaxy galaxy2 = galaxies[j];
            total_steps += abs(galaxy2.x - galaxy.x) + abs(galaxy2.y - galaxy.y);
        }
    }

    return total_steps;
}

long partTwo() {
    vector<Galaxy> galaxies;
    copy(rawGalaxies.begin(), rawGalaxies.end(), back_inserter(galaxies));

    long total_steps = 0;

    for (int i=0; i<galaxies.size(); i++) {
        Galaxy* galaxy = &galaxies[i];
        
        int xOffset = 0;
        for (int col : empty_cols) if (galaxy->x > col) xOffset++;
        galaxy->x += xOffset*999999;
        
        int yOffset = 0;
        for (int row : empty_rows) if (galaxy->y > row) yOffset++;
        galaxy->y += yOffset*999999;
    }

    for (int i=0; i<galaxies.size(); i++) {
        Galaxy galaxy = galaxies[i];
        for (int j=i+1; j<galaxies.size(); j++) {
            Galaxy galaxy2 = galaxies[j];
            total_steps += abs(galaxy2.x - galaxy.x) + abs(galaxy2.y - galaxy.y);
        }
    }

    return total_steps;
}

int main() {
    //ifstream file("./input.example.txt");
    ifstream file("../../inputs/2023/11.txt");

    if (file.is_open()) {
        string line;
        int row = 0;
        while (getline(file, line)) {
            bool empty = true;
            set<int> dots;
            for (int col=0; col<line.length(); col++)
                if (line[col] == '#') {
                    rawGalaxies.push_back({col, row});
                    empty = false;
                } else {
                    dots.insert(col);
                }
            
            if (empty) empty_rows.insert(row);
            
            if (empty_cols.empty()) {
                copy(dots.begin(), dots.end(), inserter(empty_cols, empty_cols.begin()));
            } else {
                set<int> intersect;
                set_intersection(dots.begin(), dots.end(), empty_cols.begin(), empty_cols.end(), inserter(intersect, intersect.begin()));
                empty_cols = intersect;           
            }

            row++;
        }

        cout << "Part 1: " << partOne() << endl;
        cout << "Part 2: " << partTwo() << endl;

    } else {
        cout << "Unable to read input" << endl;
    }
    return 0;
}