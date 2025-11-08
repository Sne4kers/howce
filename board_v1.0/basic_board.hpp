#include "general/chess.h"
#include <vector>
#include <array>
#include <tuple>
#include <stdexcept>

namespace chess {
class BasicBoard : public BoardInterface {
private:
    inline bool is_point_in_bound(const Point& p) const {
        return p.x_ >= 0 && p.y_ >= 0 && p.x_ < 8 && p.y_ < 8;
    }
    std::vector<PlacedPiece> all_pieceses_;
    std::array<std::array<std::pair<Piece, Color>, 8>, 8> board_state_;
    std::vector<Move> moves_made_;

    Color next_to_go_ = Color::WHITE;
    bool game_is_finished_ = false;
    
    inline bool is_square_empty(const Point& p) const {
        // assumes correct coordinates passed before that
        return board_state_[p.x_][p.y_].first == Piece::VOID;
    }

    template<Piece Piece_T>
    inline constexpr std::vector<int> get_diff_x_for_piece() const {
        if constexpr (Piece_T == Piece::ROOK) {
            return std::vector<int>({0, 0, 1, -1});
        } 
        if constexpr (Piece_T == Piece::BISHOP) {
            return std::vector<int>({1, -1, 1, -1});
        }
        if constexpr (Piece_T == Piece::QUEEN) {
            return std::vector<int>({1, -1, 1, -1, 0, 0, 1, -1});
        } else {
            // assert(false && "call for wron type");
            return std::vector<int>({});
        }
    }

    template<Piece Piece_T>
    inline constexpr std::vector<int> get_diff_y_for_piece() const {
        if constexpr (Piece_T == Piece::ROOK) {
            return {1, -1, 0, 0};
        } 
        if constexpr (Piece_T == Piece::BISHOP) {
            return {1, 1, -1, -1};
        }
        if constexpr (Piece_T == Piece::QUEEN) {
            return {1, -1, 0, 0, 1, 1, -1, -1};
        } else {
            // assert(false && "call for wron type")
            return {};
        }
    }

    template<Piece Piece_T>
    std::vector<Point> get_moves_from_position(const PlacedPiece& piece_to_move) const {
        std::vector<Point> result;
        result.reserve(24);

        const std::vector<int> possible_diff_x = get_diff_x_for_piece<Piece_T>();
        const std::vector<int> possible_diff_y = get_diff_y_for_piece<Piece_T>();
        // static_assert(possible_diff_x.size() == possible_diff_y.size());

        for (size_t i = 0; i < possible_diff_x.size(); i++) {
            auto new_coords = piece_to_move.coordinates_;
            int current_diff_x = possible_diff_x[i];
            int current_diff_y = possible_diff_y[i];
            for (size_t _ = 1; _ < 8; _++) {
                new_coords.y_ += current_diff_y;
                new_coords.x_ += current_diff_x;
                if (is_point_in_bound(new_coords) && is_square_empty(new_coords)) {
                    result.push_back(new_coords);
                } else {
                    break;
                }
            }
        }
        return result;
    }

