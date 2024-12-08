#include <iostream>
#include <string>
#include <vector>

struct MultCommand {
    int X;
    int Y;

    MultCommand(int x, int y) : X(x), Y(y) {}

    int Calc() const {
        return X * Y;
    }
};

std::vector<MultCommand> ParseInput() {
    std::string input;

    for (std::string line; std::getline(std::cin, line, '\n');) {
        input += line;
    }

    enum class ParseState {
        Searching,
        M,
        U,
        L,
        ParsingX,
        ParsingY,

        D,
        O,
        N,
        Apostrophe,
        T,
        OpenParen,
    };

    ParseState state = ParseState::Searching;
    std::string number;
    int x;
    bool enabled = true;
    bool cmdIsDo = true;

    std::vector<MultCommand> commands;

    for (size_t i = 0; i < input.size(); ++i) {
        switch (state) {
            case ParseState::Searching: {
                if (input[i] == 'd') {
                    state = ParseState::D;
                }
                if (enabled && input[i] == 'm') {
                    state = ParseState::M;
                }
                break;
            }
            case ParseState::M: {
                if (input[i] != 'u') {
                    state = ParseState::Searching;
                } else {
                    state = ParseState::U;
                }
                break;
            }
            case ParseState::U: {
                if (input[i] != 'l') {
                    state = ParseState::Searching;
                } else {
                    state = ParseState::L;
                }
                break;
            }
            case ParseState::L: {
                if (input[i] != '(') {
                    state = ParseState::Searching;
                } else {
                    state = ParseState::ParsingX;
                }
                break;
            }
            case ParseState::ParsingX:
            case ParseState::ParsingY: {
                if (input[i] >= '0' && input[i] <= '9') {
                    number += input[i];
                    // good
                    break;
                } else if (input[i] == ',') {
                    if (state == ParseState::ParsingX) {
                        x = std::stoi(number);
                        number.clear();
                        state = ParseState::ParsingY;

                        // good
                        break;
                    }
                } else if (input[i] == ')') {
                    if (state == ParseState::ParsingY) {
                        commands.emplace_back(x, std::stoi(number));
                    }
                }
                // Stop parsing and go to searching.
                // Could be because of bad, or because done parsing
                // command.
                number.clear();
                state = ParseState::Searching;
                break;
            }
            case ParseState::D: {
                if (input[i] != 'o') {
                    state = ParseState::Searching;
                } else {
                    state = ParseState::O;
                }
                break;
            }
            case ParseState::O: {
                if (input[i] == 'n') {
                    state = ParseState::N;
                    cmdIsDo = false;
                } else if (input[i] == '(') {
                    state = ParseState::OpenParen;
                    cmdIsDo = true;
                } else {
                    state = ParseState::Searching;
                }
                break;
            }
            case ParseState::N: {
                if (input[i] != '\'') {
                    state = ParseState::Searching;
                } else {
                    state = ParseState::Apostrophe;
                }
                break;
            }
            case ParseState::Apostrophe: {
                if (input[i] != 't') {
                    state = ParseState::Searching;
                } else {
                    state = ParseState::T;
                }
                break;
            }
            case ParseState::T: {
                if (input[i] != '(') {
                    state = ParseState::Searching;
                } else {
                    state = ParseState::OpenParen;
                }
                break;
            }
            case ParseState::OpenParen: {
                if (input[i] == ')') {
                    enabled = cmdIsDo;
                }
                state = ParseState::Searching;
                break;
            }
        }
    }

    return commands;
}

int main() {
    std::vector<MultCommand> commands = ParseInput();

    int result = 0;

    for (MultCommand& cmd : commands) {
        result += cmd.Calc();
    }

    std::cout << result << '\n';
}
