#include <iostream>
#include "Screen.cpp"
#include <array>
#include <Windows.h>
//found online for Sleep function to use as time delay

    int main() {
    Screen screen = Screen();

    //array position to be used for the loop to move down
    array<int, 2> position;
    position[0] = screen.get_board_height(); // initializing to height of board
    while(screen.check_for_exit){

        screen.add_piece(screen.get_rand_piece());
        // call for a new piece and puts it on the board
        //moves down at maximum as many times and the board height
        for(int i = 0; i < screen.get_board_height(); i ++) {
            //only prints the screen and calls move down if there has been no collision with the previous piece
            //and/or the previous piece is not at the bottom of the board.
            if(screen.can_move_down) {
                char choice;
                screen.print_screen();
                Sleep(1000);  // delays the falling possible in future to make time speed up
                std::cout << "\n";
                std::cout << "Which way would you like to move?\n"
                             "(Right 'R')(Left 'L')(Down 'D')(Rotate 'S'): \n";
                std::cin >> choice;

                    if(choice == 'R'){
                        screen.move_right(screen.get_screen(), screen.get_position());
                        Sleep(1000);
                    }
                    else if(choice == 'L'){
                        screen.move_left(screen.get_screen(), screen.get_position());
                        Sleep(1000);
                    }
                    else if(choice =='S'){
                        screen.rotate(screen.get_screen(), screen.get_position() );
                        Sleep(1000);
                    }



                screen.move_down(screen.get_screen(), screen.get_position());
            }

        }

    }
    std::cout << "Game Over, Thanks for playing.";




}
