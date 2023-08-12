#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// 2D Coordinate

struct Coordinate {
    int x;
    int y;
    Coordinate(): x{0}, y{0} {}
    Coordinate(int x, int y): x{x}, y{y} {}
    Coordinate operator+(const Coordinate &rhs) const {return Coordinate{x + rhs.x, y + rhs.y};}
    Coordinate operator-(const Coordinate &rhs) const {return Coordinate{x - rhs.x, y - rhs.y};}
    Coordinate& operator+=(const Coordinate &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Coordinate& operator-=(const Coordinate &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    template<typename T>
    static inline T& get(vector<vector<T>> &vvT, Coordinate &coordinate) {return vvT[coordinate.y][coordinate.x];}
};

#define DIR 4
Coordinate dir[DIR] = {
    { 1, 0}, {-1, 0}, { 0,-1}, { 0, 1}
};

// Chess Piece

enum Direction {
    RIGHT = 0,
    LEFT = 1,
    UP = 2,
    DOWN = 3
};

istream& operator>>(istream& is, Direction& direction) {
    int temp;
    is >> temp;
    direction = static_cast<Direction>(temp - 1);
    return is;
}

struct Piece {
    Coordinate coordinate;
    Direction direction;
    Piece(): coordinate{}, direction{} {};
    Piece(int x, int y, int dirction): coordinate{x, y}, direction{direction} {};
    void invert_direction() {
        #define INVERT 1
        direction = static_cast<Direction>((int)direction ^ INVERT);
        #undef INVERT
    }
};

// Group

struct Group {
    deque<int> pieces_id;
    Group():pieces_id() {}
    void push_back(int piece) {pieces_id.push_back(piece);}
    void add(Group &group) {
        for(int piece_id: group.pieces_id) {pieces_id.push_back(piece_id);}
        deque<int>().swap(group.pieces_id);
    }
    void invert_add(Group &group) {
        typedef deque<int>::reverse_iterator dPri;
        for(dPri rit = group.pieces_id.rbegin(); rit != group.pieces_id.rend(); ++rit) {
            pieces_id.push_back(*rit);
        }
        deque<int>().swap(group.pieces_id);
    }
};

// Board

enum FloorColor {
    WHITE = 0,
    RED = 1,
    BLUE = 2
};

istream& operator>>(istream& is, FloorColor& floor_color) {
    int temp;
    is >> temp;
    floor_color = static_cast<FloorColor>(temp);
    return is;
}

struct Board {
    int turn;
    vector<vector<Group>> groups;
    vector<vector<FloorColor>> floor_color;
    int number_of_pieces;
    vector<Piece> pieces_list;
    vector<bool> pieces_valid;
    Board(int size, int pieces):
        groups{vector<vector<Group>>(size + 2, vector<Group>(size + 2, Group()))},
        floor_color{vector<vector<FloorColor>>(size + 2, vector<FloorColor>(size + 2, BLUE))},
        number_of_pieces(pieces),
        pieces_list{vector<Piece>(pieces, Piece())},
        pieces_valid{vector<bool>(pieces, true)}
    {
        for(int col_it = 1; col_it <= size; ++col_it) {
            for(int row_it = 1; row_it <= size; ++row_it) {
                cin >> floor_color[col_it][row_it];
            }
        }
        int piece_it = 0;
        for(Piece &piece: pieces_list) {
            cin >> piece.coordinate.y >> piece.coordinate.x >> piece.direction;
            using Cord = Coordinate;
            Cord::get(groups, piece.coordinate).push_back(piece_it++);
        }
    }
    bool run_turn() {
        for(int it = 0; it < number_of_pieces; ++it) {
            if(!pieces_valid[it]) {continue;}
            #define GOAL 4
            if(GOAL <= move_group(it)) {
                return true;
            }
            #undef GOAL
        }
        return false;
    }
    size_t move_group(int piece_no) {
        Piece &piece = pieces_list[piece_no];
        Coordinate now = piece.coordinate;
        Coordinate next = piece.coordinate + dir[piece.direction];
        using Cord = Coordinate;
        FloorColor floor_color_next = Cord::get(floor_color, next);
        if(floor_color_next == WHITE) {
            Group &group_next = Cord::get(groups, next);
            Group &group_now = Cord::get(groups, now);
            group_next.add(group_now);
            pieces_valid[piece_no] = false;
            int group_front = group_next.pieces_id.front();
            pieces_valid[group_front] = true;
            pieces_list[group_front].coordinate = next;
            return group_next.pieces_id.size();
        }
        else if(floor_color_next == RED) {
            Group &group_next = Cord::get(groups, next);
            Group &group_now = Cord::get(groups, now);
            group_next.invert_add(group_now);
            pieces_valid[piece_no] = false;
            int group_front = group_next.pieces_id.front();
            pieces_valid[group_front] = true;
            pieces_list[group_front].coordinate = next;
            return group_next.pieces_id.size();
        }
        else if(floor_color_next ==  BLUE) {
            Coordinate prev = piece.coordinate - dir[piece.direction];
            piece.invert_direction();
            if(Cord::get(floor_color, prev) == BLUE) {return Cord::get(groups, now).pieces_id.size();}
            return move_group(piece_no);
        }
        return -1;
    }
};

int main() {
    int size, number_of_pieces;
    cin >> size >> number_of_pieces;
    Board board{size, number_of_pieces};
    #define MAX_LOOP 1000
    for(int it = 1; it <= MAX_LOOP; ++it) {
        if(!board.run_turn()) {continue;}
        cout << it;
        return 0;
    }
    #undef MAX_LOOP
    cout << -1;
    return 0;
}