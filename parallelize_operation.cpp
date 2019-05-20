#include "parallelize_operation.hpp"

using namespace std;

vector<byteArray> parallelize_encryption(vector<byteArray> &plainText, byteArray &key, byteArray &randomArray, vector<byteArray> &counter){

    aes_operation aesObject(key);

    vector<byteArray> encryptedMessage(plainText.size(), vector<unsigned char>(KEY_BLOCK, 0x00));

    float microseconds = 0.0f;
	int pragmaPrivate = 0;
	for (int t = 2; t <= THREAD_COUNT; t += 2){

		for (int r = 0; r != ROUND; ++r){
			auto start_time = std::chrono::high_resolution_clock::now();
			
			// private: clause declares the variables in the list to be private to each thread in a team.
			// shared: clause declares the variables in the list to be shared among all the threads in a team. 
			//		All threads within a team access the same storage area for shared variables. 
			// num_threads: Number of Threads to invoke.
			#pragma omp parallel private(pragmaPrivate) shared(aesObject, encryptedMessage, counter, plainText) num_threads(t)
            {
				#pragma omp for 
				for (pragmaPrivate = 0; pragmaPrivate < plainText.size(); ++pragmaPrivate){
                    byteArray temp = aesObject.aesEncrypt(counter[pragmaPrivate], key);
					temp = xorOp2(temp, plainText[pragmaPrivate]);
                    encryptedMessage[pragmaPrivate] = temp;
				}

			}

			auto end_time = std::chrono::high_resolution_clock::now();
			auto time = end_time - start_time;
			microseconds += std::chrono::duration_cast<std::chrono::microseconds>(time).count();
		}

		cout << t << " Threads - Encrypted Duration: " << microseconds / (1000.0f * ROUND) << endl;
		microseconds = 0.0f;
	}

	return encryptedMessage;
}

vector<byteArray> parallelize_decryption(vector<byteArray> &encryptedData, byteArray &key, byteArray &randomArray, vector<byteArray> &counter){
    aes_operation aesObject(key);
	int pragmaPrivate = 0;
    vector<byteArray> decryptedMessage(encryptedData.size(), vector<unsigned char>(KEY_BLOCK, 0x00));
    float microseconds = 0.0f;

	for (int t = 2; t <= THREAD_COUNT; t += 2){
		for (int r = 0; r != ROUND; ++r){
			auto start_time = std::chrono::high_resolution_clock::now();
			
			// private: clause declares the variables in the list to be private to each thread in a team.
			// shared: clause declares the variables in the list to be shared among all the threads in a team. 
			//		All threads within a team access the same storage area for shared variables. 
			// num_threads: Number of Threads to invoke.
			#pragma omp parallel private(pragmaPrivate) shared(aesObject, decryptedMessage, counter, encryptedData) num_threads(t)
            {
				#pragma omp for 
				for (pragmaPrivate = 0; pragmaPrivate < encryptedData.size(); ++pragmaPrivate){
                    byteArray temp = aesObject.aesDecrypt(counter[pragmaPrivate], key);
					temp = xorOp2(temp, encryptedData[pragmaPrivate]);
                    decryptedMessage[pragmaPrivate] = temp;
				}
			}

			auto end_time = std::chrono::high_resolution_clock::now();
			auto time = end_time - start_time;
			microseconds += std::chrono::duration_cast<std::chrono::microseconds>(time).count();
		}

		cout << t << " Threads - Decrypted Duration: " <<  microseconds / (1000.0f * ROUND) << endl;
		microseconds = 0.0f;
	}

    return decryptedMessage;
}

void testerFunction2(){
    cout << "Echo Bravo Charlie" << endl;
}