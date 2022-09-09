#include <iostream>
#include <unistd.h>

const int size = 32;//board size
const int radius = 1;//perception field of a cell

void show_board(int board[size][size]){
    /**
     * prints the gamestate
     * 
     * @param board = the gamestate to be visualized
     */
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
    /**
     * ruleset of the original "game of life"
     * 
     * @param own_state = 1 if the sell is alive or 0 if it's dead
     * @param num_alive = number of neighbours who are alive
     * 
     * @return 1 if cell is alive in the next timestep and 0 if it is not
     */
    if((own_state == 0 && num_alive==2) || num_alive ==3){
        return 1;
    }
    return 0;
}

void step(int board[size][size]){
    /**
     * Updates the board according to set rules
     * 
     * @param board[size][size] = input board to be updated
     */
    int num_alive;
    int temp_board[size][size];
    std::copy(&board[0][0], &board[0][0]+size*size,&temp_board[0][0]);// need a 2. board to not mess with having new and old cells at the same time
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            // count alive neighbours
            num_alive = 0 - temp_board[i][j];// because the own state is also looked at when counting neighbours
            for(int k = -radius; k<=radius; k++){
                for(int l = -radius; l<=radius; l++){
                    num_alive += temp_board[(i+k)%size][(j+l)%size];//if we would go out of the board we reenter on the other side
                }
            }

            board[i][j] = rule_set(temp_board[i][j], num_alive);
        }
    }
}

void play(int board[size][size], int num_iter){
    /**
     * Plays the game of life with the input board
     * 
     * @param board[size][size] = board to play with
     * @param num_iter = number of iterations
     */
    show_board(board);//show init board

    for(int i = 0; i < num_iter; i++){
        // wait
        sleep(1);

        step(board);
        show_board(board);
    }
}

void fill_random(int board[size][size], float frac){
    /**
     * Fills the input board randomly with dead and alive cells
     * 
     * @param board[size][size] = input board to be filled
     * @param frac = the approximate fraction of spaces to be filled with alive cells
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

    fill_random(board, .05);

    play(board, 100);
    return 0;
}