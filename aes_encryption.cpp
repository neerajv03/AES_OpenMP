#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <array>
#include <vector>

#include "constant.hpp"
#include "project_utilities.hpp"
#include "counter_mode.hpp"

#include <string>

using namespace std;
bool checkArgumentParser(int argsLength, char** argument, string &outputFile, string &messageFile, string &keyFile);

int main(int argc, char** argv){
    cout << "Encryption with AES started" << endl;

    string outputFile;
    string messageFile;
    string keyFile;

    bool isArgsCorrect = checkArgumentParser(argc, argv, outputFile, messageFile, keyFile);
    if(!isArgsCorrect){
        return -1;
    }

    vector<unsigned char> keyData = readKey(keyFile);
    printByteArray(keyData, "Key");

    vector<vector <unsigned char>> messageData = readMessageFile(messageFile);

    printBigHiphen("Converting Message to Byte Array Start");
    for(int i = 0; i < messageData.size(); i++){
        printByteArray(messageData[i], "Message");
    }
    printBigHiphen("Converting Message to Byte Array End");

    vector<unsigned char> randomArray = getRandomByteArray(10);
    printByteArray(randomArray, "IV Array");


    vector<vector <unsigned char>> counters(messageData.size(), vector<unsigned char> (KEY_BLOCK, 0x00));

    generateCounter(counters, randomArray);
    printBigHiphen("Random Nounce Calculation Start: ");
    for(int i = 0; i < counters.size(); i++){
        printByteArray(counters[i], "Counter");
    }
    printBigHiphen("Random Nounce Calculation End: ");

    return 0;
}