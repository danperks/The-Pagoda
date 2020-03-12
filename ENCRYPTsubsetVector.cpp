/*
Title: Encryption (Encrypt) for Client/Server Communication
Author: Daniel J Chalmers
Date: 27/02/20 - 30/02/20
Part of BSc Computer Science, Module 4007CEM: Activity Led Learning, Coventry University
Project Co-Authors: Daniel Perks, Harrison Duffield, Robert Crabtree
For integration with 'DECRYPT', 'Server' and 'Client' .cpp files
***EXECUTION IN ISOLAION REQUIRES INPUTTED DATA (nothing imported)***
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace std;


string encode(string characterParamater, int length, string encodedString, char subsetArray[][9], int rows, int cols)
{
	vector<char> characters(characterParamater.begin(), characterParamater.end());
	for (int i = 0; i < characters.size(); i++)
	{
		cout << characters.at(i) << "";
	}
	for (int i = 0; i < length; ++i)
	{
		for (int k = 0; k < (cols +  1); ++k)
		{
			for (int j = 0; j < (rows + 1); ++j)
			{
				if (characters[i] == subsetArray[j][k])
				{
					string subset = to_string(j + 1);
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
			}
		}
	}
	return encodedString;
}

void setArguments(string characterParameter, int a, int b, int* length, int *rows, int *cols)
{
	*length = characterParameter.size();
	*rows = a;
	*cols = b;
}

int main()
{
	string strInput;
	cout << "Enter your string\n>";
	getline(cin, strInput);
	vector<char> charactersPlaceholder(strInput.begin(), strInput.end());
	string encodedString;
	random_device randomDevice;
	mt19937 pseudoRandom(randomDevice()); // mt19937 type = pseudorandom generator of 32-bit numbers (state size of 19937 bits)
	uniform_int_distribution<> randomSubset(3,4); // Define range
	uniform_int_distribution<> randomChecksum(10000, 99999);
	int checksum = randomChecksum(pseudoRandom);
	int alphabetSubset = randomSubset(pseudoRandom);
	bool runningValue;
	runningValue = true;
	encodedString.append(to_string(alphabetSubset));
	encodedString.append(to_string(checksum));
	string characterArgument(charactersPlaceholder.begin(), charactersPlaceholder.end());

	while (runningValue == true)
	{
		if (alphabetSubset == 3)
		{
			int length, rows, cols;
			setArguments(characterArgument, 8, 9, &length, &rows, &cols);
			char subsetArray[8][9] = { {'A','B','C','D','E','F','G','H','I'}, {'J','K','L','M','N','O','P','Q','R'},
										{'S','T','U','V','W','X','Y','Z',' '}, { '.',',','?','!','%','-','+','0','1'},
										{'2','3','4','5','6','7','8','9','a'}, {'b','c','d','e','f','g','h','i','j'},
										{'k','l','m','n','o','p','q','r','s'}, {'t','u','v','w','x','y','z','\''} };
			string encoded = encode(characterArgument, length, encodedString, subsetArray, rows, cols);
			cout << encoded;
			runningValue = false;
		}
		else if (alphabetSubset == 4)
		{
			int length, rows, cols;
			setArguments(characterArgument, 9, 8, &length, &rows, &cols);
			char subsetArray[9][9] = { {'A','B','C','D','E','F','G','H'}, {'I','J','K','L','M','N','O','P'}, {'Q','R','S','T','U','V','W','X'},
										{'Y','Z',' ','.',',','?','!','%'}, {'-','+','0','1','2','3','4','5'}, {'6','7','8','9','a','b','c','d'},
										{'e','f','g','h','i','j','k','l'}, {'m','n','o','p','q','r','s','t'}, {'u','v','w','x','y','Z','\''} };
			string encoded = encode(characterArgument, length, encodedString, subsetArray, rows, cols);
			cout << encoded;
			runningValue = false;
		}
	}
	//cout << encoded;
}


