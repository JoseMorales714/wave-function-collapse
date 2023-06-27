#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <random>

std::vector<std::vector<char>> GRID = {
    {'-', '-', '-'},
    {'-', '-', '-'},
    {'-', '-', '-'}
};

std::vector<char> left_collapse(char);
std::vector<char> up_collapse(char);
std::vector<char> find_intersection(std::vector<char>, std::vector<char>);
int get_random_num(int, int);
void update_grid(int, int, std::vector<char>);
void print_grid(); // testing purposes
void start();
void generate_grid();

int main() {

    generate_grid();

    return 0;

}

std::vector<char> left_collapse(char ch) {
    std::unordered_map<char, std::vector<char>> valid_options = {
        {'b', {'b', 'r'}},
        {'u', {'d', 'l', 'u'}},
        {'r', {'d', 'l', 'u'}},
        {'l', {'b', 'r'}},
        {'d', {'d', 'l', 'u'}}
    };

    auto it = valid_options.find(ch);
    std::vector<char> valid = it->second;
    return valid;
}

std::vector<char> up_collapse(char ch) {
    std::unordered_map<char, std::vector<char>> valid_options = {
        {'b', {'b', 'd'}},
        {'u', {'b', 'd'}},
        {'r', {'u', 'l', 'r'}},
        {'l', {'u', 'l', 'r'}},
        {'d', {'u', 'l', 'r'}}
    };

    auto it = valid_options.find(ch);
    std::vector<char> valid = it-> second;
    return valid;
}

std::vector<char> find_intersection(std::vector<char> a, std::vector<char> b) {
    std::vector<char> intersection;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(intersection));
    return intersection;
}

int get_random_num(int lower, int upper) { // inclusive of both limits
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(lower, upper);
    int random_num = distr(gen);
    return random_num;
}

void update_grid(int row, int column, std::vector<char> options) {
    int random_index = get_random_num(0, options.size());
    GRID[row][column] = options[random_index];
    return;
}

void print_grid() {

    for (int i = 0; i < GRID.size(); i++) {
        for (int j = 0; j < GRID[i].size(); j++) {
            std::cout << GRID[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

void start() {
    // generate random index for a tile to put it at the upper corner of the grid
    std::vector<char> ids = {'b', 'u', 'l', 'r', 'd'};
    int random_index = get_random_num(0, 4);
    update_grid(0, 0, ids[random_index]);
    return;
}

void generate_grid() {
    std::vector<char> options;
    for (int i = 0; i < GRID.size(); i++){
        for(int j = 0; j < GRID[i].size(); j++) {
            if (i == 0 && j == 0) {
                start(); // if first iteration, initialize
                continue;
            }

            if (i == 0) { // if its the first row, meaning no up neighbors
                options = left_collapse(GRID[i][j]);
                update_grid(i, j, options);
            }

            else {
                options = find_intersection(left_collapse(GRID[i][j]), up_collapse(GRID[i][j]));
                update_grid(i, j, options);
            }
        }
    }
}