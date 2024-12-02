#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Report {

    std::vector<int> m_Levels;

public:

    Report() = default;
    Report(const std::vector<int>& levels) : m_Levels(levels) {}

    bool IsSafe() const {
        bool safe = IsSafeForwards() || IsSafeBackwards();

        if (!safe) {
            for (size_t i = 0; i < m_Levels.size(); ++i) {
                safe = IsSafeWithFault(i);
                if (safe) break;
            }
        }

        return safe;
    }

private:

    bool IsSafeForwards() const {
        int direction = 0;

        for (size_t i = 1; i < m_Levels.size(); ++i) {
            if (m_Levels[i] == m_Levels[i - 1]) {
                // return IsSafeWithFault(i, true);
                return false;
            }

            int dir;
            if (m_Levels[i] > m_Levels[i - 1]) {
                dir = 1;
            } else {
                dir = -1;
            }

            if (direction != 0) {
                if (dir != direction) {
                    // return IsSafeWithFault(i, true);
                    return false;
                }
            } else {
                direction = dir;
            }

            if (abs(m_Levels[i] - m_Levels[i - 1]) > 3) {
                // return IsSafeWithFault(i, true);
                return false;
            }
        }

        return true;
    }

    bool IsSafeBackwards() const {
        int direction = 0;

        for (size_t i = m_Levels.size() - 2; i >= 0; --i) {
            if (m_Levels[i] == m_Levels[i + 1]) {
                // return IsSafeWithFault(i, false);
                return false;
            }

            int dir;
            if (m_Levels[i] > m_Levels[i + 1]) {
                dir = 1;
            } else {
                dir = -1;
            }

            if (direction != 0) {
                if (dir != direction) {
                    // return IsSafeWithFault(i, false);
                    return false;
                }
            } else {
                direction = dir;
            }

            if (abs(m_Levels[i] - m_Levels[i + 1]) > 3) {
                // return IsSafeWithFault(i, false);
                return false;
            }
        }

        return true;
    }

    bool IsSafeWithFault(size_t faultyIdx) const {
        Report report;

        for (size_t i = 0; i < m_Levels.size(); ++i) {
            if (i != faultyIdx) {
                report.m_Levels.push_back(m_Levels[i]);
            }
        }

        return report.IsSafeForwards() || report.IsSafeBackwards();
    }
};


int main() {
    std::vector<Report> reports;

    std::string line;
    std::string num;

    while (std::getline(std::cin, line, '\n')) {
        std::stringstream ss(line);
        std::vector<int> levels;
        while (ss >> num) {
            levels.push_back(std::stoi(num));
        }

        reports.emplace_back(levels);
    }

    int safeReports = 0;

    for (const Report& report : reports) {
        if (report.IsSafe()) {
            ++safeReports;
        }
    }

    std::cout << safeReports << '\n';
}
