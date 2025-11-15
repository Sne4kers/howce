#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "engine.hpp"
// #include "engine/board_v1.0/basic_board.hpp"

class CLI {
private:
    static std::vector<std::string> split(std::string input) {
        auto result = std::vector<std::string>();
        
        size_t next_separator_position = input.find(' ');
        while (next_separator_position != std::string::npos) {
            result.emplace_back(input.substr(0, next_separator_position));
            input = input.substr(next_separator_position + 1);
            next_separator_position = input.find(' ');
        }

        result.emplace_back(input);
        return result;
    }

    void new_game() {
        board_ = chess::BasicBoard();
        engine_ = Engine();

        std::cout << "Initialized new game\n";
        std::cout << board_;
    }

    void eval() {
        int score = engine_.get_eval_of_position(board_);
        std::cout << "The current board was scored at " << score << '\n';
    }

    void invalidate_input(const std::string& extra_info = "") {
        std::cout << "Bad input\n" << extra_info;
    }

    void sugest_fixing_no_extra_arguments(const std::string& command_name) {
        invalidate_input(command_name + " command doesn't have any additional arguments");
    }

    void verify_command(const std::vector<std::string>& arguments) {
        if (arguments[0] == "newgame") {
            if (arguments.size() != 1) {
                sugest_fixing_no_extra_arguments("newgame");
            } else {
                new_game();
            }
        } else if (arguments[0] == "eval") {
            if (arguments.size() != 1) {
                sugest_fixing_no_extra_arguments("eval");
            } else {
                eval();
            }
        } else {
            invalidate_input("no such command found");
        }
    }

    chess::BasicBoard board_;
    Engine engine_;
public:
    CLI() {}
    [[ noreturn ]] void main_cli_loop() {
        std::cout << "Welcome to Yehor's chess engine" << std::endl;

        while (true) {
            std::string user_input;
            std::getline(std::cin, user_input);
            auto arguments = split(user_input);

            if (arguments.size() == 0) {
                invalidate_input();
            }

            verify_command(arguments);
        }
        // get_board
        // make move
        // get eval
        // let the engine run for a limited amount of depth
    }
};