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

int main()
{
	string strInput;
	cout << "Enter your string\n>";
	getline(cin, strInput);
	transform(strInput.begin(), strInput.end(), strInput.begin(), ::toupper);
	vector<char> characters(strInput.begin(), strInput.end());
	string encodedString;

	random_device randomDevice;
	mt19937 pseudoRandom(randomDevice()); // mt19937 type = pseudorandom generator of 32-bit numbers (state size of 19937 bits)
	uniform_int_distribution<> randomSubset(3, 6); // Define range
	uniform_int_distribution<> randomChecksum(10000, 99999);
	int checksum = randomChecksum(pseudoRandom);
	int alphabetSubset = randomSubset(pseudoRandom);
	//cout << "Checksum = " << checksum << "\n";
	//cout << "alphabetSubset = " << alphabetSubset << "\n";
	encodedString.append(to_string(alphabetSubset));
	encodedString.append(to_string(checksum));


	if (alphabetSubset == 3)
	{
		char subset1[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };
		char subset2[] = { 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R' };
		char subset3[] = { 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ' };
		char subset4[] = { '.', ',', '?', '!', '%', '-', '+', '0', '1' };
		char subset5[] = { '2', '3', '4', '5', '6', '7', '8', '9' };
		int length = characters.size();
		for (int i = 0; i < length; ++i)
		{
			for (int k = 0; k < 10; ++k)
			{
				if (characters[i] == subset1[k])
				{
					string subset = "1";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset2[k])
				{
					string subset = "2";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset3[k])
				{
					string subset = "3";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset4[k])
				{
					string subset = "4";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset5[k])
				{
					string subset = "5";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
			}
		}

	}
	else if (alphabetSubset == 4)
	{
		char subset1[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
		char subset2[] = { 'H', 'I', 'J', 'K', 'L', 'M', 'N' };
		char subset3[] = { 'O', 'P', 'Q', 'R', 'S', 'T', 'U' };
		char subset4[] = { 'V', 'W', 'X', 'Y', 'Z', ' ', '.' };
		char subset5[] = { ',', '?', '!', '%', '-', '+', '0' };
		char subset6[] = { '1', '2', '3', '4', '5', '6', '7' };
		char subset7[] = { '8', '9' };
		int length = characters.size();
		for (int i = 0; i < length; ++i)
		{
			for (int k = 0; k < 8; ++k)
			{
				if (characters[i] == subset1[k])
				{
					string subset = "1";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset2[k])
				{
					string subset = "2";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset3[k])
				{
					string subset = "3";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset4[k])
				{
					string subset = "4";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset5[k])
				{
					string subset = "5";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset6[k])
				{
					string subset = "6";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset7[k])
				{
					string subset = "7";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
			}
		}

	}
	else if (alphabetSubset == 5)
	{
		char subset1[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
		char subset2[] = { 'G', 'H', 'I', 'J', 'K', 'L' };
		char subset3[] = { 'M', 'N', 'O', 'P', 'Q', 'R' };
		char subset4[] = { 'S', 'T', 'U', 'V', 'W', 'X' };
		char subset5[] = { 'Y', 'Z', ' ', '.', ',', '?' };
		char subset6[] = { '!', '%', '-', '+', '0', '1' };
		char subset7[] = { '2', '3', '4', '5', '6', '7' };
		char subset8[] = { '8', '9' };
		int length = characters.size();
		for (int i = 0; i < length; ++i)
		{
			for (int k = 0; k < 7; ++k)
			{
				if (characters[i] == subset1[k])
				{
					string subset = "1";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset2[k])
				{
					string subset = "2";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset3[k])
				{
					string subset = "3";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset4[k])
				{
					string subset = "4";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset5[k])
				{
					string subset = "5";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset6[k])
				{
					string subset = "6";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset7[k])
				{
					string subset = "7";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset8[k])
				{
					string subset = "8";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
			}
		}

	}
	else if (alphabetSubset == 6)
	{
		char subset1[] = { 'A', 'B', 'C', 'D', 'E' };
		char subset2[] = { 'F', 'G', 'H', 'I', 'J' };
		char subset3[] = { 'K', 'L', 'M', 'N', 'O' };
		char subset4[] = { 'P', 'Q', 'R', 'S', 'T' };
		char subset5[] = { 'U', 'V', 'W', 'X', 'Y' };
		char subset6[] = { 'Z', ' ', '.', ',', '?' };
		char subset7[] = { '!', '%', '-', '+', '0' };
		char subset8[] = { '1', '2', '3', '4', '5' };
		char subset9[] = { '6', '7', '8', '9' };
		int length = characters.size();
		for (int i = 0; i < length; ++i)
		{
			for (int k = 0; k < 7; ++k)
			{
				if (characters[i] == subset1[k])
				{
					string subset = "1";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset2[k])
				{
					string subset = "2";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset3[k])
				{
					string subset = "3";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset4[k])
				{
					string subset = "4";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset5[k])
				{
					string subset = "5";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset6[k])
				{
					string subset = "6";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset7[k])
				{
					string subset = "7";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset8[k])
				{
					string subset = "8";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
				else if (characters[i] == subset9[k])
				{
					string subset = "9";
					string index = to_string(k + 1);
					encodedString.append(subset);
					encodedString.append(index);
				}
			}
		}
	}
	cout << "\n" << encodedString << "\n";
}

// Written in Microsoft Visual Studio Community 2019