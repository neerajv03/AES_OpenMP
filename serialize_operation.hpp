#define ROUND 10
#include <vector>

using namespace std;

typedef vector<unsigned char> byteArray;


vector<byteArray> serialize_encryption(vector<byteArray> &plainText, byteArray &key, byteArray &randomArray, vector<byteArray> &counter);
vector<byteArray> serialize_decryption(vector<byteArray> &encryptedData, byteArray &key, byteArray &randomArray, vector<byteArray> &counter);
void testerFunction2();