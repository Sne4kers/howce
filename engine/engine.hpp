#pragma once

#include "basic_evaluator.hpp"

class Engine {
private:
    Evaluator evaluator_;
public:
    Engine() : evaluator_(Evaluator()) {}
    static int get_eval_of_position(const chess::BasicBoard& board) {
        Evaluator::eval(board);
    }
};