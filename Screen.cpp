#include "Piece.cpp"
#include "time.h"
#include <array>
#include <iostream>


class Screen{
private:
    //variables for board height and width, width should be odd to allow for piece to center
    static const int board_width = 13;
    static const int board_height = 13;
    //need a variable to get starting position
    int starting_col = (board_width/2) - 1;


    //array for game board
    std::array<std::array<char, board_width>, board_height> screen;
    Piece p = Piece();

    Z_block Z_piece;
    I_block I_piece;
    J_block J_piece;
    L_block L_piece;
    O_block O_piece;
    T_block T_piece;
    S_block S_piece;

public:

    Screen(){
        //fill each pixel
        reset_screen();

    }
    // bools to allow for main function to have while condition for exiting game
    bool check_for_exit = true;
    bool can_move_down = true;

    //gets random number and uses switch to get corresponding random piece.

    std::array<array<char, 3>, 3> get_rand_piece(){
        p.reset_pos();
        can_move_down = true;
        std::cout<< "This the the reset position: ";
        std::cout << p.cur_pos[0] << ", " << p.cur_pos[1] << "\n";

        srand ( time(NULL) );
        int num = rand() % 6 ;

        switch (num) {
            case 0:
                return Z_piece.piece;
            case 1:
                return J_piece.piece;
            case 2:
                return I_piece.piece;
            case 3:
                return L_piece.piece;
            case 4:
                return O_piece.piece;
            case 5:
                return S_piece.piece;
            case 6:
                return T_piece.piece;

        }


    }

    //gets the array of current screen
    std::array<std::array<char, board_width>, board_height> get_screen(){
        return screen;
    }
    //resets the game board
    void reset_screen(){
        for(auto &s : screen){
            s.fill('.');
        }
    }

    void print_screen(){
        for (auto line : screen){
            for(auto pixel : line){
                std::cout << pixel;
            }
            std::cout << "\n";
        }
    }

    //add piece to screen
    void add_piece( std::array<std::array<char, 3>,3> piece){
        for(int row=0; row<piece.size(); row++){
            for(int col=5; col<5+piece.size(); col++ )
            {
                screen[row][col] = piece[row][col-5];
            }
        }
    }

    //pass the entire game board and position and change one index of row above with previous
    void rotate(std::array<std::array<char, board_width>, board_height> screen,std::array<int, 2> pos){
        //takes to piece and location and rotates it, no need to change position
        for(int row = 0; row < 3; row ++){
            for(int col = 0; col <  3; col ++) {

                this->screen[row + (pos[0] - 2)][col + pos[1]] = screen[2 - col+(pos[0]-2)][pos[1] + row];

            }
        }
    }

    void move_down(std::array<std::array<char, board_width>, board_height> screen, std::array<int, 2> pos){

        bool at_edge = false; // bool to allow for breaking out of second loop

        for (int i = pos[0] + 1; i >= pos[0] - 3; i--) {
            for (int j = pos[1]; j <pos[1] + 3; j++) {

                //if trying to move anything but X it won't move or if trying to move into and X already on board
                if(screen[i-1][j] != 'X' || this->screen[i][j] == 'X') {
                    if((screen[i-1][j] == 'X' && this->screen[i][j] == 'X')||
                        (screen[i-1][j+1] == 'X' && this->screen[i][j+1] =='X')||
                        (screen[i-1][j+2] == 'X' && this->screen[i][j+2] == 'X')){
                        //  sets at edge = true to allow for breaking from second loo[
                        at_edge = true;
                        break;
                    }
                    continue;
                }
                else{
                    //bottom bound, checks if at bottom of board and checks for collision
                    if (((pos[0] >= board_height - 1 || pos[1] >= board_height - 1)) &&
                    ((screen[board_height - 1][j] == 'X' || screen[board_height - 1][j + 1] == 'X'
                    || screen[board_height - 1][j + 2] == 'X'))) {
                        //  sets at edge = true to allow for breaking from second loo[
                        at_edge = true;
                        //  breaks from first loop
                        break;

                    } else {

                            this->screen[i][j] = screen[i - 1][j];
                            //screen[i-1][j] = the block you are trying to move
                            //this->screen[i][j] = block you are trying to move to
                            this->screen[i-1][j] = '.';
                            //sets the screen where piece was moved = to '.'

                    }
                }
            }
            if(at_edge) {  //  breaks from second for loop if the block is at a boundary

                //  if it is at the bottom or hitting another piece, it checks if it is also at the height
                //  limit or the top of the board and the game should end
                for(int r = 0; r < board_width; r++){
                    if(this->screen[0][r] == 'X'){
                        check_for_exit = false;
                    }
                }
                can_move_down = false;
                p.cur_pos[0] -= 1; // didn't move, need to subtract 1 from position so when it adds at the end the
                //position is still correct
                break;
            }
        }
        // adds 1 to the position (row) to account for moving down.
        p.cur_pos[0] +=1;
    }

