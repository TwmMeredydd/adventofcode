#include <iostream>
#include <fstream>
#include <list>

using namespace std;

int partOne(string lines[]) {
    int part_num_total = 0;
    for (int l=0; l < lines->length(); l++) {
        string line = lines[l];
        for (int i=0; i<line.length(); i++) {
            if (isdigit(line[i])) {
                int num_from_pos;
                int num_to_pos;
                bool valid = false;
                int part_num = 0;
                num_from_pos = i;
                while (isdigit(line[i])) {
                    num_to_pos = i;
                    part_num = part_num * 10 + int(line[i])-48;
                    i++;
                }
            
                for (int j=l-1; j<l+2; j++) {
                    if (j<0 || j>=lines->length()) continue;
                    for (int c=num_from_pos-1; c<num_to_pos+2; c++) {
                        if (c<0 || c>=line.length()) continue;
                        if (!isdigit(lines[j][c]) && lines[j][c] != '.') {
                            valid = true;
                            goto nextdigit;
                        }
                    } 
                }
            
                nextdigit:
                if (valid) {
                    part_num_total += part_num;
                }
            }
        }
    }

    return part_num_total;
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
        
        string lines[count];
        for (int i=0; i<count; i++) {
            getline(file, line);
            lines[i] = line;
        }

        cout << "Part 1: " << partOne(lines) << endl;
    } else {
        cout << "Unable to read input file" << endl;
    }

    return 0;
}
