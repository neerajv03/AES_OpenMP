#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <omp.h>
#include <inttypes.h>
#include <chrono>

#include "parallelize_operation.hpp"
#include "project_utilities.hpp"
#include "aes_class.h"


#define KEY_BLOCK 16

using namespace std;

vector<byteArray> parallelize_encryption(vector<byteArray> &plainText, byteArray &key, byteArray &randomArray, vector<byteArray> &counter){

    aes_operation aesObject(key);

    vector<byteArray> encryptedMessage(plainText.size(), vector<unsigned char>(KEY_BLOCK, 0x00));

    float microseconds = 0.0f;

	for (int t = 2; t != THREAD_COUNT; t += 2){
		cout << endl << "OpenMP (" << t << " Threads) - Encrypted Duration  ";

		for (int r = 0; r != ROUND; ++r){
			auto start_time = std::chrono::high_resolution_clock::now();
			
			#pragma omp parallel private(i) shared(aesObject, encryptedMessage, counter, plainText) num_threads(t)
            {
				#pragma omp for 
				for (int i = 0; i < plainText.size(); ++i){
                    byteArray temp = aesObject.aesEncrypt(counter[i], key);
					temp = xorOp2(temp, plainText[i]);
                    encryptedMessage[i] = temp;
				}

			}

			auto end_time = std::chrono::high_resolution_clock::now();
			auto time = end_time - start_time;
			microseconds += std::chrono::duration_cast<std::chrono::microseconds>(time).count();
		}

		cout << microseconds / (1000.0f * ROUND) << endl;
		microseconds = 0.0f;
	}

	return encryptedMessage;
}

vector<byteArray> parallelize_decryption(vector<byteArray> &encryptedData, byteArray &key, byteArray &randomArray, vector<byteArray> &counter){
    aes_operation aesObject(key);

    vector<byteArray> decryptedMessage(encryptedData.size(), vector<unsigned char>(KEY_BLOCK, 0x00));
    float microseconds = 0.0f;

	for (int t = 2; t != THREAD_COUNT; t += 2){
		cout << endl << "OpenMP (" << t << " Threads) - Encrypted Duration  ";

		for (int r = 0; r != ROUND; ++r){
			auto start_time = std::chrono::high_resolution_clock::now();
			
			#pragma omp parallel private(i) shared(aesObject, decryptedMessage, counter, encryptedData) num_threads(t)
            {
				#pragma omp for 
				for (int i = 0; i < encryptedData.size(); ++i){
                    byteArray temp = aesObject.aesDecrypt(counter[i], key);
					temp = xorOp2(temp, encryptedData[i]);
                    decryptedMessage[i] = temp;
				}

			}

			auto end_time = std::chrono::high_resolution_clock::now();
			auto time = end_time - start_time;
			microseconds += std::chrono::duration_cast<std::chrono::microseconds>(time).count();
		}

		cout << microseconds / (1000.0f * ROUND) << endl;
		microseconds = 0.0f;
	}

    return decryptedMessage;
    
}

void testerFunction2(){
    cout << "Echo Bravo Charlie" << endl;
}