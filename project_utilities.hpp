
#include <vector>
#include <iostream>
#include <bitset>
#include <string>
#define KEY_BLOCK 16

using namespace std;
typedef vector<unsigned char> byteArray;

// Reading data from file
const vector<byteArray> readMessageFile(const string &fileName);
const byteArray readKey(const string &fileName);

// Args Parser
bool checkArgumentParser(int argsLength, char** argument, string &outputFile, string &messageFile, string &keyFile);

// To get Random Byte array for IV + counter encryption
const byteArray getRandomByteArray(const unsigned int &length);

// Xor Operations for the Encryption
void xorOperation(byteArray &message, byteArray &key, int length);
byteArray xorOp2(byteArray &message1, byteArray &message2);


// Functions for printing and testing
void printHiphen();
void printByteArray(byteArray &arr, string fileType);
void printBigHiphen(string textMessage);
void testFunction();

bool checkByteArray(vector <byteArray> &message1, vector <byteArray> &message2);