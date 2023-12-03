#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Part {
    int start_x;
    int end_x;
    int y;
    int value;
};

string *lines;
vector<Part> parts;

int ctoi(char c) {
    return int(c)-48;
}

bool isCoordInPart(int x, int y, Part part) {
    return x >= part.start_x && x < part.start_x + to_string(part.value).length() && y == part.y;
}

vector<Part> getParts() {
    vector<Part> parts;

    for (int y=0; y < lines->length(); y++) {
        string line = lines[y];
        for (int x=0; x<line.length(); x++) {
            if (isdigit(line[x])) {
                struct Part part = {x, x, y, ctoi(line[x])};
                x++;
                while(isdigit(line[x])) {
                    part.end_x = x;
                    part.value = part.value * 10 + ctoi(line[x]);
                    x++;
                }
                parts.push_back(part);
            }
        }
    }
    
    return parts;
}

int partOne() {
    int part_num_total = 0;
    const int line_length = lines[0].length();
    for (Part part : parts) {
        for (int y=part.y-1; y<=part.y+1; y++) {
            if (y<0 || y >= lines->length()) continue;
            for (int x=part.start_x-1; x<=part.end_x+1; x++) {
                if (x<0 || x>=line_length) continue;
                if (!isdigit(lines[y][x]) && lines[y][x] != '.') {
                    part_num_total += part.value;
                    goto nextpart;
                }
            }
        }
        nextpart:;
    }

    return part_num_total;
}

int partTwo() {
    int gear_ratio_total = 0;
    for (int y=0; y<lines->length(); y++) {
        string line = lines[y];
        for (int x=0; x<line.length(); x++) {
            if (line[x] == '*') {
                Part lastFound = {-1,-1,-1,-1};
                int partCount = 0;
                int ratio = 1;

                for (int y1=y-1; y1<=y+1; y1++) {
                    if (y1<0 || y1>=lines->length()) continue;
                    for (int x1=x-1; x1<=x+1; x1++) {
                        if (x1<0 || x1 >= line.length() || isCoordInPart(x1, y1, lastFound)) continue;
                        for (Part part : parts) {
                            if (isCoordInPart(x1, y1, part)) {
                                lastFound = part;
                                if(++partCount > 2) goto notGear;
                                ratio *= part.value;
                            }
                        }
                    }
                }
                if (partCount == 2) gear_ratio_total += ratio;
            }
            notGear:;
        }
    }

    return gear_ratio_total;
}

int main() {
    //ifstream file("./input.example.txt");
    ifstream file("../../inputs/2023/03.txt");

    string line;
    int count = 0;
    if (file.is_open()) {
        while (getline(file, line)) count++;
        file.clear();
        file.seekg(0, ios::beg);
        
        lines = new string[count];
        for (int i=0; i<count; i++) {
            getline(file, line);
            lines[i] = line;
        }

        parts = getParts();

        cout << "Part 1: " << partOne() << endl;
        cout << "Part 2: " << partTwo() << endl;

        delete [] lines;
    } else {
        cout << "Unable to read input file" << endl;
    }

    return 0;
}
