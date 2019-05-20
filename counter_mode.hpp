#include <vector>
#include <string>
#include <iostream>

#include "project_utilities.hpp"
#include "aes_class.h"

using namespace std;

// Adds 1 to the random array by doing a left shift by 8 bits
byteArray incrmentCounter(const byteArray &start_counter, const unsigned int &round);

// Generated Counter
void generateCounter(vector<byteArray> &ctrs, const byteArray &IV);