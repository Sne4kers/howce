// #include <chess-basic>
#include "basic_board.hpp"
#include <iostream>
// using namespace std;

int main() {
    auto board = chess::BasicBoard();
    std::cout << board;
    // std::cout << board.get_piece_info_from_id(0) << " has moves: " << board.get_possible_moves_for_piece(0).size() << std::endl;
    // std::cout << board.get_piece_info_from_id(1) << " has moves: " << board.get_possible_moves_for_piece(1).size() << std::endl;
    // std::cout << board.get_piece_info_from_id(2) << " has moves: " << board.get_possible_moves_for_piece(2).size() << std::endl;
    // std::cout << board.get_piece_info_from_id(3) << " has moves: " << board.get_possible_moves_for_piece(3).size() << std::endl;
    // std::cout << board.get_piece_info_from_id(4) << " has moves: " << board.get_possible_moves_for_piece(4).size() << std::endl;

    for (int i = 31; i >= 0; i--) {
        std::cout << board.get_piece_info_from_id(i) << " has moves: " << board.get_possible_moves_for_piece(i).size() << std::endl;
    }
    return 0;
}