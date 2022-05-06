#include <array>

using std::array;

class Piece {
protected:
    //initial position when new piece put on board

    const array<int, 2> pos = {2,5};

public:
    //variable cur_pos to allow the current piece's position to be manipulated
    array<int, 2> cur_pos = pos;


    Piece() = default;;

    //resets the position of new piece when it generates
    //called when get_rand_piece is called
    void reset_pos(){
        cur_pos = pos;
    }



};
// All different pieces as arrays of char arrays

class Z_block: public Piece{
public:
    array<array<char, 3>, 3> piece   = {{{'.', 'X', '.'},
                                         {'X', 'X', '.'},
                                         {'X', '.', '.'},}};
};

class I_block: public Piece{
public:
    array<array<char, 3>, 3> piece =   {{{'.', 'X', '.'},
                                         {'.', 'X', '.'},
                                         {'.', 'X', '.'},}};

};

class J_block: public Piece{
public:
    array<array<char, 3>, 3> piece =   {{{'.', 'X', '.'},
                                         {'.', 'X', '.'},
                                         {'X', 'X', '.'},}};

};

class L_block: public Piece{
public:
    array<array<char, 3>, 3> piece =   {{{'.', 'X', '.'},
                                         {'.', 'X', '.'},
                                         {'.', 'X', 'X'},}};

};

class O_block: public Piece{
public:
    array<array<char, 3>, 3> piece =   {{{'X', 'X', '.'},
                                         {'X', 'X', '.'},
                                         {'.', '.', '.'},}};

};

class T_block: public Piece{
public:
    array<array<char, 3>, 3> piece   = {{{'.', 'X', '.'},
                                         {'X', 'X', '.'},
                                         {'.', 'X', '.'},}};

};

class S_block: public Piece{
public:
    array<array<char, 3>, 3> piece =  {{{'X', '.', '.'},
                                        {'X', 'X', '.'},
                                        {'.', 'X', '.'},}};

};