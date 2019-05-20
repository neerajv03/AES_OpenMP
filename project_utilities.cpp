
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <omp.h>

#include "project_utilities.hpp"

using namespace std;

// ---------------------------------------------------------------------//
// Reads the Message file from the file name and returns the byte array data.
const vector<byteArray> readMessageFile(const string &fileName){
	vector<byteArray> data;
	char act_char;
	unsigned int counter = 0;
	byteArray next_byte_array;
	ifstream infile;

	infile.open(fileName);

	while (!infile.eof()){
		if (counter < KEY_BLOCK){
			infile.get(act_char);
			next_byte_array.push_back(act_char);
			counter++;
		}
		else{
			data.push_back(next_byte_array);
			next_byte_array = {};
			counter = 0;
		}
	}

	infile.close();
	return data;
}


// ---------------------------------------------------------------------//
// Reads Key from a file and returns the key data as hex format
const byteArray readKey(const string &fileName){
	byteArray data;
	char act_char;
	unsigned int counter = 0;
	ifstream infile;

	infile.open(fileName);

	while (!infile.eof() && counter < KEY_BLOCK){
		infile.get(act_char);
		data.push_back(act_char);
		counter++;
	}

	infile.close();
	return data;
}


// ---------------------------------------------------------------------//
void printByteArray(byteArray &arr, string fileType){
    printHiphen();
    cout << fileType << ":" << endl;
	for (size_t i = 0; i != arr.size(); ++i){
		cout << hex << (int)arr[i] << "\t";
	}
	cout << endl << endl;
}


// ---------------------------------------------------------------------//
// Checks Arguments Passed to the file
bool checkArgumentParser(int argsLength, char** argument, string &outputFile, string &messageFile, string &keyFile){
        if(argsLength != 7){
            printHiphen();
            cout << "Argument Length value is: " << argsLength << endl;
            cout << "Run In the below format." << endl;
            cout << "./aes_encryption_parallelize -m message_file.txt -k key_file.txt -o output.txt" << endl;
            cout << "./aes_encryption_serialize -m message_file.txt -k key_file.txt -o output.txt" << endl;
            return false;
    }

    for(int i = 1; i < argsLength; i++){
        string tempArg = argument[i];

        if(tempArg.compare("-m") == 0){
            messageFile = argument[i+1];
        }
        else if(tempArg.compare("-k") == 0){
            keyFile = argument[i+1];
        }
        else if(tempArg.compare("-o") == 0){
            outputFile = argument[i + 1];
        }
        else{
            printHiphen();
            cout << "Error in input parameters. Please check parsed input variables" << endl;
            cout << "./aes_encryption_parallelize -m message_file.txt -k key_file.txt -o output.txt" << endl;
            cout << "./aes_encryption_serialize -m message_file.txt -k key_file.txt -o output.txt" << endl;            return false;
        }
        i +=1;
    }

    printHiphen();
    cout << "Files have been set" << endl;
    cout << "Message File: " << messageFile << endl;
    cout << "Key File: " << keyFile << endl;
    cout << "Encrypted output File: " << outputFile << endl;

    return true;
}


//---------------------------------------------------------------------//
// Random Byte Array Nounce added for counter.

const byteArray getRandomByteArray(const unsigned int &length){
    byteArray randomArray(length);

	random_device rd;
	mt19937 generator(rd());
    // Would have values 0 - F
	uniform_int_distribution<int> distribution(0, 16);

	for (size_t i = 0; i != randomArray.size(); ++i)
		randomArray[i] = (unsigned char)distribution(generator);
	
	return randomArray;
}


// ---------------------------------------------------------------------//
void xorOperation(byteArray &message, byteArray &key, int length){
    for(int i = 0; i < length; i++)
        message[i] ^= key[i];
}


byteArray xorOp2(byteArray &message1, byteArray &message2){
    byteArray res(message1.size());
    for (int i = 0; i != message1.size(); ++i)
        res[i] = message1[i] ^ message2[i];
    return res;
}

// ---------------------------------------------------------------------//
void printHiphen(){
    cout << "----------------------------------------" << endl;
}

// ---------------------------------------------------------------------//
void printBigHiphen(string textMessage){
    cout << "------------------" << textMessage << "------------------" << endl;
}

// ---------------------------------------------------------------------//
void testFunction(){
    printHiphen();
    cout << "Hi you are inside project utilities" << endl;
}

// ---------------------------------------------------------------------//
bool checkByteArray(vector <byteArray> &message1, vector <byteArray> &message2){
    if(message1.size() != message2.size())
        return false;


    for(int i = 0; i < message1.size();i++){
        byteArray message_1_i = message1[i];
        byteArray message_2_i = message1[i];

        for(int j = 0; j < message_1_i.size(); j++){
        if(message_1_i[j] != message_2_i[j])
            return false;
        }
    }
    return true;
}