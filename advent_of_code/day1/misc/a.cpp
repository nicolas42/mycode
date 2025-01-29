#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    std::ifstream file("day1_input.csv");
    std::vector<std::vector<int>> arrays;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<int> row;
        size_t pos = 0;
        while ((pos = line.find(',')) != std::string::npos) {
            row.push_back(std::stoi(line.substr(0, pos)));
            line.erase(0, pos + 1);
        }
        row.push_back(std::stoi(line));
        arrays.push_back(row);
    }

    int difference = 0;
    for (const auto& row : arrays) {
        std::vector<int> col0 = row, col1 = row;
        std::sort(col0.begin(), col0.end());
        std::sort(col1.begin(), col1.end());
        difference += std::abs(col0[0] - col1[1]);
    }

    int similarity = 0;
    for (const auto& row : arrays) {
        auto count = std::count(row.begin(), row.end(), row[1]);
        similarity += row[0] * count;
    }

    std::count << "The answer to part 1 is " << difference << "\n";
    std::count << "The answer to part 2 is " << similarity << "\n";
}
