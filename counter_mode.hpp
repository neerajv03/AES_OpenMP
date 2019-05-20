#pragma once



#include <vector>
#include <string>
#include <iostream>

#include "project_utilities.hpp"
#include "aes_class.hpp"
using namespace std;


ByteArray incrmentCounter(const ByteArray &start_counter, const unsigned int &round);


void generateCounter(vector<ByteArray> &ctrs, const ByteArray &IV);