    std::vector<Point> get_possible_moves(const PlacedPiece& piece_to_move) const {
        std::vector<Point> result;
        result.reserve(24);
        if (piece_to_move.piece_ == Piece::ROOK) {
            return get_moves_from_position<Piece::ROOK>(piece_to_move);

        } else if (piece_to_move.piece_ == Piece::BISHOP) {
            return get_moves_from_position<Piece::BISHOP>(piece_to_move);

        } else if (piece_to_move.piece_ == Piece::QUEEN) {
            return get_moves_from_position<Piece::QUEEN>(piece_to_move);

        } else if (piece_to_move.piece_ == Piece::KNIGHT) {
            
            auto possible_moves = std::array<Point, 8>({
                Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ - 1), static_cast<int16_t>(piece_to_move.coordinates_.y_ - 2)},
                Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ - 1), static_cast<int16_t>(piece_to_move.coordinates_.y_ + 2)},
                Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ + 1), static_cast<int16_t>(piece_to_move.coordinates_.y_ + 2)},
                Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ + 1), static_cast<int16_t>(piece_to_move.coordinates_.y_ - 2)},
                Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ + 2), static_cast<int16_t>(piece_to_move.coordinates_.y_ - 1)},
                Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ + 2), static_cast<int16_t>(piece_to_move.coordinates_.y_ + 1)},
                Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ - 2), static_cast<int16_t>(piece_to_move.coordinates_.y_ + 1)},
                Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ - 2), static_cast<int16_t>(piece_to_move.coordinates_.y_ - 1)},
                
            });
            for (const auto& new_position : possible_moves) {
                if (is_point_in_bound(new_position) && is_square_empty(new_position)) {
                    result.emplace_back(new_position);
                }
            }
            return result;
        } else if (piece_to_move.piece_ == Piece::KING) {
            auto possible_moves = std::array<Point, 8>({
                Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ - 1), static_cast<int16_t>(piece_to_move.coordinates_.y_ + 0)},
                Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ - 1), static_cast<int16_t>(piece_to_move.coordinates_.y_ + 1)},
                Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ - 1), static_cast<int16_t>(piece_to_move.coordinates_.y_ - 1)},
                Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ + 1), static_cast<int16_t>(piece_to_move.coordinates_.y_ + 0)},
                Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ + 1), static_cast<int16_t>(piece_to_move.coordinates_.y_ + 1)},
                Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ + 1), static_cast<int16_t>(piece_to_move.coordinates_.y_ - 1)},
                Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ + 0), static_cast<int16_t>(piece_to_move.coordinates_.y_ - 1)},
                Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ + 0), static_cast<int16_t>(piece_to_move.coordinates_.y_ + 1)},
            });
            for (const auto& new_position : possible_moves) {
                if (is_point_in_bound(new_position) && is_square_empty(new_position)) {
                    result.emplace_back(new_position);
                }
            }
            return result;
        } else if (piece_to_move.piece_ == Piece::PAWN) {
            std::array<Point, 2> possible_captures;
            Point move_forward, extra_move_forward;
            int row_value_with_extra_jump;
            if (piece_to_move.color_ == Color::BLACK) {
                row_value_with_extra_jump = 6;
                possible_captures = std::array<Point, 2>({
                    Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ + 1), static_cast<int16_t>(piece_to_move.coordinates_.y_ - 1)},
                    Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ - 1), static_cast<int16_t>(piece_to_move.coordinates_.y_ - 1)},
                });

                move_forward = Point{piece_to_move.coordinates_.x_, static_cast<int16_t>(piece_to_move.coordinates_.y_ - 1)};
                extra_move_forward = Point{piece_to_move.coordinates_.x_, static_cast<int16_t>(piece_to_move.coordinates_.y_ - 2)};
            } else {
                row_value_with_extra_jump = 1;
                possible_captures = std::array<Point, 2>({
                    Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ + 1), static_cast<int16_t>(piece_to_move.coordinates_.y_ + 1)},
                    Point{static_cast<int16_t>(piece_to_move.coordinates_.x_ - 1), static_cast<int16_t>(piece_to_move.coordinates_.y_ + 1)},
                });
                
                move_forward = Point{piece_to_move.coordinates_.x_, static_cast<int16_t>(piece_to_move.coordinates_.y_ + 1)};
                extra_move_forward = Point{piece_to_move.coordinates_.x_, static_cast<int16_t>(piece_to_move.coordinates_.y_ + 2)};    
            }

            for (const auto& possible_capture : possible_captures) {
                if (is_point_in_bound(possible_capture) && !is_square_empty(possible_capture)) {
                    result.emplace_back(possible_capture);
                }
            }
            
            if (piece_to_move.coordinates_.y_  == row_value_with_extra_jump && is_point_in_bound(move_forward) && is_point_in_bound(extra_move_forward) && is_square_empty(move_forward) && is_square_empty(extra_move_forward)) {
                result.emplace_back(extra_move_forward);
            }

            if (is_point_in_bound(move_forward) && is_square_empty(move_forward)) {
                result.emplace_back(move_forward);
            }
            
            // TODO enpasssant rule
            return result;  
        } else {
            return {};    
        }
    }
