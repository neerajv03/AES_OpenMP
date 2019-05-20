#ifndef aes_operation_H
#define aes_operation_H

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#define ROUND 10
#define SUBKEYS 11

using namespace std;

typedef vector<unsigned char> byteArray;

class aes_operation  {

    public:
    aes_operation(byteArray passedKey);

    byteArray aesEncrypt(byteArray messageData, byteArray key);
    byteArray aesDecrypt(byteArray encryptedData, byteArray key);

    private:
    byteArray key;
    vector<byteArray> keys;

    byteArray keyExpansion(byteArray keyData);

    void keySchedule();
    void keyAddition(byteArray &message, int round);
    void subBytes(byteArray &message);
    void subBytesInv(byteArray &encryptedMessage);
    void shiftRows(byteArray &message);
    void shiftRowsInvert(byteArray &encryptedMessage);
    void mixColumns(byteArray &message);
    void mixColumnsInvert(byteArray &encryptedMessage);
    byteArray computeSubKeys(byteArray &prev_subkey, const int &round);

};

#endif