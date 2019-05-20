
#include <vector>
#include <string>
#include <iostream>

#include "project_utilities.hpp"
#include "aes_class.h"
using namespace std;


byteArray incrmentCounter(const byteArray &start_counter, const unsigned int &round);


void generateCounter(vector<byteArray> &ctrs, const byteArray &IV);