#include <iterator>
#include <limits>
#include <stdexcept>
#include "ai.h"


enum INPUTS
{
   MOVES, HELP, RESIGN, BOARD, OTHER
};

void print_winner_message(const int& winner_int, const int& player_int)
{
   std::string s;
   if (winner_int == player_int)
   {
      s = "You win!";
   }
   else if (winner_int == -player_int)
   {
      s = "AI wins!";
   }
   else
   {
      s = "Game is a draw!";
   }
   std::cout << s << std::endl;
   
}

INPUTS get_string_input(const std::string& s)
{
   if (s == "moves")
   {
      return MOVES;
   }
   else if (s == "board")
   {
      return BOARD;
   }
   else if (s == "help")
   {
      return HELP;
   }
   else if (s == "resign")
   {
      return RESIGN;
   }
   else
   {
      return OTHER;
   }
}

void play_versus_human()
{
    board b({
        0, 0, 0,
        0, 0, 0,
        0, 0, 0});

    std::string inpt;

    bool game_over = false;
    int turn_int = 1; //To keep track of whether it's X's or O's turn.

    b.print_board(0);
   
   while (!game_over)
   {
      std::string inpt;
      std::string foo = (turn_int == 1) ? "X" : "O";
      std::cout << ">> ";
      std::cin >> inpt;
      
      switch(get_string_input(inpt))
      {
         case RESIGN:
            {
            std::string winner = (turn_int == 1) ? "O" : "X";
            std::cout << winner << " wins!" << std::endl;
            game_over = true; 
            break;
            }

         case MOVES:
            std::cout << "Available moves:" << std::endl;        
            b.print_board(1);
            break;
         
         case HELP:
            {
            std::string s = 
               "\n* moves  -- displays legal moves.\n"
               "* board  -- shows current board state.\n"
               "* <i>    -- mark square i with your symbol.\n"
               "* resign -- resign the game.\n";
            std::cout << s << std::endl;
            break;
            }

         case BOARD:
            std::cout << "\nCurrent board state:" << std::endl;
            b.print_board(0);
            break;

         default:
            try 
            {
               int move = stoi(inpt);
               move -= 1; //Ensuring 1-based indexing.
               std::string s;
               if (b.is_move_valid(move))
               {
                  s = (turn_int == 1) ? "X" : "O";
                  std::cout << s + "'s move:" << std::endl;
                  b.update_board(move, turn_int);
                  int winner = b.get_winner();
                  if  (winner != -2)
                  {
                     std::string foo = "";
                     if (winner == 1) { foo = "X wins!"; }
                     else if  (winner == -1) { foo = "O wins!"; }
                     else { foo = "Game is a draw!"; }
                     std::cout << foo << std::endl;
                     game_over = true;
                  }
                  b.print_board(0); 
                  turn_int *= -1;
               }
               else { std::cout << "Invalid move: " << inpt << std::endl; }
            }
            catch(...)
            {
               std::cout << "Invalid move." << std::endl;
            }
            break;
      }

   }
}

void play_versus_ai()
{
    srand(time(NULL));

    board b({
        0, 0, 0,
        0, 0, 0,
        0, 0, 0});
    
    //Randomly choose if AI is playing as X or O. 
    int ai_int = rand() % 2;
    ai_int = ai_int == 0 ? -1 : 1;
    
    //Player is given the opposite symbol to the AI.
    int player_int = -ai_int;
   
    std::string s;
    s = (player_int == 1) ? "X" : "O";
    std::cout << "You are playing as: " << s << std::endl;

    //Create the AI. 
    ai x(ai_int);

    //If AI is playing as X, choose a random square to move.
    if (ai_int == 1) 
    { 
        int move = rand() % 9;
        b.update_board(move, x.get_player_int());
        std::cout << "AI's move:" << std::endl;
    }

    bool game_over = false;

    while (!game_over)
    {
        b.print_board(0);
        std::string inpt;

        bool valid_move = false;

        while (!valid_move)
        {
            std::cout << ">>> ";
            std::cin >> inpt;
            
            //Prints available moves.
            if (inpt == "moves")
            {
               std::cout << "Available moves:" << std::endl;
               b.print_board(1);
            }

            else if (inpt == "help")
            {
               std::string s = 
                  "\n* moves  -- displays legal moves.\n"
                  "* board  -- shows current board state.\n"
                  "* <i>    -- mark square i with your symbol.\n"
                  "* resign -- resign the game.\n";
               std::cout << s << std::endl;
            }
            
            //Prints the current board state.
            else if(inpt == "board")
            {
               std::cout << "\nCurrent board state:" << std::endl;
               b.print_board(0);
            }

            //Player resigns the game.
            else if (inpt == "resign")
            {
               print_winner_message(-player_int, player_int);
               game_over = true;
               break;
            }
            else
            {
               try
               {
                  int p_move = std::stoi(inpt) - 1; //Convert input string into an int.
                  if (b.is_move_valid(p_move)) //Check if the move is valid.
                  {
                     valid_move = true; 
                     b.update_board(p_move, player_int); //Update the board with the player's move.
                     std::cout << "Your move:" << std::endl;
                     b.print_board(0);
                     int winner_int = b.get_winner();
                     if  (winner_int != -2) //Check if the game has been won.
                     {
                        print_winner_message(winner_int, player_int);
                        game_over = true; 
                        break; 
                     }
                  }
                  else
                  {
                     std::cout << "Invalid move." << std::endl;
                  }
               }
               catch(...)
               {
                  std::cout << "Invalid input." << std::endl; 
               }
            }
            
         }
        
        if (!game_over)
        {
           std::array<int,2> arr = x.calculate_move(b, x.get_player_int());
           b.update_board(arr[1], x.get_player_int());
           std::cout << "AI's move:" << std::endl;
           int winner_int = b.get_winner();
           
           if (winner_int != -2) 
           { 
              b.print_board(0); 
              print_winner_message(winner_int, player_int);
              break; 
           }
        }
    }   
}

int main()
{
   std::cout << "Enter 'help' for a list of available commands." << std::endl;  
    while (true)
    {
      std::cout << "Please enter a command: ";
      std::string s;
      std::cin >> s;
      
      if (s == "quit")
      {
         std::cout << "Application closed." << std::endl;
         break;
      }
      else if (s == "ai")
      {
         play_versus_ai();
      }
      else if (s == "human")
      {
         play_versus_human();
      }
      else if (s == "help")
      {
         std::string foo = 
            "\n* help  -- displays list of commands.\n"
            "* human -- begin a 2-player game of tictactoe.\n"
            "* ai    -- begin a game of tictactoe versus the computer.\n"
            "* quit  -- close the application.\n";
         std::cout << foo << std::endl;   
      }
      else
      {  
         std::cout << "Unrecognised command '" << s << "'. Use command 'help' for a list of available commands." << std::endl;
      }

    }
}
