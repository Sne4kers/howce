#pragma once

#include "engine/board_v1.0/basic_board.hpp"
#include <iostream>

consteval std::array<std::array<int, 8>, 8> rotate_by_180_matrix(const std::array<std::array<int, 8>, 8>& matrix) {
    std::array<std::array<int, 8>, 8> to_return{}; 

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            to_return[7 - i][7 - j] = matrix[i][j];
        }
    }
    return to_return;
}

consteval std::array<std::array<int, 8>, 8> negate(const std::array<std::array<int, 8>, 8>& matrix) {
    std::array<std::array<int, 8>, 8> to_return{}; 

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            to_return[i][j] = -matrix[i][j];
        }
    }
    return to_return;
}

class Evaluator {
private:
    // Took basic tables from 
    // https://www.chessprogramming.org/Simplified_Evaluation_Function
    // TODO replace with something makign more sense?
    inline static constexpr std::array<std::array<int, 8>, 8> pawn_eval_matrix = {{
        {{ 0,  0,  0,  0,  0,  0,  0,  0}},
        {{ 50, 50, 50, 50, 50, 50, 50, 50}},
        {{ 10, 10, 20, 30, 30, 20, 10, 10}},
        {{ 5,  5, 10, 25, 25, 10,  5,  5}},
        {{ 0,  0,  0, 20, 20,  0,  0,  0}},
        {{ 5, -5,-10,  0,  0,-10, -5,  5}},
        {{ 5, 10, 10,-20,-20, 10, 10,  5}},
        {{ 0,  0,  0,  0,  0,  0,  0,  0}}
    }};

    inline static constexpr std::array<std::array<int, 8>, 8> knight_eval_matrix = {{
        {{-50,-40,-30,-30,-30,-30,-40,-50}},
        {{-40,-20,  0,  0,  0,  0,-20,-40}},
        {{-30,  0, 10, 15, 15, 10,  0,-30}},
        {{-30,  5, 15, 20, 20, 15,  5,-30}},
        {{-30,  0, 15, 20, 20, 15,  0,-30}},
        {{-30,  5, 10, 15, 15, 10,  5,-30}},
        {{-40,-20,  0,  5,  5,  0,-20,-40}},
        {{-50,-40,-30,-30,-30,-30,-40,-50}}
    }};

    inline static constexpr std::array<std::array<int, 8>, 8> bishop_eval_matrix = {{
        {{-20,-10,-10,-10,-10,-10,-10,-20}},
        {{-10,  0,  0,  0,  0,  0,  0,-10}},
        {{-10,  0,  5, 10, 10,  5,  0,-10}},
        {{-10,  5,  5, 10, 10,  5,  5,-10}},
        {{-10,  0, 10, 10, 10, 10,  0,-10}},
        {{-10, 10, 10, 10, 10, 10, 10,-10}},
        {{-10,  5,  0,  0,  0,  0,  5,-10}},
        {{-20,-10,-10,-10,-10,-10,-10,-20}}
    }};

    inline static constexpr std::array<std::array<int, 8>, 8> rook_eval_matrix = {{
        {{0,  0,  0,  0,  0,  0,  0,  0}},
        {{5, 10, 10, 10, 10, 10, 10,  5}},
        {{-5,  0,  0,  0,  0,  0,  0, -5}},
        {{-5,  0,  0,  0,  0,  0,  0, -5}},
        {{-5,  0,  0,  0,  0,  0,  0, -5}},
        {{-5,  0,  0,  0,  0,  0,  0, -5}},
        {{-5,  0,  0,  0,  0,  0,  0, -5}},
        {{0,  0,  0,  5,  5,  0,  0,  0}}
    }};

    inline static constexpr std::array<std::array<int, 8>, 8> queen_eval_matrix = {{
        {{-20,-10,-10, -5, -5,-10,-10,-20}},
        {{-10,  0,  0,  0,  0,  0,  0,-10}},
        {{-10,  0,  5,  5,  5,  5,  0,-10}},
        {{-5,  0,  5,  5,  5,  5,  0, -5}},
        {{0,  0,  5,  5,  5,  5,  0, -5}},
        {{-10,  5,  5,  5,  5,  5,  0,-10}},
        {{-10,  0,  5,  0,  0,  0,  0,-10}},
        {{-20,-10,-10, -5, -5,-10,-10,-20}}
    }};

    inline static constexpr std::array<std::array<int, 8>, 8> king_eval_matrix_midgame = {{
        {{-30,-40,-40,-50,-50,-40,-40,-30}},
        {{-30,-40,-40,-50,-50,-40,-40,-30}},
        {{-30,-40,-40,-50,-50,-40,-40,-30}},
        {{-30,-40,-40,-50,-50,-40,-40,-30}},
        {{-20,-30,-30,-40,-40,-30,-30,-20}},
        {{-10,-20,-20,-20,-20,-20,-20,-10}},
        {{20, 20,  0,  0,  0,  0, 20, 20}},
        {{20, 30, 10,  0,  0, 10, 30, 20}}
    }};

