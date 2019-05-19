#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <array>
#include <vector>

#include "constant.hpp"
#include "project_utilities.hpp"

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

    printBigHiphen();
    for(int i = 0; i < messageData.size(); i++){
        printByteArray(messageData[i], "Message");
    }
    printBigHiphen();

    return 0;
}