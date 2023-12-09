#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <map>

using namespace std;

typedef vector<vector<long long>> transformMap;

static vector<string> input;
static vector<transformMap> maps;

struct SeedRange {
    long long start;
    long long end;
};

bool inRange(long long num, long long start, long long length) {
    return num >= start && num < (start + length);
}

long long vectorMin(vector<long long> values) {
    long long minVal = values[0];
    for (long long val : values) if (val < minVal) minVal = val;
    return minVal;
}

vector<long long> parseNumbers(string raw) {
    vector<long long> numbers;
    for (int i=0; i<raw.length(); i++) {
        numbers.push_back(0);
        while (!isdigit(raw[i])) i++;
        while (isdigit(raw[i])) {
            numbers.back() = numbers.back()*10 + int(raw[i])-48;
            i++;
        } 
    }

    return numbers;
}

void generateMaps() {
    int row = 3;
    
    for (int map=0; map<7; map++) {
        maps.push_back({});
        while(input[row] != "" && row < input.size()) {
            maps.back().push_back(parseNumbers(input[row]));
            row++;
        }
        row+=2;
    }
}

long long partOne() {
    vector<long long> cursors = parseNumbers(input[0]);

    for (int cursor_i=0; cursor_i<cursors.size(); cursor_i++) {
        for (transformMap map : maps) {
            long long cursor = cursors[cursor_i];
            for (vector<long long> node : map) {
                if (cursor >= node[1] && cursor < node[1] + node[2]) {
                    cursors[cursor_i] = node[0] + cursor - node[1];
                    break;
                }
            }
        }
    }

    return vectorMin(cursors);
}

long long splitAndTransform(SeedRange seedRange, int mapStartI) {
    vector<long long> endings;
    SeedRange backup = seedRange;

    for (int i = mapStartI; i < maps.size(); i++) {
        for (vector<long long> transform : maps[i]) {
            bool start_in_range = inRange(seedRange.start, transform[1], transform[2]);
            bool end_in_range = inRange(seedRange.end, transform[1], transform[2]);
            if (start_in_range || end_in_range) {
                long long test = 0;
                if (start_in_range && !end_in_range) {
                    test = splitAndTransform({transform[1]+transform[2], seedRange.end}, i);
                    endings.push_back(test);
                    seedRange.end = transform[1] + transform[2]-1;
                } else if (end_in_range && !start_in_range) {
                    test = splitAndTransform({seedRange.start, transform[1]-1}, i);
                    endings.push_back(test);
                    seedRange.start = transform[1];
                }
                seedRange.start += transform[0] - transform[1];
                if (start_in_range && end_in_range) test = seedRange.start;
                seedRange.end += transform[0] - transform[1];
                break;
            } else if (seedRange.start < transform[1] && seedRange.end > transform[1] + transform[2]-1) {
                endings.push_back(splitAndTransform({seedRange.start, transform[1]-1}, i));
                endings.push_back(splitAndTransform({transform[1]+transform[2], seedRange.end}, i));
                seedRange.start = transform[0];
                seedRange.end = transform[0] + transform[2]-1;
                break;
            }
            
        } 
    }

    endings.push_back(seedRange.start);
    return vectorMin(endings);
}

long long partTwo() {
    vector<long long> raw_seeds = parseNumbers(input[0]);
    vector<SeedRange> seedRanges;

    for (int i=0; i<raw_seeds.size(); i+=2) {
        seedRanges.push_back({raw_seeds[i], raw_seeds[i] + raw_seeds[i+1]-1});
    }

    vector<long long> processedSeeds;

    for (SeedRange seedRange : seedRanges) processedSeeds.push_back(splitAndTransform(seedRange, 0));

    return vectorMin(processedSeeds);
}

int main() {
    //ifstream file("./input.example.txt");
    ifstream file("../../inputs/2023/05.txt");

    string line;
    if (file.is_open()) {
        while (getline(file, line)) input.push_back(line); 

        generateMaps();

        cout << partOne() << endl;
        cout << partTwo() << endl;
    }

    return 0;
}