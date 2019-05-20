#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <array>
#include <vector>

#include "project_utilities.hpp"
#include "counter_mode.hpp"
#include "parallelize_operation.hpp"

#include <string>

using namespace std;

int main(int argc, char** argv){
    cout << "Parallel Encryption & Decryption with AES started" << endl;

    string outputFile;
    string messageFile;
    string keyFile;
    // Check Args Parsed
    bool isArgsCorrect = checkArgumentParser(argc, argv, outputFile, messageFile, keyFile);
    if(!isArgsCorrect){
        return -1;
    }

    // Read Key
    vector<unsigned char> keyData = readKey(keyFile);
    printByteArray(keyData, "Key");

    // read Plain Text
    vector<vector <unsigned char>> messageData = readMessageFile(messageFile);

    printBigHiphen("Converting Message to Byte Array Start");
    for(int i = 0; i < messageData.size(); i++){
        printByteArray(messageData[i], "Message");
    }
    printBigHiphen("Converting Message to Byte Array End");

    // Get Random byte Array
    vector<unsigned char> randomArray = getRandomByteArray(10);
    printByteArray(randomArray, "IV Array");

    // Generate Counters for that Random Array
    vector<vector <unsigned char>> counters(messageData.size(), vector<unsigned char> (KEY_BLOCK, 0x00));
    generateCounter(counters, randomArray);

    printBigHiphen("Random Nounce Calculation Start: ");
    for(int i = 0; i < counters.size(); i++){
        printByteArray(counters[i], "Counter");
    }
    printBigHiphen("Random Nounce Calculation End: ");
    
    // Get Encrypted Data
    vector<vector <unsigned char>> encryptedData = parallelize_encryption(messageData, keyData, randomArray, counters);

    printBigHiphen("Encrypted Message to Byte Array Start");
    for(int i = 0; i < encryptedData.size(); i++){
        printByteArray(encryptedData[i], "Message");
    }
    printBigHiphen("Encrypted Message to Byte Array End");

    // Get Decrypted Data
    vector<vector <unsigned char>> decryptedData = parallelize_decryption(encryptedData, keyData, randomArray, counters);
    printBigHiphen("Decrypted Message to Byte Array Start");
    for(int i = 0; i < decryptedData.size(); i++){
        printByteArray(decryptedData[i], "Message");
    }
    printBigHiphen("Decrypted Message to Byte Array End");

    printHiphen();
    return 0;
}