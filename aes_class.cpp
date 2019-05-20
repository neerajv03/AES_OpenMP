#include "aes_class.hpp"
#include "project_utilities.hpp"
#include "constant.hpp"

using namespace std;


aes_operation::aes_operation(byteArray key): key(key){
    printHiphen();
    cout << "AES Object Created" << endl;
}


vector<byteArray> aes_operation::aesEncrypt(vector<byteArray> messageData, byteArray key){
    return messageData;

}


vector<byteArray> aes_operation::aesDecrypt(vector<byteArray> encryptedData, byteArray key){
    return encryptedData;
}


byteArray aes_operation::keyExpansion(byteArray keyData){
    keyData;
}


byteArray aes_operation::computeSubKeys(byteArray &prev_subkey, const int &round){
	byteArray result(KEY_BLOCK);

	result[0] = (prev_subkey[0] ^ (sBox[prev_subkey[13]] ^ RC[round]));
	result[1] = (prev_subkey[1] ^ sBox[prev_subkey[14]]);
	result[2] = (prev_subkey[2] ^ sBox[prev_subkey[15]]);
	result[3] = (prev_subkey[3] ^ sBox[prev_subkey[12]]);

	for (int i = 4; i != KEY_BLOCK; i += 4){
		result[i + 0] = (result[i - 4] ^ prev_subkey[i + 0]);
		result[i + 1] = (result[i - 3] ^ prev_subkey[i + 1]);
		result[i + 2] = (result[i - 2] ^ prev_subkey[i + 2]);
		result[i + 3] = (result[i - 1] ^ prev_subkey[i + 3]);
	}

	return result;
}

void aes_operation::keyAddition(byteArray &message, int round){
    xorOperation(message, keys[round], KEY_BLOCK);
}


void aes_operation::subBytes(byteArray &message){

}   


byteArray aes_operation::mulRows(byteArray data){
    data;
}


byteArray aes_operation::shiftColumn(byteArray data){
    data;
}


void aes_operation::keySchedule(){
	for (int round = 0; round != ROUND + 1; round++){
		if (round == 0)
			keys[round] = key;
		else
			keys[round] = computeSubKeys(keys[round - 1], round - 1);	
	}
}