public:
    BasicBoard() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                board_state_[i][j] = std::make_pair(Piece::VOID, Color::WHITE);
            }
        }

        board_state_[0][0] = std::make_pair(Piece::ROOK, Color::WHITE);
        board_state_[1][0] = std::make_pair(Piece::KNIGHT, Color::WHITE);
        board_state_[2][0] = std::make_pair(Piece::BISHOP, Color::WHITE);
        board_state_[3][0] = std::make_pair(Piece::QUEEN, Color::WHITE);
        board_state_[4][0] = std::make_pair(Piece::KING, Color::WHITE);
        board_state_[5][0] = std::make_pair(Piece::BISHOP, Color::WHITE);
        board_state_[6][0] = std::make_pair(Piece::KNIGHT, Color::WHITE);
        board_state_[7][0] = std::make_pair(Piece::ROOK, Color::WHITE);

        board_state_[0][1] = std::make_pair(Piece::PAWN, Color::WHITE);
        board_state_[1][1] = std::make_pair(Piece::PAWN, Color::WHITE);
        board_state_[2][1] = std::make_pair(Piece::PAWN, Color::WHITE);
        board_state_[3][1] = std::make_pair(Piece::PAWN, Color::WHITE);
        board_state_[4][1] = std::make_pair(Piece::PAWN, Color::WHITE);
        board_state_[5][1] = std::make_pair(Piece::PAWN, Color::WHITE);
        board_state_[6][1] = std::make_pair(Piece::PAWN, Color::WHITE);
        board_state_[7][1] = std::make_pair(Piece::PAWN, Color::WHITE);

        board_state_[0][7] = std::make_pair(Piece::ROOK, Color::BLACK);
        board_state_[1][7] = std::make_pair(Piece::KNIGHT, Color::BLACK);
        board_state_[2][7] = std::make_pair(Piece::BISHOP, Color::BLACK);
        board_state_[3][7] = std::make_pair(Piece::QUEEN, Color::BLACK);
        board_state_[4][7] = std::make_pair(Piece::KING, Color::BLACK);
        board_state_[5][7] = std::make_pair(Piece::BISHOP, Color::BLACK);
        board_state_[6][7] = std::make_pair(Piece::KNIGHT, Color::BLACK);
        board_state_[7][7] = std::make_pair(Piece::ROOK, Color::BLACK);

        board_state_[0][6] = std::make_pair(Piece::PAWN, Color::BLACK);
        board_state_[1][6] = std::make_pair(Piece::PAWN, Color::BLACK);
        board_state_[2][6] = std::make_pair(Piece::PAWN, Color::BLACK);
        board_state_[3][6] = std::make_pair(Piece::PAWN, Color::BLACK);
        board_state_[4][6] = std::make_pair(Piece::PAWN, Color::BLACK);
        board_state_[5][6] = std::make_pair(Piece::PAWN, Color::BLACK);
        board_state_[6][6] = std::make_pair(Piece::PAWN, Color::BLACK);
        board_state_[7][6] = std::make_pair(Piece::PAWN, Color::BLACK);
        
        PieceId next_id = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                const auto& [piece, piece_color] = board_state_[i][j];
                if (piece != Piece::VOID) {
                    all_pieceses_.emplace_back(PlacedPiece{piece, piece_color, Point{static_cast<int16_t>(i), static_cast<int16_t>(j)}, next_id});
                    next_id++;
                }
            }
        }
    }

    bool is_finished() const override {
        return game_is_finished_;
    }
    
    Color next_to_move() const override {
        return next_to_go_;
    }

    std::vector<PlacedPiece> available_pieces() const override {
        return all_pieceses_;
    }

    std::vector<Point> get_possible_moves_for_piece(const PieceId& piece_id_to_move) const override {
        for (const auto& piece : all_pieceses_) {
            if (piece.id_ == piece_id_to_move) [[ unlikely ]] {
                return get_possible_moves(piece);
            }
        }
        throw std::runtime_error("No such piece id available");
        return {};
    }

    PlacedPiece get_piece_info_from_id(const PieceId& piece_id_to_move) const {
        for (const auto& piece : all_pieceses_) {
            if (piece.id_ == piece_id_to_move) [[ unlikely ]] {
                return piece;
            }
        }
        throw std::runtime_error("No such piece id available");
        return {};
    }

    std::vector<Move> get_move_log() const {
        return moves_made_;
    }

    friend std::ostream &operator<<(std::ostream &os, const BasicBoard& m) { 
        const std::string new_line = "\n";
        const std::string space_literal = " ";
        const std::string reset_literal_line = "\x1b[0;m";
        for (int i = 7; i >= 0; i--) {
            for (int j = 0; j < 8; j++) {
                os << get_pretty_printing_of_cell_with_piece(m.board_state_[j][i].first, m.board_state_[j][i].second, j, i);
            }
            os << reset_literal_line;
            os << space_literal << std::to_string(i + 1);
            os << new_line;
        }
        std::string col_value = " a ";
        for (int j = 0; j < 8; j++) {
            os << col_value;
            col_value[1]++;
        }
        os << new_line;
        return os;
    }

};
}