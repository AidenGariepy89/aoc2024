#include <cassert>
#include <iostream>
#include <string>
#include <vector>


typedef std::vector<int> Update;

struct Rule {
    int Before;
    int After;

    Rule(int before, int after) : Before(before), After(after) {
        assert(before != after);
    }

    bool Followed(const Update& update) const {
        int beforeIdx = -1;
        int afterIdx = -1;

        for (size_t i = 0; i < update.size(); ++i) {
            if (update[i] == Before) {
                beforeIdx = i;
            }
            if (afterIdx == -1 && update[i] == After) {
                afterIdx = i;
            }
        }

        return (beforeIdx == -1 || afterIdx == -1 || beforeIdx < afterIdx);
    }

    friend std::ostream& operator<<(std::ostream& os, const Rule& rule) {
        os << rule.Before;
        os << '|';
        os << rule.After;
        return os;
    }
};

std::ostream& operator<<(std::ostream& os, const Update& update) {
    for (size_t i = 0; i < update.size(); ++i) {
        os << update[i];
        if (i < update.size() - 1) {
            os << ',';
        }
    }
    return os;
}

bool IsValidUpdate(const std::vector<Rule>& rules, const Update& update) {
    for (const Rule& rule : rules) {
        if (!rule.Followed(update)) {
            return false;
        }
    }

    return true;
}

void CorrectUpdate(const std::vector<Rule>& rules, Update& update) {
}

void ParseInput(std::vector<Rule>& rules, std::vector<Update>& updates) {
    bool parsingRules = true;

    for (std::string line; std::getline(std::cin, line, '\n');) {
        if (line == "") {
            parsingRules = false;
            continue;
        }

        if (parsingRules) {
            size_t pos = line.find("|");
            std::string before = line.substr(0, pos);
            line.erase(0, pos + 1);

            rules.emplace_back(std::stoi(before), std::stoi(line));
        } else {
            size_t idx = updates.size();
            updates.emplace_back();
            std::string number;

            for (char c : line) {
                if (c == ',') {
                    updates[idx].push_back(std::stoi(number));
                    number.clear();
                    continue;
                }

                number += c;
            }

            updates[idx].push_back(std::stoi(number));
        }
    }
}


int main() {
    std::vector<Rule> rules;
    std::vector<Update> updates;

    ParseInput(rules, updates);

    int sum = 0;
    int sumCorrected = 0;

    for (Update& update : updates) {
        if (IsValidUpdate(rules, update)) {
            sum += update[update.size() / 2];
            sumCorrected += update[update.size() / 2];
        } else {
            CorrectUpdate(rules, update);
            sumCorrected += update[update.size() / 2];
        }
    }

    std::cout << sum << '\n';
    std::cout << sumCorrected << '\n';

    return 0;
}
