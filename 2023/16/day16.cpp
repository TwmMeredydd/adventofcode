#include <fstream>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

std::vector<std::vector<char>> map;

enum Direction {
    NORTH = 0,
    SOUTH = 1,
    EAST = 2,
    WEST = 3
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
    } else {
        std::cout << "Unable to read input\n";
    }

    return 0;
}