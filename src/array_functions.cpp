/*
 * functionstocomplete.cpp
 *
 *  Created on: 2/15/20
 *      Author:gabriel caicedo
 */

//============================================================================
//	stuff you will need
//============================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include "array_functions.h"
#include "constants.h"
#include "utilities.h"
#include <algorithm>

using namespace constants;
using namespace std;
//using namespace utilities;

struct entry { //struct used to store a word with the number of occurences
	string word = "";
	int number_occurences = 0;
};

entry g_array[constants::MAX_WORDS]; //global array of entries

void clearArray() {
	int size = getArraySize();
	for (int i = 0; i < size; i++) { //goes through each entry and 'resets' it
		g_array[i].word = "";
		g_array[i].number_occurences = 0;
	}

}

//TODO define a structure to track words and number of times they occur

//TODO add a global array of entry structs (global to this file)

//TODO add variable to keep track of next available slot in array

//TODO define all functions in header file

std::string fileName = "testdata_full.txt";

//how many unique words are in array
int getArraySize() {
	int count = 0;
	while (count <= constants::MAX_WORDS) {
		if (getArrayWordAt(count) == "") {
			return count;
		}
		count++;
	}
	return count;
}

//get data at a particular location
std::string getArrayWordAt(int i) {
	return g_array[i].word;
}
int getArrayWord_NumbOccur_At(int i) {
	return g_array[i].number_occurences;
}

/*loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(std::fstream &myfstream) {

	if (!myfstream.is_open()) {
		return false;
	}
	string line;
	while (!myfstream.eof()) {
		getline(myfstream, line);
		processLine(line);
	}
	return true;
}

/*take 1 line and extract all the tokens from it
 feed each token to processToken for recording*/
void processLine(std::string &myString) {
	//processes the line token by token as shown in project description
	//const char constants::CHAR_TO_SEARCH_FOR = '';
	stringstream ss(myString);
	string token;

	while (getline(ss, token, CHAR_TO_SEARCH_FOR)) {
		processToken(token);

	}

}

/*Keep track of how many times each token seen*/
void processToken(std::string &token) {
	for (int i = 0; i <= constants::MAX_WORDS; i++) {

		strip_unwanted_chars(token);
		string temp1 = getArrayWordAt(i);
		string temp2 = token;
		toUpper(temp1);
		toUpper(temp2);

		if (temp1 == temp2) {
			g_array[i].number_occurences++;
			return;
		}

		else if (g_array[i].word == "") {
			g_array[i].word = token;
			g_array[i].number_occurences = 1;
			return;
		}
	}

}

/*if you are debugging the file must be in the project parent directory
 in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode) {

	myfile.open(myFileName.c_str());
	if (!myfile.is_open()) {
		cout << "Error: " + myFileName + " could not be opened." << endl;
	}
	return myfile.is_open();

}

/*iff myfile is open then close it*/
void closeFile(std::fstream& myfile) {
	if (myfile.is_open()) {
		myfile.close();
	}

}

/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename) {
	fstream outputFile;
	if (!openFile(outputFile, outputfilename)) {
		return FAIL_FILE_DID_NOT_OPEN;
	}
	if (getArraySize() == 0) {
		return FAIL_NO_ARRAY_DATA;
	}
	for (int i = 0; i < getArraySize(); i++) {
		outputFile << getArrayWordAt(i) << " " << getArrayWord_NumbOccur_At(i)
				<< "\n";
	}
	closeFile(outputFile);
	return SUCCESS;
}


bool compareToAscending(entry a, entry b) {
return a.word < b.word;
}

bool compareToDescending(entry a, entry b) {
return a.word > b.word;
}
bool compareToNumOccurrences(entry a, entry b) {
return a.number_occurences < b.number_occurences;
}
/*
 * Sort myEntryArray based on so enum value.
 * The presence of the enum implies a switch statement based on its value
 */
void sortArray(constants::sortOrder so) {
int size = getArraySize();
switch (so) {
case ASCENDING: {
	sort(begin(g_array), begin(g_array) + size, compareToAscending);
	/*for (int i = 0; i < size; i++) {
	 for (int j = size-1;
	 j > i && compareToAscending(g_array[i], g_array[j]); j--) {
	 //std::cout<<j<<std::endl;
	 entry temp = g_array[j];
	 g_array[j] = g_array[i];
	 g_array[i] = temp;
	 }
	 }*/
	break;

}
case DESCENDING: {
	sort(begin(g_array), begin(g_array) + size, compareToDescending);
	/*for (int i = 0; i < size; i++) {
	 for (int j = size;
	 j > i && compareToDescending(g_array[i], g_array[j]); j--) {
	 entry temp = g_array[j];
	 g_array[j] = g_array[i];
	 g_array[i] = temp;
	 }
	 }*/
	break;
}
case NUMBER_OCCURRENCES: {
	sort(begin(g_array), begin(g_array) + size, compareToNumOccurrences);
	/*for (int i = 0; i < size; i++) {
	 for (int j = size;
	 j > i && compareToNumOccurrences(g_array[i], g_array[j]);
	 j--) {
	 entry temp = g_array[j];
	 g_array[j] = g_array[i];
	 g_array[i] = temp;
	 }
	 }*/
	break;
}
case NONE: {
	return;
}
}

}




