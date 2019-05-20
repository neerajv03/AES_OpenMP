
#include <vector>
#include <iostream>
#include <bitset>
#include <string>
#define KEY_BLOCK 16

using namespace std;
typedef vector<unsigned char> byteArray;

const vector<byteArray> readMessageFile(const string &fileName);

const byteArray readKey(const string &fileName);

void printByteArray(byteArray &arr, string fileType);

bool checkArgumentParser(int argsLength, char** argument, string &outputFile, string &messageFile, string &keyFile);

const byteArray getRandomByteArray(const unsigned int &length);


void printHiphen();

void printBigHiphen(string textMessage);

void testFunction();

void xorOperation(byteArray &message, byteArray &key, int length);
