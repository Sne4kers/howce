#include <vector>
#include <cinttypes>
#include <stdexcept>

namespace chess {
enum Piece {
    ROOK = 4,
    QUEEN = 6,
    KING = 5,
    KNIGHT = 3,
    BISHOP = 2,
    PAWN = 1,
    VOID = 0
};

enum Color {
    WHITE = true,
    BLACK = false
};

struct Point {
    int16_t x_;
    int16_t y_;
};

using PieceId = int;

struct PlacedPiece {
    Piece piece_;
    Color color_;
    Point coordinates_;
    PieceId id_;
};

std::ostream &operator<<(std::ostream &os, const Piece& piece) { 
    std::string value;
    if (piece == Piece::BISHOP) {
        value = "Bishop";
    } else if (piece == Piece::PAWN) {
        value = "Pawn";
    } else if (piece == Piece::KNIGHT) {
        value = "Knight";
    } else if (piece == Piece::QUEEN) {
        value = "Queen";
    } else if (piece == Piece::KING) {
        value = "King";
    } else if (piece == Piece::ROOK) {
        value = "Rook";
    } else {
        value = "Void This shouldnt happen";
    }
    os << value;
    return os;
}

std::ostream& operator<<(std::ostream &os, const Color& color) { 
    std::string value;
    if (color == Color::WHITE) {
        value = "White";
    } else if (color == Color::BLACK) {
        value = "Black";
    } else {
        value = "Color Not implemented, This shouldnt happen";
    }
    os << value;
    return os;
}

std::ostream& operator<<(std::ostream &os, const Point& point) { 
    std::string value = std::string(1, 'a' + point.x_) + std::to_string(point.y_ + 1);
    os << value;
    return os;
}

std::ostream& operator<<(std::ostream &os, const PieceId& id) { 
    os << std::to_string(id);
    return os;
}

std::ostream& operator<<(std::ostream &os, const PlacedPiece& placed_piece) { 
    const std::string space_str = " ";
    const std::string at_str = "@";
    const std::string with_id_str = " with id ";
    os << placed_piece.color_ << space_str << placed_piece.piece_ << at_str << placed_piece.coordinates_ << with_id_str << placed_piece.id_;
    return os;
}

struct Move {
    chess::Point from_;
    chess::Point to_;
};

std::string get_pretty_printing_of_cell_with_piece(const Piece& piece, const Color& piece_color, int x, int y) {
    Color color_of_cell = ((x + y) % 2 == 1) ? Color::WHITE : Color::BLACK;
    std::string piece_literal;
    std::string background_color_escape_seq;
    std::string piece_color_escape_seq;
    if (piece == Piece::PAWN) {
        piece_literal = " p ";
    } else if (piece == Piece::BISHOP) {
        piece_literal = " b ";
    } else if (piece == Piece::ROOK) {
        piece_literal = " R ";
    } else if (piece == Piece::KNIGHT) {
        piece_literal = " h ";
    } else if (piece == Piece::QUEEN) {
        piece_literal = " Q ";
    } else if (piece == Piece::KING) {
        piece_literal = " K ";
    } else {
        piece_literal = "   ";
    }
    if (color_of_cell == Color::WHITE) {
        background_color_escape_seq = "\x1b[48;5;247m";
    } else {
        background_color_escape_seq = "\x1b[48;5;232m";
    }
    if (piece_color == Color::WHITE) {
        piece_color_escape_seq = "\x1b[38;5;15m";
    } else {
        piece_color_escape_seq = "\x1b[38;5;238m";
    }
    return background_color_escape_seq + piece_color_escape_seq + piece_literal;
}

class BoardInterface {
public:
    virtual bool is_finished() const = 0;
    virtual Color next_to_move() const = 0;
    virtual std::vector<PlacedPiece> available_pieces() const = 0;
    virtual std::vector<Point> get_possible_moves_for_piece(const PieceId& piece_id_to_move) const = 0;
};
}