    void move_right(std::array<std::array<char, board_width>, board_height> screen, std::array<int, 2> pos){

        std::array<int, 2> pos_new = pos; // make new array to more easily move right
        pos_new[1] += 2; //start position in bottom right to pull the piece over.
        bool at_edge = false; // bool to allow for breaking out of second loop

        //loop to move through the local 3x3 array surround the piece starting in bottom right.
        for(int i = pos_new[0]; i > pos_new[0] - 3; i--){
            for(int j = pos_new[1] + 1; j >= pos_new[1] - 2; j--) {

                //checks if the piece is at the edge and won't let it move further
                //makes sure that the actual piece, i.e. 'X' is at the edge and not just the empty space in
                //the 3x3 array that is being moved.
                if((pos_new[1]  >= board_width-1 || pos[1] >= board_width -1) && (screen[i][board_width-1] == 'X' ||
                screen[i-1][board_width-1] == 'X' || screen[i-2][board_width-1] == 'X')){

                    at_edge = true;
                    p.cur_pos[1] -=1; // didn't move, need to subtract 1 from position so when it adds at the end the
                    //position is still correct
                    break; //breaks from first loop
                }
                else {
                    if (j == pos[1]) { // piece already moved, need to remove remanence
                        this->screen[i][j] = '.';
                    } else {
                        if(screen[i][j-1] != 'X' && this-> screen[i][j] !='X'){ //ignores anything not the block
                            continue;
                        }
                        else {
                            this->screen[i][j] = screen[i][j - 1]; //sets the actual screen equal to where piece was
                        }
                    }
                }
            }
            if(at_edge){  //breaks from second for loop if the block is at the right bound
                break;
            }

        }

        p.cur_pos[1] +=1; //adds 1 to the position (col) to account for moving

    }

    void move_left(std::array<std::array<char, board_width>, board_height> screen, std::array<int, 2> pos){

        bool at_edge = false; // bool to allow for breaking out of second loop

        for(int i = pos[0]; i > pos[0] - 3; i--){
            for(int j = pos[1] - 1; j <= pos[1] + 2; j++) {

                if((pos[1]  == 0 ) && (screen[i][0] == 'X' ||
                                       screen[i-1][0] == 'X' || screen[i-2][0] == 'X')) {
                    at_edge = true;
                    p.cur_pos[1] += 1;
                    break;
                }
                else{
                    if (j == pos[1] + 2) { // piece already moved, need to remove remanence
                        this->screen[i][j] = '.';
                    }
                    else {
                        this->screen[i][j] = screen[i][j + 1];

                    }
                }
            }
            if(at_edge) {  //breaks from second for loop if the block is at the right bound
                break;
            }

        }
        std::cout << "\n";
        p.cur_pos[1] -=1; //adds 1 to the position (col) to account for moving
    }

    array<int, 2> get_position(){
        return p.cur_pos;

    }
    int get_board_height(){
        return board_height;
    }
};