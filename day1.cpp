#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

void ParseInput(std::vector<int>& left, std::vector<int>& right) {
    bool parseLeft = true;

    for (std::string num; std::cin >> num;) {
        int number = std::stoi(num);

        if (parseLeft) {
            left.push_back(number);
        } else {
            right.push_back(number);
        }

        parseLeft = !parseLeft;
    }
}

int CalculateDistance(const std::vector<int>& left, const std::vector<int>& right) {
    assert(left.size() == right.size());

    int dist = 0;

    for (size_t i = 0; i < left.size(); ++i) {
        dist += abs(left[i] - right[i]);
    }

    return dist;
}

int CalculateSimilarity(const std::vector<int>& left, const std::vector<int>& right) {
    assert(left.size() == right.size());

    std::map<int, int> occurences;

    for (int num : left) {
        occurences[num] = 0;
    }

    for (int num : right) {
        if (auto search = occurences.find(num); search != occurences.end()) {
            occurences[num] += 1;
        }
    }

    int similarity = 0;

    for (int num : left) {
        similarity += num * occurences[num];
    }

    return similarity;
}

int main() {
    std::vector<int> left;
    std::vector<int> right;

    ParseInput(left, right);
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    int dist = CalculateDistance(left, right);
    int similarity = CalculateSimilarity(left, right);

    std::cout << dist << '\n';
    std::cout << similarity << '\n';
}
