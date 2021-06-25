#include <iostream>

const int size = 30;

template<typename T, size_t n>
void printArray(T const(& arr)[n]){
    for (size_t i = 0; i < size; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n";
}

int * step(int *arr){   
    static int output [size]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for (size_t i = 0; i < size; i++) {
        int neighbours =0;
        for (int y = 0; y < 3; y++){
            int neigh = (i-1+y) %size;
            if ( arr[neigh]==1){
                neighbours +=1;
            }
        }
        if (neighbours==3)
        {
            output[i]=0;
        }else{
            output[i]=1;
        }
    }
    return output;
}

int main(){
    int world [size] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    printArray(world);
    int *pWorld = step(world);
    for (size_t round = 0; round < 20; round++)
    {
        int *pWorld = step(pWorld);

        for (size_t i = 0; i < size; i++) {
            std::cout << pWorld[i] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}