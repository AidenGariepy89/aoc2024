#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> GetInput() {
    std::vector<std::string> output;

    for (std::string line; std::getline(std::cin, line, '\n');) {
        output.push_back(line);
    }

    return output;
}

std::array<int, 8> ColumnDirs{ 1, 1, 0, -1, -1, -1, 0, 1 }; // right, down-right, down, down-left, etc.
std::array<int, 8> RowDirs{ 0, -1, -1, -1, 0, 1, 1, 1 }; // right, down-right, down, down-left, etc.

int GetMatches(const std::vector<std::string>& puzzle, const std::string& word, size_t r, size_t c) {
    int matches = 0;

    for (size_t dir = 0; dir < ColumnDirs.size(); ++dir) {
        int dc = ColumnDirs[dir];
        int dr = RowDirs[dir];
        bool found = true;

        for (size_t i = 1; i < word.size(); ++i) {
            int cc = c + dc * i;
            int rr = r + dr * i;

            if (cc < 0 || rr < 0) {
                found = false;
                break;
            }
            if (rr >= puzzle.size()) {
                found = false;
                break;
            }
            if (cc >= puzzle[rr].length()) {
                found = false;
                break;
            }
            if (puzzle[rr][cc] != word[i]) {
                found = false;
                break;
            }
        }

        if (found) {
            ++matches;
        }
    }

    return matches;
}

int GetOccurences(const std::vector<std::string>& puzzle, const std::string& word) {
    assert(word.length() > 0);

    int occurences = 0;

    for (size_t r = 0; r < puzzle.size(); ++r) {
        for (size_t c = 0; c < puzzle[r].length(); ++c) {
            if (puzzle[r][c] == word[0]) {
                occurences += GetMatches(puzzle, word, r, c);
            }
        }
    }

    return occurences;
}

std::array<int, 4> DiagonalColumn{ 1, -1, 1, -1 }; // down-right, up-left, up-right, down-left
std::array<int, 4> DiagonalRow{ -1, 1, 1, -1 };

bool IsXmas(const std::vector<std::string>& puzzle, size_t r, size_t c) {
    int mCount = 0;
    int sCount = 0;
    char lastFound = 0;

    for (size_t dir = 0; dir < DiagonalRow.size(); ++dir) {
        int rr = r + DiagonalRow[dir];
        int cc = c + DiagonalColumn[dir];

        if (rr < 0 || cc < 0) {
            return false;
        }
        if (rr >= puzzle.size()) {
            return false;
        }
        if (cc >= puzzle[rr].length()) {
            return false;
        }

        if (puzzle[rr][cc] == 'M') {
            if (dir % 2 != 0 && lastFound == 'M') {
                return false;
            }

            ++mCount;
            lastFound = 'M';
            continue;
        }
        if (puzzle[rr][cc] == 'S') {
            if (dir % 2 != 0 && lastFound == 'S') {
                return false;
            }

            ++sCount;
            lastFound = 'S';
            continue;
        }
        return false;
    }

    return mCount == 2 && sCount == 2;
}

int GetXmasOccurences(const std::vector<std::string>& puzzle) {
    int occurences = 0;

    for (size_t r = 0; r < puzzle.size(); ++r) {
        for (size_t c = 0; c < puzzle.size(); ++c) {
            if (puzzle[r][c] == 'A') {
                occurences += IsXmas(puzzle, r, c);
            }
        }
    }

    return occurences;
}

int main() {
    std::vector<std::string> puzzle = GetInput();

    int occurences = GetOccurences(puzzle, "XMAS");
    int xmas = GetXmasOccurences(puzzle);

    std::cout << occurences << '\n';
    std::cout << xmas << '\n';
}
