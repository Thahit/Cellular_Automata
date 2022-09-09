#include <iostream>
#include <unistd.h>

const int size = 24;//board size

void show_board(int board[size][size]){
    int len = size*2+3;

    for(int i = 0; i<len; i++){//border
        std::cout << "-";
    }
    std::cout << std::endl;

    for(int i = 0; i < size; i++){
        std::cout << "|";
        for(int j = 0; j < size; j++){
            if(board[i][j]==1){
                std::cout << " x";
            }
            else{std::cout << "  ";}
        }
        std::cout <<" |" << std::endl;
    }

    for(int i = 0; i<len; i++){//border
        std::cout << "-";
    }
    std::cout << std::endl;
}


int rule_set(int own_state, int num_alive){
    if((own_state == 0 && num_alive==2) || num_alive ==3){
        return 1;
    }
    return 0;
}

int** step(int board[size][size]){
    /**
     * Updates the board according to set rules
     * 
     * @param board[size][size] = input board to be updated
     * 
     */
    int num_alive;
    int** new_board[size][size];// need a 2. board to not mess with having new and old cells at the same time
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            // count alive neighbours
            num_alive = 0 - board[i][j];// because the own state is also looked at when counting neighbours
            for(int k = -1; k<2; k++){
                for(int l = -1; l<2; l++){
                    num_alive += board[(i+k)%size][(j+l)%size];//if we would go out of the board we reenter on the other side
                }
            }

            new_board[i][j] = rule_set(board[i][j], num_alive);
        }
    }
    return new_board;
}

void play(int board[size][size], int num_iter){
    /**
     * Plays the game of life with the input board
     * 
     * @param board[size][size] = board to play with
     * @param num_iter = number of iterations
     * 
     */
    show_board(board);//show init board

    for(int i = 0; i < num_iter; i++){
        step(board);

        show_board(board);

        // wait
        sleep(2);
    }
}

void fill_random(int board[size][size], float frac){
    /**
     * Fills the input board randomly with dead and alive cells
     * 
     * @param board[size][size] = input board to be filled
     * @param frac = the approximate fraction of spaces to be filled with alive cells
     * 
     */
    float random_number;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            random_number = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            if (random_number < frac){
                board[i][j] = 1;
            }
        }
    }
}

int main(){
    int board[size][size];

    fill_random(board, .1);

    play(board, 3);
    return 0;
}