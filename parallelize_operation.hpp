#define ROUND 10
#define THREAD_COUNT 10

using namespace std;

typedef vector<unsigned char> byteArray;


vector<byteArray> parallelize_encryption(vector<byteArray> &plainText, byteArray &key, byteArray &randomArray, vector<byteArray> &counter);
vector<byteArray> parallelize_decryption(vector<byteArray> &encryptedData, byteArray &key, byteArray &randomArray, vector<byteArray> &counter);
void testerFunction2();