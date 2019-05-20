#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <array>
#include <vector>
#include <string>

#include "project_utilities.hpp"
#include "counter_mode.hpp"
#include "serialize_operation.hpp"

using namespace std;

int main(int argc, char** argv){
    cout << "Serial Encryption & Decryption with AES started" << endl;

    string outputFile;
    string messageFile;
    string keyFile;

    // Check Args Parsed
    bool isArgsCorrect = checkArgumentParser(argc, argv, outputFile, messageFile, keyFile);
    if(!isArgsCorrect){
        return -1;
    }

    // Get Key
    vector<unsigned char> keyData = readKey(keyFile);
    printByteArray(keyData, "Key");

    // Get Message Data
    vector<vector <unsigned char>> messageData = readMessageFile(messageFile);

    printBigHiphen("Converting Message to Byte Array Start");
    for(int i = 0; i < messageData.size(); i++){
        printByteArray(messageData[i], "Message");
    }
    printBigHiphen("Converting Message to Byte Array End");

    // Generate and get Random Data
    vector<unsigned char> randomArray = getRandomByteArray(10);
    printByteArray(randomArray, "IV Array");

    // Generate Counters for encryption
    vector<vector <unsigned char>> counters(messageData.size(), vector<unsigned char> (KEY_BLOCK, 0x00));
    generateCounter(counters, randomArray);
    printBigHiphen("Random Nounce Calculation Start: ");
    for(int i = 0; i < counters.size(); i++){
        printByteArray(counters[i], "Counter");
    }
    printBigHiphen("Random Nounce Calculation End: ");

    // Encrypt Data
    vector<vector <unsigned char>> encryptedData = serialize_encryption(messageData, keyData, randomArray, counters);

    printBigHiphen("Encrypted Message to Byte Array Start");
    for(int i = 0; i < encryptedData.size(); i++){
        printByteArray(encryptedData[i], "Message");
    }
    printBigHiphen("Encrypted Message to Byte Array End");

    // Decrypt Data
    vector<vector <unsigned char>> decryptedData = serialize_decryption(encryptedData, keyData, randomArray, counters);
    printBigHiphen("Decrypted Message to Byte Array Start");
    for(int i = 0; i < decryptedData.size(); i++){
        printByteArray(decryptedData[i], "Message");
    }
    printBigHiphen("Decrypted Message to Byte Array End");

    printHiphen();

    bool isEqual = checkByteArray(messageData, decryptedData);

    if(!isEqual)
        cout << "Message and Decrypted data not matching" << endl;
    else
        cout << "Message and Decrypted data macthes" << endl;

    testerFunction2();
    return 0;
}