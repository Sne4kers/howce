// #include <chess-basic>
#include "engine.hpp"
#include <iostream>
// using namespace std;

int main() {
    auto board = chess::BasicBoard();
    auto evaluator = Evaluator();
    std::cout << board;
    std::cout << "Evaluation of current position: " << evaluator.eval(board) << std::endl;
    // std::cout << board.get_piece_info_from_id(0) << " has moves: " << board.get_possible_moves_for_piece(0).size() << std::endl;
    // std::cout << board.get_piece_info_from_id(1) << " has moves: " << board.get_possible_moves_for_piece(1).size() << std::endl;
    // std::cout << board.get_piece_info_from_id(2) << " has moves: " << board.get_possible_moves_for_piece(2).size() << std::endl;
    // std::cout << board.get_piece_info_from_id(3) << " has moves: " << board.get_possible_moves_for_piece(3).size() << std::endl;
    // std::cout << board.get_piece_info_from_id(4) << " has moves: " << board.get_possible_moves_for_piece(4).size() << std::endl;

    for (int i = 31; i >= 0; i--) {
        std::cout << board.get_piece_with_id(i).value() << " has moves: " << board.get_possible_moves_for_piece(i).size() << std::endl;
    }

    size_t id = 13;
    for (const auto& next_location : board.get_possible_moves_for_piece(id)) {
        std::cout << next_location.x_ << " " << next_location.y_ << std::endl;
    }
    chess::MoveOutcome move_outcome = board.make_move(id, chess::Point{3, 3});
    std::cout << "Evaluation of current position: " << evaluator.eval(board) << std::endl;
    std::cout << "Move was " << move_outcome.success << std::endl;
    size_t capturing_piece = 18;
    for (const auto& next_location : board.get_possible_moves_for_piece(capturing_piece)) {
        std::cout << next_location.x_ << " " << next_location.y_ << std::endl;
    }
    move_outcome = board.make_move(capturing_piece, chess::Point{3, 3});
    // std::cout << "Move was " << move_outcome.success << std::endl;
    std::cout << board;
    std::cout << "Evaluation of current position: " << evaluator.eval(board) << std::endl;

    for (int i = 31; i >= 0; i--) {
        std::cout << i << " " << board.get_piece_with_id(i).has_value() << " has moves: " << board.get_possible_moves_for_piece(i).size() << std::endl;
    }

    Engine e = Engine();
    return 0;
}