    inline static constexpr auto black_pawn_eval_matrix = negate(pawn_eval_matrix);
    inline static constexpr auto black_knight_eval_matrix = negate(knight_eval_matrix);
    inline static constexpr auto black_bishop_eval_matrix = negate(bishop_eval_matrix);
    inline static constexpr auto black_rook_eval_matrix = negate(rook_eval_matrix);
    inline static constexpr auto black_queen_eval_matrix = negate(queen_eval_matrix);
    inline static constexpr auto black_king_eval_matrix_midgame = negate(king_eval_matrix_midgame);


    inline static constexpr auto white_pawn_eval_matrix = rotate_by_180_matrix(pawn_eval_matrix);
    inline static constexpr auto white_knight_eval_matrix = rotate_by_180_matrix(knight_eval_matrix);
    inline static constexpr auto white_bishop_eval_matrix = rotate_by_180_matrix(bishop_eval_matrix);
    inline static constexpr auto white_rook_eval_matrix = rotate_by_180_matrix(rook_eval_matrix);
    inline static constexpr auto white_queen_eval_matrix = rotate_by_180_matrix(queen_eval_matrix);
    inline static constexpr auto white_king_eval_matrix_midgame = rotate_by_180_matrix(king_eval_matrix_midgame);

    inline static constexpr int get_pawn_matrix_value(chess::Color color, int x, int y) {
        if (color == chess::Color::WHITE) {
            return white_pawn_eval_matrix[y][x];
        } else {
            return black_pawn_eval_matrix[y][x];
        }
    }

    inline static constexpr int get_bishop_matrix_value(chess::Color color, int x, int y) {
        if (color == chess::Color::WHITE) {
            return white_bishop_eval_matrix[y][x];
        } else {
            return black_bishop_eval_matrix[y][x];
        }
    }

    inline static constexpr int get_knight_matrix_value(chess::Color color, int x, int y) {
        if (color == chess::Color::WHITE) {
            return white_knight_eval_matrix[y][x];
        } else {
            return black_knight_eval_matrix[y][x];
        }
    }

    inline static constexpr int get_queen_matrix_value(chess::Color color, int x, int y) {
        if (color == chess::Color::WHITE) {
            return white_queen_eval_matrix[y][x];
        } else {
            return black_queen_eval_matrix[y][x];
        }
    }

    inline static constexpr int get_king_matrix_value(chess::Color color, int x, int y) {
        if (color == chess::Color::WHITE) {
            return white_king_eval_matrix_midgame[y][x];
        } else {
            return black_king_eval_matrix_midgame[y][x];
        }
    }

    inline static constexpr int get_rook_matrix_value(chess::Color color, int x, int y) {
        if (color == chess::Color::WHITE) {
            return white_rook_eval_matrix[y][x];
        } else {
            return black_rook_eval_matrix[y][x];
        }
    }


    inline static constexpr int get_value_for_position_of_piece(const chess::PlacedPiece& p) {
        // value_matrix;
        const auto& x = p.coordinates_.x_;
        const auto& y = p.coordinates_.y_;
        
        if (p.piece_ == chess::Piece::PAWN) {
            return get_pawn_matrix_value(p.color_, x, y);
        } else if (p.piece_ == chess::Piece::BISHOP) {
            return get_bishop_matrix_value(p.color_, x, y);
        } else if (p.piece_ == chess::Piece::ROOK) {
            return get_rook_matrix_value(p.color_, x, y);
        } else if (p.piece_ == chess::Piece::QUEEN) {
            return get_queen_matrix_value(p.color_, x, y);
        } else if (p.piece_ == chess::Piece::KNIGHT) {
            return get_knight_matrix_value(p.color_, x, y);
        } else if (p.piece_ == chess::Piece::KING) {
            return get_king_matrix_value(p.color_, x, y);
        } else {
            return 0;
        }
    }

    inline static constexpr int get_value_for_piece_existence(const chess::PlacedPiece& p) {
        // value_matrix;
        const int mult = p.color_ == chess::Color::WHITE ? 1 : -1;
        // P = 100
        // N = 320
        // B = 330
        // R = 500
        // Q = 900
        // K = 20000
        if (p.piece_ == chess::Piece::PAWN) {
            return mult * 100;
        } else if (p.piece_ == chess::Piece::BISHOP) {
            return mult * 330;
        } else if (p.piece_ == chess::Piece::ROOK) {
            return mult * 500;
        } else if (p.piece_ == chess::Piece::QUEEN) {
            return mult * 900;
        } else if (p.piece_ == chess::Piece::KNIGHT) {
            return mult * 320;
        } else if (p.piece_ == chess::Piece::KING) {
            return mult * 20000;
        } else {
            return 0;
        }
    }
public:
    static int eval(const chess::BasicBoard& board) {
        int position_value = 0;
        int piece_value = 0;
        for (const auto& piece : board.available_pieces()) {
            position_value += get_value_for_position_of_piece(piece);
            piece_value += get_value_for_piece_existence(piece);
            // std::cout << piece.piece_ << " " << piece.coordinates_ << " " << piece.id_ << std::endl;
            // std::cout << get_value_for_piece_existence(piece) << " " << get_value_for_position_of_piece(piece) << std::endl;
            // std::cout <<"--------------" << std::endl;
        }
        int sum = piece_value + position_value;
        return sum;
    }
};  