#include <array>
#include <vector>
#include <math.h>
#include <string>
#include <iostream>

class board
{
    private:
    std::array<int,9> arr;

    public:
    board(const std::array<int,9>& arr);
    board();

    int get_winner() const;
    std::vector<int> get_legal_moves() const;
    std::array<int,9> get_board() const;
    void print_board(const int& type) const;
    bool update_board(const int& idx, const int& val);
    bool is_move_valid(int move_idx) const;
};
