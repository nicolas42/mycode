#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib> // for std::abs

int main() {
    // Open the file
    std::ifstream file("input.txt");
    if (!file) {
        std::cerr << "Error: Could not open the file\n";
        return 1;
    }

    std::vector<int> vec1, vec2;
    int num1, num2;

    // Read numbers into two vectors
    while (file >> num1 >> num2) {
        vec1.push_back(num1);
        vec2.push_back(num2);
    }

    // Close the file
    file.close();

    // Sort both vectors
    std::sort(vec1.begin(), vec1.end());
    std::sort(vec2.begin(), vec2.end());

    // Calculate the sum of absolute differences
    int sum_abs_diff = 0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        sum_abs_diff += std::abs(vec1[i] - vec2[i]);
    }

    // Output the result
    std::cout << "The sum of absolute differences is: " << sum_abs_diff << '\n';

    return 0;
}
