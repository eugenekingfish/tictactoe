#include "board.h"

#define SIGN(a) ((a > 0) - (a < 0))

board::board(const std::array<int,9>& arr) 
{
    this->arr = arr;
}

board::board()
{
    for (int i = 0; i < this->arr.size(); ++i)
    {
        this->arr[i] = 0;
    }
}

//Returns 1 if X wins, -1 if O wins, 0 if draw, and -2 if game is unfinished.
int board::get_winner() const
{
    std::array<int,4> totals = {0, 0, 0, 0};

    //Left-right diagonal
    totals[0] = this->arr[0] + this->arr[4] + arr[8];
    //Right-left diagonal
    totals[1] = this->arr[2] + this->arr[4] + this->arr[6];

    for (int i = 0; i < 3; ++i)
    {
        //Columns
        totals[2] = this->arr[i] + this->arr[i+3] + this->arr[i+6];
        //Rows
        totals[3] = this->arr[i + 2*i] + this->arr[i + 2*i + 1] + this->arr[i + 2*i + 2];

        if (abs(totals[2]) == 3 || abs(totals[3]) == 3) { break; }
    }

    for (int i = 0; i < totals.size(); ++i)
    {
        if (abs(totals[i]) == 3) { return SIGN(totals[i]); }
    }

    std::vector<int> moves = this->get_legal_moves();
    if (moves.size() == 0) { return 0; }
    else { return -2; }
}

std::vector<int> board::get_legal_moves() const
{
    std::vector<int> moves;
    for (int i = 0; i < this->arr.size(); ++i)
    {
        if (this->arr[i] == 0) { moves.push_back(i); }
    }
    return moves;
}

std::array<int,9> board::get_board() const
{
    return this->arr;
}

void board::print_board(const int& type) const
{
    std::string res = "\n";
    for (int i = 0; i < 9; ++i)
    {
        std::string s = " ";
        switch (this->arr[i])
        {
            case  1: type == 0 ? s = "X" : s = "-"; break;
            case -1: type == 0 ? s = "O" : s = "-"; break;
            case  0: type == 0 ? s = "_" : s = std::to_string(i+1); break;
        }
        if (i > 0 && i % 3 == 0) { res += ("|\n|" + s); }
        else { res += ("|" + s); }
    }
    res += "|\n";
    std::cout << res << std::endl;
}

bool board::is_move_valid(int move_idx) const
{
    if (this->arr[move_idx] == 0) { return true; }
    return false;
}

bool board::update_board(const int& idx, const int& val)
{
    if (0 <= idx && idx < this->arr.size() && this->arr[idx] == 0)
    {
        this->arr[idx] = val;
        return true;
    }
    return false;
}
