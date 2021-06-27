#include <iostream>
#include <map>
#include <bits/stdc++.h>

#include <algorithm>
#include <iterator>

const int size = 30;

void printArray(std::array<int,size>& arr){
    for (size_t i = 0; i < size; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n";
}

/**
 * deciding the outcome by counting the number of neighbours
**/
std::array<int,size> step_with_number_thresholds(std::array<int,size>& arr, int neighbourhood){   
    std::array<int,size> new_array ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    for (size_t i = 0; i < size; i++) {
        int num_neighbours = 0;
        for (size_t y = 0; y < neighbourhood; y++){

            int pos = (i - ((neighbourhood-1)/2) + y + size) % size;
            int neigh = arr[pos];
            if ( neigh == 1){
                num_neighbours += 1;
            }
        }
        if (num_neighbours == 3){
            new_array[i] = 0;
        }else{
            new_array[i] = 1;
        }
        
    }
    return  new_array;
}

/**
 * deciding the outcome by having ab outcome state for every combination
**/
int NewState(int left, int center, int right){
    std::vector<int> neighbours {left, center, right};
    std::map<std::vector<int>, int> state_map = {
        {{0,0,0}, 1},
        {{0,0,1}, 0},
        {{0,1,0}, 1},
        {{0,1,1}, 1},
        {{1,0,0}, 0},
        {{1,0,1}, 0},
        {{1,1,0}, 1},
        {{1,1,1}, 0},
    };
    return state_map[neighbours] ? state_map[neighbours]:0;
}

/**
 * deciding the outcome by counting the number of neighbours
**/
int * step_with_defined_for_all(int *arr){   
    static int output [size] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    for (size_t i = 0; i < size; i++) {
        output[i] = NewState(arr[(i-1) %size], arr[(i) %size], arr[(i+1) %size]);
    }
    return output;
}


int main(){
    std::array<int,size> world = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    std::cout << "Initial state:\n";
    printArray(world);
    int number_of_rounds = 10;
    int neighbourhood = 3;
    std::cout << "Simulation (number of rounds: " <<number_of_rounds  << "):\n";

    for (size_t round = 0; round < number_of_rounds; round++){
        world = step_with_number_thresholds(world, neighbourhood);
        printArray(world);
    }

    return 0;
}