#include <fstream>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <set>

std::vector<std::vector<char>> map;

enum Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

class Beam {
    public:
        int x, y;
        Direction direction;

        Beam(int x, int y, Direction direction) {
            this->x = x;
            this->y = y;
            this->direction = direction;
        }

        friend bool operator==(const Beam &lhs, const Beam &rhs) {
            return lhs.x==rhs.x && lhs.y==rhs.y && lhs.direction == rhs.direction;
        }

        std::string toString() {
            return std::to_string(this->x) + "-" + std::to_string(this->y) + "-" + std::to_string(this->direction);
        } 

};

std::vector<Beam> processBeam(Beam beam) {
    switch (map[beam.y][beam.x]) {
        case '/':
            switch (beam.direction) {
                case NORTH:
                    return {{beam.x+1, beam.y, EAST}};
                    break;
                case EAST:
                    return {{beam.x, beam.y-1, NORTH}};
                    break;
                case SOUTH:
                    return {{beam.x-1, beam.y, WEST}};
                    break;
                case WEST:
                    return {{beam.x, beam.y+1, SOUTH}};
                    break;
            }
            break;
        case '\\':
            switch (beam.direction) {
                case NORTH:
                    return {{beam.x-1, beam.y, WEST}};
                    break;
                case EAST:
                    return {{beam.x, beam.y+1, SOUTH}};
                    break;
                case SOUTH:
                    return {{beam.x+1, beam.y, EAST}};
                    break;
                case WEST:
                    return {{beam.x, beam.y-1, NORTH}};
                    break;
            }
            break;
        case '|':
            switch (beam.direction) {
                case EAST:
                case WEST:
                    return {{beam.x, beam.y+1, SOUTH}, {beam.x, beam.y-1, NORTH}};
                    break;
                case NORTH:
                    return {{beam.x, beam.y-1, NORTH}};
                    break;
                case SOUTH:
                    return {{beam.x, beam.y+1, SOUTH}};
                    break;
            }
            break;
        case '-':
            switch (beam.direction) {
                case NORTH:
                case SOUTH:
                    return {{beam.x-1, beam.y, WEST}, {beam.x+1, beam.y, EAST}};
                    break;
                case EAST:
                    return {{beam.x+1, beam.y, EAST}};
                    break;
                case WEST:
                    return {{beam.x-1, beam.y, WEST}};
                    break;
            }
            break;
        case '.':
            switch (beam.direction) {
                case NORTH:
                    return {{beam.x, beam.y-1, NORTH}};
                    break;
                case EAST:
                    return {{beam.x+1, beam.y, EAST}};
                    break;
                case SOUTH:
                    return {{beam.x, beam.y+1, SOUTH}};
                    break;
                case WEST:
                    return {{beam.x-1, beam.y, WEST}};
                    break;
            }
            break;
    }
    return {{-1, -1, NORTH}};
}

bool isOnMap(Beam beam) {
    return beam.x >= 0 && beam.x < map[0].size() && beam.y >= 0 && beam.y < map.size();
}

int partOne() {
    std::queue<Beam> cursors;
    std::vector<Beam> history;
    cursors.push({0, 0, EAST});

    while (!cursors.empty()) {
        Beam cursor = cursors.front();
        cursors.pop();
        history.push_back(cursor);

        for (Beam beam : processBeam(cursor)) {
            if (isOnMap(beam) && std::find(history.begin(), history.end(), beam) == history.end()) cursors.push(beam);
        }
    }

    int energized = 0;

    std::cout << "\n";

    std::vector<std::string> printout(map.size(), std::string().append(map[0].size(), '.'));

    for (Beam ghost : history) {
        char* c = &printout[ghost.y][ghost.x];
        if (*c == '.') {
            *c = '#';
            energized++;
        }
    }

    for (auto s : printout) {
        std::cout << s << "\n";
    }

    return energized;
}

// Keeps fucking Seg-faulting

// std::unordered_map<std::string, std::set<std::string>> recurseBeamCache;
// std::set<std::string> recurseBeam(Beam beam, std::set<std::string> &beamMap) {
//     if (recurseBeamCache.find(beam.toString()) != recurseBeamCache.end()) return recurseBeamCache[beam.toString()];

//     std::set<std::string> history = {};
//     std::vector<Beam> targets = {beam};

//     while (targets.size() == 1) {
//         Beam target = targets[0];
//         if (!isOnMap(target)) break;
//         history.insert(target.toString());
//         targets = processBeam(targets[0]);
//     }

//     beamMap.insert(history.begin(), history.end());

//     for (Beam b : targets) {
//         std::set<std::string> h = recurseBeam(b, beamMap);
//         history.merge(h);
//     }

//     recurseBeamCache[beam.toString()] = history;
//     return history;
// }

// int partTwo() {

//     int energized = 0;

//     auto test = [&energized](Beam b) {
//         std::set<std::string> beamMap;
//         std::set<std::string> history = recurseBeam(b, beamMap);
//         int e = beamMap.size();
//         if (e > energized) energized = e;
//     };

//     for (int y=0; y<map.size(); y++) {
//         test({0, y, EAST});
//         test({map[0].size()-1, y, WEST});
//     }
//     for (int x=0; x<map[0].size(); x++) {
//         test({x, 0, SOUTH});
//         test({x, map.size()-1, NORTH});
//     }

//     return energized;
// }


// Takes tooooo fukin' long.
int energize(Beam start) {
    int energized = 0;

    std::queue<Beam> cursors;
    std::vector<Beam> history;
    cursors.push(start);

    while (!cursors.empty()) {
        Beam cursor = cursors.front();
        cursors.pop();
        history.push_back(cursor);

        for (Beam beam : processBeam(cursor)) {
            if (isOnMap(beam) && std::find(history.begin(), history.end(), beam) == history.end()) cursors.push(beam);
        }
    }

    std::vector<std::string> printout(map.size(), std::string().append(map[0].size(), '.'));

    for (Beam ghost : history) {
        char* c = &printout[ghost.y][ghost.x];
        if (*c == '.') {
            *c = '#';
            energized++;
        }
    }

    return energized;
}

int partTwo() {
    int energized = 0;

    auto test = [&energized](Beam b) {
        int e = energize(b);
        if (e > energized) energized = e;
    };

    for (int y=0; y<map.size(); y++) {
        test({0, y, EAST});
        test({map[0].size()-1, y, WEST});
    }
    for (int x=0; x<map[0].size(); x++) {
        test({x, 0, SOUTH});
        test({x, map.size()-1, NORTH});
    }

    return energized;
}

int main() {
    //std::ifstream file("./input.example.txt");
    std::ifstream file("../../inputs/2023/16.txt");

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            map.push_back({});
            for (char c : line) map.back().push_back(c);
        }
        
        std::cout << "Part 1: " << partOne() << "\n";
        std::cout << "Part 2: " << partTwo() << "\n";
    } else {
        std::cout << "Unable to read input\n";
    }

    return 0;
}