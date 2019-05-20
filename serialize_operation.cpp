#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <omp.h>
#include <inttypes.h>
#include <chrono>

#include "project_utilities.hpp"
#include "aes_class.h"

#include "serialize_operation.hpp"


#define KEY_BLOCK 16

using namespace std;

vector<byteArray> serialize_encryption(vector<byteArray> &plainText, byteArray &key, byteArray &randomArray, vector<byteArray> &counter){

    aes_operation aesObject(key);

    vector<byteArray> encryptedMessage(plainText.size(), vector<unsigned char>(KEY_BLOCK, 0x00));

    float microseconds = 0.0f;

        auto start_time = std::chrono::high_resolution_clock::now();

		for (int r = 0; r != ROUND; ++r){
			
				for (int i = 0; i < plainText.size(); ++i){
                    byteArray temp = aesObject.aesEncrypt(counter[i], key);
					temp = xorOp2(temp, plainText[i]);
                    encryptedMessage[i] = temp;
				}
		}
        auto end_time = std::chrono::high_resolution_clock::now();
		auto time = end_time - start_time;
        microseconds += std::chrono::duration_cast<std::chrono::microseconds>(time).count();

		cout << microseconds / (1000.0f * ROUND) << endl;
	

	return encryptedMessage;
}

vector<byteArray> serialize_decryption(vector<byteArray> &encryptedData, byteArray &key, byteArray &randomArray, vector<byteArray> &counter){
    aes_operation aesObject(key);

    vector<byteArray> decryptedMessage(encryptedData.size(), vector<unsigned char>(KEY_BLOCK, 0x00));
    float microseconds = 0.0f;

    auto start_time = std::chrono::high_resolution_clock::now();
		for (int r = 0; r != ROUND; ++r){
            for (int i = 0; i < encryptedData.size(); ++i){
                byteArray temp = aesObject.aesDecrypt(counter[i], key);
                temp = xorOp2(temp, encryptedData[i]);
                decryptedMessage[i] = temp;
            }
		}
        auto end_time = std::chrono::high_resolution_clock::now();
        auto time = end_time - start_time;
        microseconds += std::chrono::duration_cast<std::chrono::microseconds>(time).count();

		cout << microseconds / (1000.0f * ROUND) << endl;	

    return decryptedMessage;
    
}

void testerFunction2(){
    cout << "Echo Bravo Charlie" << endl;
}