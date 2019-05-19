#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <array>
#include <vector>

#include "constant.hpp"

using namespace std;

int main(int argc, char** argv){
    cout << "Encryption with AES started" << endl;

    char message[] = "This is a Test Message";

    char key[16] = { 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 23, 35, 56};

    

    for(int i = 0; i < 10; i++){
        cout << sBox[i] << endl;
    }

    return 0;
}