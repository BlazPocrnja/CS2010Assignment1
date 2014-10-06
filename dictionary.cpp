#include <cstdio>
#include <cctype>
#include <iostream>

using namespace std;
/*
Author : Blaz Pocrnja 
Student ID : 5035473
Assignment #1 
Purpose: Reads a text file, and builds a dictionary of words found in the file. Keeps track of the frequency of words.
*/

#define NUMWORD 10
#define WORDSIZE 132

char tmpArray[WORDSIZE];
int tmpArrayStart;	    //Positional marker for adding characters to tmpArray

char dictionary[NUMWORD][WORDSIZE];

int numFilled;              //Number of filled dictionary locations

int freq[NUMWORD];	    //Frequency of words in dictionary corresponding to it's row numbers

void addChar(char);
bool cmpStrings(const char *, const char *);
void copyOver(void);
void searchDictionary(void);

/*
---------------------------------------------
-Adds character to temporary array at a given position
-Increments position everytime one is added 
---------------------------------------------
*/
void addChar(char ch){
	tmpArray[tmpArrayStart] = ch;
	tmpArrayStart++;
}

/*
---------------------------------------------
-Compares the first character of each string
and only continues comparing the pairs if they are equal
-Returns false if one pair does not equal
---------------------------------------------
*/
bool cmpStrings(const char * str1, const char * str2 ){
	for(int i = 0; i < WORDSIZE; i++){
		if(str1[i] != str2[i])
		return false;
	}
	return true;
}

/*
---------------------------------------------
-Copies temporary Array into the next available dictionary location
-Increments its frequency by 1
-Increments number of filled locations by 1
-Resets temporary array
---------------------------------------------
*/
void copyOver(){
	for(int i = 0; i < WORDSIZE; i++){
		dictionary[numFilled][i] = tmpArray[i];
	}
	freq[numFilled]++;
	numFilled++;
	for(int i = 0; i < WORDSIZE; i++){
		tmpArray[i] = '\0';
	}
}

/*
---------------------------------------------
-Compares rows of dictionary array with temporary array
-If there is a match, frequency is increased by 1 and return call is made
-Otherwise it must be added to dictionary with copyOver
---------------------------------------------
*/
void searchDictionary(){
	bool same;
	for(int i = 0; i < NUMWORD; i++){
		same = cmpStrings(tmpArray, dictionary[i]);
		if(same){
			freq[i]++;
			for(int i = 0; i < WORDSIZE; i++){
				tmpArray[i] = '\0';
			}
			return;
		}
	}
	copyOver();
	
}

/*
---------------------------------------------
-Reads input file one character at a time
-If character is alphabetic passes value to addChar function 
and increments word size counter (stringsize)
-A space or new line char calls a search of dictionary for previous alphabetic characters only if temporary array is not empty
and resets word size counter and pointer on temporary holding Array to 0
-Stops reading input when dictionary is full
-Outputs dictionary contents
---------------------------------------------
*/
int main(){
	char ch;
	int stringsize = 0;
	while(cin.good()){
		ch = cin.get();
		if (isalpha(ch)){
			if(stringsize < WORDSIZE){
				ch = tolower(ch);
				addChar(ch);
				stringsize++;
			}

		}
		else if (ch == ' ' || ch == '\n' ){
			if(tmpArray[0] != '\0'){
				searchDictionary();
			}
			stringsize = 0;
			tmpArrayStart = 0;
		}
		if (numFilled == NUMWORD){
			cout << "Dictionary Full"<< endl;
			break;
		}
	}
	
	cout << "Word		Frequency" << endl; 
	cout << "--------------------" << endl;
	for (int i = 0; i < numFilled; i++){
		for(int j = 0; j < WORDSIZE; j++){
			cout << dictionary[i][j];
		}
		cout << "				" << freq[i] << endl;
	}

}
