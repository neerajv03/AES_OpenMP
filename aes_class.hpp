#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#define ROUND 10

using namespace std;

typedef vector<unsigned char> byteArray;

class aes_operation{

    public:


    aes_operation(byteArray key);

    vector<byteArray> aesEncrypt(vector<byteArray> messageData, byteArray key);
    vector<byteArray> aesDecrypt(vector<byteArray> encryptedData, byteArray key);

    private:
    byteArray key;
    vector<byteArray> keys;

    byteArray keyExpansion(byteArray keyData);

    void keySchedule();
    void keyAddition(byteArray &message, int round);

    byteArray computeSubKeys(byteArray &prev_subkey, const int &round);

    void subBytes(byteArray &message);
    byteArray mulRows(byteArray data);
    byteArray shiftColumn(byteArray data);
};