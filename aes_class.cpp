#include "aes_class.h"
#include "project_utilities.hpp"
#include "constant.hpp"

using namespace std;


aes_operation::aes_operation(byteArray passedKey) : keys(SUBKEYS){
	key = passedKey;
	printByteArray(key, "Key Test");
    printHiphen();
    cout << "AES Object Created" << endl;
	keySchedule();
}


byteArray aes_operation::aesEncrypt(byteArray messageData, byteArray key){
	int i = 0, round = 0;
	byteArray message = messageData;

	keyAddition(message, round);
	round = 1;

	for (round; round != 10; ++round)	{
		subBytes(message);
		shiftRows(message);
		mixColumns(message);
		keyAddition(message, round);
	}

	// Last round without Mix-Column (RNUM_ROUNDS)
	round = 10;
	subBytes(message);
	shiftRows(message);
	keyAddition(message, round);

	return message;
}


byteArray aes_operation::aesDecrypt(byteArray encryptedData, byteArray key){
    return encryptedData;
}


void aes_operation::keyAddition(byteArray &message, int round){
	//printBigHiphen("Key Addition");
    xorOperation(message, keys[round], KEY_BLOCK);
}


// Substituing for the components present in sBox Constant
void aes_operation::subBytes(byteArray &message){
	//printBigHiphen("Sub Bytes");
	for (int i = 0; i < KEY_BLOCK; i++){
		message[i] = sBox[message[i]];
	}
}   


void aes_operation::shiftRows(byteArray &message){
	//printBigHiphen("Shift Rows");
	byteArray tmp(KEY_BLOCK);

	tmp[0] = message[0];
	tmp[1] = message[5];
	tmp[2] = message[10];
	tmp[3] = message[15];

	tmp[4] = message[4];
	tmp[5] = message[9];
	tmp[6] = message[14];
	tmp[7] = message[3];

	tmp[8] = message[8];
	tmp[9] = message[13];
	tmp[10] = message[2];
	tmp[11] = message[7];

	tmp[12] = message[12];
	tmp[13] = message[1];
	tmp[14] = message[6];
	tmp[15] = message[11];

	message = tmp;
}


void aes_operation::mixColumns(byteArray &message){
	//printBigHiphen("Mix Columns");
	unsigned char b0, b1, b2, b3;

	for (int i = 0; i < KEY_BLOCK; i += 4){
		b0 = message[i + 0];
		b1 = message[i + 1];
		b2 = message[i + 2];
		b3 = message[i + 3];

		message[i + 0] = mul[b0][0] ^ mul[b1][1] ^ b2 ^ b3;
		message[i + 1] = b0 ^ mul[b1][0] ^ mul[b2][1] ^ b3;
		message[i + 2] = b0 ^ b1 ^ mul[b2][0] ^ mul[b3][1];
		message[i + 3] = mul[b0][1] ^ b1 ^ b2 ^ mul[b3][0];
	}
}


void aes_operation::keySchedule(){
	//printBigHiphen("Key Schedule");
	for (int round = 0; round < 11; round++){
		if (round == 0){
			keys[round] = key;
		}
		else
			keys[round] = computeSubKeys(keys[round - 1], round - 1);	
	}
}


byteArray aes_operation::computeSubKeys(byteArray &prev_subkey, const int &round){
	//printBigHiphen("Compute Sub Keys");
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