#include <iostream>

template<typename T, size_t n>
void printArray(T const(& arr)[n])
{
    for (size_t i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n";
}

int * step(int *arr){   
    int n = sizeof(arr)/sizeof(arr[0]);
    static int output [8]={0,0,0,0,0,0,0,0};
    for (size_t i = 0; i < n; i++) {
        int neighbours =0;
        for (int y = 0; y < 3; y++){
            int neigh = (i-1+y) %n;
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
    int world [8] = {1,1,1,0,1,0,1,1};
    printArray(world);
    int *pWorld = step(world);
    for (size_t round = 0; round < 20; round++)
    {
        int *pWorld = step(pWorld);

        for (size_t i = 0; i < 8; i++) {
            std::cout << pWorld[i] << ' ';
        }
        std::cout << '\n';
    }
    
    return 0;
}