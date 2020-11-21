#include "board.h"
class ai
{
    private:
    int player_int;

    public:
    ai(const int& i);
    std::array<int,2> calculate_move(const board& b, const int& player_int) const;
    int get_player_int() const;

};