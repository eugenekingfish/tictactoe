#include "ai.h"
#include <vector>
#include <iostream>

ai::ai(const int& i)
{
    this->player_int = i;
}

int ai::get_player_int() const
{
    return this->player_int;
}

std::array<int,2> ai::calculate_move(const board& b, const int& player_int) const
{
    std::array<int,2> res = {-1000 * player_int, -1};
    int winner = b.get_winner();
    if (winner != -2) { res[0] = winner * (1 + b.get_legal_moves().size()); return res; }

    std::vector<int> moves = b.get_legal_moves();

    for (int i = 0; i < moves.size(); ++i)
    {
        board b_temp(b.get_board());
        b_temp.update_board(moves[i], player_int);
        std::array<int,2> arr = calculate_move(b_temp, -player_int);

        if (player_int == -1)
        {
            if (arr[0] < res[0])
            {
                res[0] = arr[0];
                res[1] = moves[i];
            }
        }
        else
        {
            if (arr[0] > res[0])
            {
                res[0] = arr[0];
                res[1] = moves[i];
            }
        }
        
    }
    return res;
}   
