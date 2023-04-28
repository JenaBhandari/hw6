#ifndef HASH_H
#define HASH_H


#include <cstdlib>
#include <string>

using namespace std;
#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }

		// A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				if (letter >= 'a' && letter <= 'z')
				{
					return (letter - 'a');
				}
				else if (letter >= '0' && letter <= '9') 
				{
					return (letter - '0' + 26);
				}
				else
				{
					throw std::invalid_argument("Invalid character: " + letter);
				}
    }

    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
				std::string edit = k;
				for (int i = 0; i < edit.size(); i++) {
        		if (edit[i] >= 'A' && edit[i] <= 'Z')
						{
							edit[i] += 'a' - 'A';
						}
    		}


				std::string zeros = "aaaaa";

				unsigned long long w[] = {0,0,0,0,0};

				int i = 4;

				while (edit.size() > 0)
				{
					std::string group;
					if (edit.size() >= 6)
					{
						group = edit.substr(edit.size() - 6, edit.size());
						edit = edit.substr(0, edit.size() - 6);
					}
					else
					{
						group = zeros.substr(0, 6 - edit.size()) + edit;
						edit = "";
					}

					w[i] = (36*36*36*36*36 * letterDigitToNumber(group[0])) +
					(36*36*36*36 * letterDigitToNumber(group[1])) +
					(36*36*36 * letterDigitToNumber(group[2])) +
					(36*36 * letterDigitToNumber(group[3])) +
					(36 * letterDigitToNumber(group[4])) + 
					(letterDigitToNumber(group[5]));
					
					i--;

				}



				HASH_INDEX_T h = (rValues[0]*w[0]+rValues[1]*w[1]+rValues[2]*w[2]+rValues[3]*w[3]+rValues[4]*w[4]);

				return h;

    }


    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
