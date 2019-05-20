#pragma once

#include <vector>
#include <iostream>
#include <bitset>
#include <string>
#define KEY_BLOCK 16

using namespace std;
typedef vector<unsigned char> ByteArray;

const vector<ByteArray> readMessageFile(const string &fileName);

const ByteArray readKey(const string &fileName);

void printByteArray(ByteArray &arr, string fileType);

bool checkArgumentParser(int argsLength, char** argument, string &outputFile, string &messageFile, string &keyFile);

const ByteArray getRandomByteArray(const unsigned int &length);


void printHiphen();

void printBigHiphen(string textMessage);

void testFunction();

void xorOperation(ByteArray &message, ByteArray &key, int length);
